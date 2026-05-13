#!/usr/bin/env python3
from __future__ import annotations

import argparse
import calendar
import csv
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass
from datetime import date, datetime, timedelta
from pathlib import Path


CPP_PROBLEM_RE = re.compile(r"^problems/(?P<id>\d+)[_.](?P<title>.+)\.cpp$")
RUST_PROBLEM_RE = re.compile(r"^rust/src/bin/p(?P<id>\d+)_(?P<title>.+)\.rs$")
WEEKLY_PROBLEM_RE = re.compile(r"^weekly_contests/(?P<contest>\d+)/Q(?P<question>[1-4])\.cpp$")

LANGS = ("cpp", "rust")
LANG_COLORS = {
    "cpp": "#d62728",
    "rust": "#f2b705",
}
PERIOD_ORDER = ("week", "month", "year")


@dataclass(frozen=True)
class ProblemInfo:
    problem_id: str
    title: str
    lang: str
    path: str
    is_weekly: bool = False


@dataclass(frozen=True)
class ProblemRecord:
    solved_date: date
    problem_id: str
    title: str
    lang: str
    path: str
    commit: str
    subject: str
    is_weekly: bool = False


def parse_date(value: str) -> date:
    try:
        return datetime.strptime(value, "%Y-%m-%d").date()
    except ValueError as exc:
        raise argparse.ArgumentTypeError("expected date in YYYY-MM-DD format") from exc


def clean_title(raw_title: str) -> str:
    title = raw_title.rsplit(".", 1)[0]
    title = title.strip("_ ")
    title = re.sub(r"[_\s]+", " ", title)
    return title or "Untitled"


def parse_problem_path(path: str, include_weekly: bool) -> ProblemInfo | None:
    cpp_match = CPP_PROBLEM_RE.match(path)
    if cpp_match:
        return ProblemInfo(
            problem_id=cpp_match.group("id"),
            title=clean_title(cpp_match.group("title")),
            lang="cpp",
            path=path,
        )

    rust_match = RUST_PROBLEM_RE.match(path)
    if rust_match:
        return ProblemInfo(
            problem_id=rust_match.group("id"),
            title=clean_title(rust_match.group("title")),
            lang="rust",
            path=path,
        )

    if include_weekly:
        weekly_match = WEEKLY_PROBLEM_RE.match(path)
        if weekly_match:
            contest = weekly_match.group("contest")
            question = weekly_match.group("question")
            return ProblemInfo(
                problem_id=f"weekly-{contest}-q{question}",
                title=f"Weekly {contest} Q{question}",
                lang="cpp",
                path=path,
                is_weekly=True,
            )

    return None


