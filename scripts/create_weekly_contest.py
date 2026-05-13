#!/usr/bin/env python3

from datetime import datetime
from pathlib import Path
import re
import sys


REPO_ROOT = Path(__file__).resolve().parents[1]
WEEKLY_CONTESTS_DIR = REPO_ROOT / "weekly_contests"


def normalize_contest_id(raw: str) -> str:
    contest_id = raw.strip()
    if not re.fullmatch(r"\d+", contest_id):
        raise ValueError("Contest ID must be a positive integer, e.g. 493")
    return contest_id


def display_path(path: Path) -> str:
    return str(path.relative_to(REPO_ROOT))


def ensure_weekly_contests_dir():
    WEEKLY_CONTESTS_DIR.mkdir(parents=True, exist_ok=True)


def create_cpp_file(filepath: Path, contest_id: str, question_index: int):
    if filepath.exists():
        print(f"File already exists: {display_path(filepath)}")
        return

    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    template = f"""// Weekly Contest {contest_id} - Q{question_index}
// Created automatically
// Created at {now}
"""

    with filepath.open("w", encoding="utf-8") as file:
        file.write(template)

    print(f"File created: {display_path(filepath)}")


def create_cmakelists(filepath: Path):
    if filepath.exists():
        print(f"File already exists: {display_path(filepath)}")
        return

    content = """get_filename_component(CONTEST_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCES "Q*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(contest_${CONTEST_ID}_${name} ${src})
endforeach()
"""

    with filepath.open("w", encoding="utf-8") as file:
        file.write(content)

    print(f"File created: {display_path(filepath)}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 scripts/create_weekly_contest.py 493")
        sys.exit(1)

    try:
        contest_id = normalize_contest_id(sys.argv[1])
    except ValueError as error:
        print(f"Error: {error}")
        sys.exit(1)

    ensure_weekly_contests_dir()

    contest_dir = WEEKLY_CONTESTS_DIR / contest_id
    contest_dir.mkdir(parents=True, exist_ok=True)
    print(f"Directory ready: {display_path(contest_dir)}")

    for question_index in range(1, 5):
        create_cpp_file(
            contest_dir / f"Q{question_index}.cpp",
            contest_id,
            question_index,
        )

    create_cmakelists(contest_dir / "CMakeLists.txt")


if __name__ == "__main__":
    main()
