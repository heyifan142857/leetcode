#!/usr/bin/env python3

import argparse
from datetime import datetime
from pathlib import Path
import re
import sys


REPO_ROOT = Path(__file__).resolve().parents[1]
CPP_PROBLEMS_DIR = REPO_ROOT / "problems"
RUST_BIN_DIR = REPO_ROOT / "rust" / "src" / "bin"


def parse_problem_title(title: str) -> tuple[str, str]:
    match = re.match(r"^\s*(\d+)\.\s*(.*)$", title)
    if not match:
        raise ValueError("Input must be in format: 'Number. Problem Title'")

    return match.group(1), match.group(2)


def format_cpp_filename(title: str) -> str:
    """
    Convert:
    '1582. Special Positions in a Binary Matrix'
    -> '1582_Special_Positions_in_a_Binary_Matrix.cpp'
    """

    problem_id, problem_name = parse_problem_title(title)

    # Replace non-alphanumeric characters with underscore
    problem_name = re.sub(r"[^A-Za-z0-9]+", "_", problem_name)

    # Remove leading/trailing underscores
    problem_name = problem_name.strip("_")

    return f"{problem_id}_{problem_name}.cpp"


def format_rust_filename(title: str) -> str:
    """
    Convert:
    '1582. Special Positions in a Binary Matrix'
    -> 'p1582_special_positions_in_a_binary_matrix.rs'
    """

    problem_id, problem_name = parse_problem_title(title)
    problem_name = re.sub(r"[^A-Za-z0-9]+", "_", problem_name).strip("_").lower()

    return f"p{problem_id}_{problem_name}.rs"


def display_path(path: Path) -> str:
    return str(path.relative_to(REPO_ROOT))


def ensure_dir(directory: Path):
    directory.mkdir(parents=True, exist_ok=True)


def current_timestamp() -> str:
    return datetime.now().strftime("%Y-%m-%d %H:%M:%S")


def create_cpp_file(filepath: Path, title: str):
    if filepath.exists():
        print(f"File already exists: {display_path(filepath)}")
        return

    now = current_timestamp()

    template = f"""// {title}
// Created automatically
// Created at {now}

#include <bits/stdc++.h>
using namespace std;
"""

    with filepath.open("w", encoding="utf-8") as f:
        f.write(template)

    print(f"File created: {display_path(filepath)}")


def create_rust_file(filepath: Path, title: str):
    if filepath.exists():
        print(f"File already exists: {display_path(filepath)}")
        return

    now = current_timestamp()

    template = f"""// {title}
// Created automatically
// Created at {now}

#[allow(dead_code)]
struct Solution;

impl Solution {{
}}

fn main() {{
}}
"""

    with filepath.open("w", encoding="utf-8") as f:
        f.write(template)

    print(f"File created: {display_path(filepath)}")


def parse_args():
    parser = argparse.ArgumentParser(
        description="Create a LeetCode problem file.",
    )
    parser.add_argument(
        "title",
        help='Problem title, e.g. "1582. Special Positions in a Binary Matrix"',
    )
    parser.add_argument(
        "-l",
        "--lang",
        choices=("cpp", "rust"),
        default="cpp",
        help="Language for the created file. Defaults to cpp.",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    title = args.title
    # Normalize whitespace: collapse newlines and multiple spaces, then strip
    title = re.sub(r"\s+", " ", title).strip()

    try:
        if args.lang == "rust":
            filename = format_rust_filename(title)
            ensure_dir(RUST_BIN_DIR)
            filepath = RUST_BIN_DIR / filename
            create_rust_file(filepath, title)
        else:
            filename = format_cpp_filename(title)
            ensure_dir(CPP_PROBLEMS_DIR)
            filepath = CPP_PROBLEMS_DIR / filename
            create_cpp_file(filepath, title)
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