def run_git_log(repo: Path) -> str:
    command = [
        "git",
        "log",
        "--reverse",
        "--date=short",
        "--name-status",
        "--pretty=format:%x1e%H%x09%ad%x09%s",
        "--",
        "problems",
        "rust/src/bin",
        "weekly_contests",
    ]
    try:
        result = subprocess.run(
            command,
            cwd=repo,
            check=True,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
    except FileNotFoundError:
        raise SystemExit("git is required but was not found")
    except subprocess.CalledProcessError as exc:
        message = exc.stderr.strip() or "failed to read git log"
        raise SystemExit(message)
    return result.stdout


def records_from_git(repo: Path, include_weekly: bool) -> list[ProblemRecord]:
    current_commit = ""
    current_date: date | None = None
    current_subject = ""
    seen: set[tuple[str, str]] = set()
    records: list[ProblemRecord] = []

    for line in run_git_log(repo).split("\n"):
        if not line:
            continue

        if line.startswith("\x1e"):
            parts = line[1:].split("\t", 2)
            if len(parts) != 3:
                current_commit = ""
                current_date = None
                current_subject = ""
                continue
            current_commit, raw_date, current_subject = parts
            current_date = datetime.strptime(raw_date, "%Y-%m-%d").date()
            continue

        if current_date is None:
            continue

        fields = line.split("\t")
        status = fields[0]
        if status.startswith("D") or len(fields) < 2:
            continue

        infos = [
            info
            for info in (parse_problem_path(path, include_weekly) for path in fields[1:])
            if info is not None
        ]
        if not infos:
            continue

        info = infos[-1]
        key = (info.lang, info.problem_id)
        if key in seen:
            continue

        seen.add(key)
        records.append(
            ProblemRecord(
                solved_date=current_date,
                problem_id=info.problem_id,
                title=info.title,
                lang=info.lang,
                path=info.path,
                commit=current_commit,
                subject=current_subject,
                is_weekly=info.is_weekly,
            )
        )

    return records


def subtract_months(day: date, months: int) -> date:
    target_month = day.month - months
    target_year = day.year + (target_month - 1) // 12
    target_month = (target_month - 1) % 12 + 1
    last_day = calendar.monthrange(target_year, target_month)[1]
    return date(target_year, target_month, min(day.day, last_day))


def period_window(period: str, today: date) -> tuple[date, date]:
    if period == "week":
        return today - timedelta(days=7), today
    if period == "month":
        return subtract_months(today, 1), today
    if period == "year":
        return subtract_months(today, 12), today
    raise ValueError(f"unknown period: {period}")


def format_short_date(day: date, include_year: bool = True) -> str:
    if include_year:
        return f"{day.year}.{day.month}.{day.day}"
    return f"{day.month}.{day.day}"


def format_date_range(start: date, end: date) -> str:
    if start.year == end.year:
        return f"{format_short_date(start)}-{format_short_date(end, include_year=False)}"
    return f"{format_short_date(start)}-{format_short_date(end)}"


def count_period(records: list[ProblemRecord], today: date, period: str) -> Counter[str]:
    start, end = period_window(period, today)
    counts: Counter[str] = Counter()
    for record in records:
        if start <= record.solved_date <= end:
            counts[record.lang] += 1
            counts["total"] += 1
    return counts


def streaks(active_dates: set[date], today: date) -> tuple[int, int]:
    if not active_dates:
        return 0, 0

    longest = 0
    current_run = 0
    previous: date | None = None
    for active_date in sorted(active_dates):
        if previous is not None and active_date == previous + timedelta(days=1):
            current_run += 1
        else:
            current_run = 1
        longest = max(longest, current_run)
        previous = active_date

    current = 0
    cursor = today
    while cursor in active_dates:
        current += 1
        cursor -= timedelta(days=1)

    return current, longest


def summarize(records: list[ProblemRecord], today: date, include_weekly: bool) -> str:
    if not records:
        return "No problem records found in git history."

    by_lang = Counter(record.lang for record in records)
    date_counts = Counter(record.solved_date for record in records)
    month_counts = Counter((record.solved_date.year, record.solved_date.month) for record in records)
    current_streak, longest_streak = streaks(set(date_counts), today)
    best_day, best_day_count = max(date_counts.items(), key=lambda item: (item[1], item[0]))
    best_month, best_month_count = max(month_counts.items(), key=lambda item: (item[1], item[0]))

    langs_by_problem: dict[str, set[str]] = defaultdict(set)
    regular_langs_by_problem: dict[str, set[str]] = defaultdict(set)
    for record in records:
        langs_by_problem[record.problem_id].add(record.lang)
        if not record.is_weekly:
            regular_langs_by_problem[record.problem_id].add(record.lang)
    solved_in_multiple_langs = sorted(
        problem_id
        for problem_id, langs in regular_langs_by_problem.items()
        if len(langs) > 1
    )

    lines = [
        "LeetCode commit statistics",
        f"  Scope: {'regular problems + weekly contest Q files' if include_weekly else 'regular problem files only'}",
        f"  Date span: {min(date_counts)} to {max(date_counts)}",
        f"  Language entries: {len(records)}",
        f"  Unique problem ids: {len(langs_by_problem)}",
        f"  C++: {by_lang['cpp']}",
        f"  Rust: {by_lang['rust']}",
    ]

    for label, period in (("Past week", "week"), ("Past month", "month"), ("Past year", "year")):
        period_counts = count_period(records, today, period)
        start, end = period_window(period, today)
        lines.append(
            f"  {label} ({format_date_range(start, end)}): {period_counts['total']} "
            f"(cpp {period_counts['cpp']}, rust {period_counts['rust']})"
        )

    active_days = len(date_counts)
    average_per_active_day = len(records) / active_days
    lines.extend(
        [
            f"  Active days: {active_days}",
            f"  Avg per active day: {average_per_active_day:.2f}",
            f"  Current streak: {current_streak} day(s)",
            f"  Longest streak: {longest_streak} day(s)",
            f"  Best day: {best_day} ({best_day_count})",
            f"  Best month: {best_month[0]}-{best_month[1]:02d} ({best_month_count})",
            f"  Solved in both C++ and Rust: {len(solved_in_multiple_langs)}",
        ]
    )

    if solved_in_multiple_langs:
        sample = ", ".join(solved_in_multiple_langs[:12])
        suffix = " ..." if len(solved_in_multiple_langs) > 12 else ""
        lines.append(f"    {sample}{suffix}")

    lines.append("")
    lines.append("Recent records:")
    for record in records[-10:]:
        lines.append(
            f"  {record.solved_date}  {record.lang:<4}  "
            f"{record.problem_id:<8}  {record.title}"
        )

    return "\n".join(lines)


def build_daily_series(
    records: list[ProblemRecord],
    start: date,
    end: date,
    mode: str,
) -> tuple[list[date], dict[str, list[int]], list[int]]:
    days = (end - start).days + 1
    dates = [start + timedelta(days=offset) for offset in range(days)]
    index_by_date = {day: index for index, day in enumerate(dates)}
    series = {lang: [0] * days for lang in LANGS}

    for record in records:
        index = index_by_date.get(record.solved_date)
        if index is not None:
            series[record.lang][index] += 1

    total = [sum(series[lang][index] for lang in LANGS) for index in range(days)]

    if mode == "cumulative":
        for lang in LANGS:
            running = 0
            for index, value in enumerate(series[lang]):
                running += value
                series[lang][index] = running
        running_total = 0
        for index, value in enumerate(total):
            running_total += value
            total[index] = running_total

    return dates, series, total


def month_start(day: date) -> date:
    return date(day.year, day.month, 1)


def next_month(day: date) -> date:
    if day.month == 12:
        return date(day.year + 1, 1, 1)
    return date(day.year, day.month + 1, 1)


def build_monthly_series(
    records: list[ProblemRecord],
    start: date,
    end: date,
    mode: str,
) -> tuple[list[date], dict[str, list[int]], list[int]]:
    months: list[date] = []
    cursor = month_start(start)
    while cursor <= month_start(end):
        months.append(cursor)
        cursor = next_month(cursor)

    index_by_month = {month: index for index, month in enumerate(months)}
    series = {lang: [0] * len(months) for lang in LANGS}

    for record in records:
        if start <= record.solved_date <= end:
            index = index_by_month[month_start(record.solved_date)]
            series[record.lang][index] += 1

    total = [sum(series[lang][index] for lang in LANGS) for index in range(len(months))]

    if mode == "cumulative":
        for lang in LANGS:
            running = 0
            for index, value in enumerate(series[lang]):
                running += value
                series[lang][index] = running
        running_total = 0
        for index, value in enumerate(total):
            running_total += value
            total[index] = running_total

    return months, series, total


def plot_period(
    records: list[ProblemRecord],
    today: date,
    period: str,
    mode: str,
    output_dir: Path,
) -> Path:
    output_dir.mkdir(parents=True, exist_ok=True)
    os.environ.setdefault("MPLCONFIGDIR", str(output_dir / ".matplotlib"))

    try:
        import matplotlib

        matplotlib.use("Agg")
        import matplotlib.dates as mdates
        import matplotlib.pyplot as plt
    except ImportError as exc:
        raise SystemExit(
            "matplotlib is required for plotting. "
            "Install it with: python -m pip install matplotlib"
        ) from exc

    start, end = period_window(period, today)
    if period == "year":
        dates, series, total = build_monthly_series(records, start, end, mode)
        _, period_series, period_total = build_monthly_series(records, start, end, "daily")
        bucket = "monthly"
    else:
        dates, series, total = build_daily_series(records, start, end, mode)
        _, period_series, period_total = build_daily_series(records, start, end, "daily")
        bucket = "daily"

    output_suffix = bucket if mode == "daily" else f"{bucket}_{mode}"
    output_path = output_dir / f"leetcode_{period}_{output_suffix}.png"

    fig_width = 9 if period != "year" else 12
    fig, ax = plt.subplots(figsize=(fig_width, 5), constrained_layout=True)

    for lang in LANGS:
        ax.plot(
            dates,
            series[lang],
            color=LANG_COLORS[lang],
            linewidth=2.2,
            marker="o",
            markersize=4,
            label=f"{lang} ({sum(period_series[lang])})",
        )

    ax.plot(
        dates,
        total,
        color="#4d4d4d",
        linewidth=1.8,
        linestyle="--",
        label=f"total ({sum(period_total)})",
    )

    if mode == "cumulative":
        title_mode = f"Cumulative {bucket}"
    else:
        title_mode = "Monthly" if bucket == "monthly" else "Daily"
    ax.set_title(f"{title_mode} LeetCode problems ({format_date_range(start, end)})")
    ax.set_ylabel("Problems")
    ax.set_xlabel("Date")
    ax.grid(True, axis="y", alpha=0.25)
    ax.legend()

    if period == "year":
        ax.xaxis.set_major_locator(mdates.MonthLocator(interval=1))
        ax.xaxis.set_major_formatter(mdates.DateFormatter("%Y-%m"))
    else:
        ax.xaxis.set_major_formatter(mdates.DateFormatter("%m-%d"))

    fig.autofmt_xdate()
    fig.savefig(output_path, dpi=180)
    plt.close(fig)
    return output_path


def write_csv(records: list[ProblemRecord], path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as csv_file:
        writer = csv.DictWriter(
            csv_file,
            fieldnames=[
                "date",
                "language",
                "problem_id",
                "title",
                "path",
                "commit",
                "subject",
                "is_weekly",
            ],
        )
        writer.writeheader()
        for record in records:
            writer.writerow(
                {
                    "date": record.solved_date.isoformat(),
                    "language": record.lang,
                    "problem_id": record.problem_id,
                    "title": record.title,
                    "path": record.path,
                    "commit": record.commit,
                    "subject": record.subject,
                    "is_weekly": record.is_weekly,
                }
            )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Summarize LeetCode problem-solving records from git commits.",
    )
    parser.add_argument(
        "--repo",
        type=Path,
        default=Path("."),
        help="Git repository path. Defaults to the current directory.",
    )
    parser.add_argument(
        "--period",
        choices=("week", "month", "year", "all"),
        default="all",
        help="Chart period. Defaults to all three fixed periods.",
    )
    parser.add_argument(
        "--mode",
        choices=("daily", "cumulative"),
        default="daily",
        help="Plot daily counts or cumulative counts within each period.",
    )
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=Path("leetcode_stats_output"),
        help="Directory for generated charts and optional CSV.",
    )
    parser.add_argument(
        "--today",
        type=parse_date,
        default=date.today(),
        help="Anchor date for past week/month/year windows, in YYYY-MM-DD.",
    )
    parser.add_argument(
        "--include-weekly",
        action="store_true",
        help="Also count weekly_contests/<contest>/Q*.cpp files.",
    )
    parser.add_argument(
        "--no-plot",
        action="store_true",
        help="Print statistics without generating charts.",
    )
    parser.add_argument(
        "--write-csv",
        action="store_true",
        help="Write the deduplicated problem records as CSV.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    repo = args.repo.resolve()
    records = records_from_git(repo, args.include_weekly)

    print(summarize(records, args.today, args.include_weekly))

    if args.write_csv:
        csv_path = args.output_dir / "problem_records.csv"
        write_csv(records, csv_path)
        print(f"\nCSV written: {csv_path}")

    if not args.no_plot:
        periods = PERIOD_ORDER if args.period == "all" else (args.period,)
        generated = [
            plot_period(records, args.today, period, args.mode, args.output_dir)
            for period in periods
        ]
        print("\nCharts written:")
        for output_path in generated:
            print(f"  {output_path}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
