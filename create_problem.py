#!/usr/bin/env python3

import argparse
from datetime import datetime
import os
import re
import sys


CPP_PROBLEMS_DIR = "problems"
RUST_BIN_DIR = os.path.join("rust", "src", "bin")


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


def ensure_dir(directory: str):
    os.makedirs(directory, exist_ok=True)


def current_timestamp() -> str:
    return datetime.now().strftime("%Y-%m-%d %H:%M:%S")


def create_cpp_file(filepath: str, title: str):
    if os.path.exists(filepath):
        print(f"File already exists: {filepath}")
        return

    now = current_timestamp()

    template = f"""// {title}
// Created automatically
// Created at {now}

#include <bits/stdc++.h>
using namespace std;
"""

    with open(filepath, "w", encoding="utf-8") as f:
        f.write(template)

    print(f"File created: {filepath}")


def create_rust_file(filepath: str, title: str):
    if os.path.exists(filepath):
        print(f"File already exists: {filepath}")
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

    with open(filepath, "w", encoding="utf-8") as f:
        f.write(template)

    print(f"File created: {filepath}")


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
            filepath = os.path.join(RUST_BIN_DIR, filename)
            create_rust_file(filepath, title)
        else:
            filename = format_cpp_filename(title)
            ensure_dir(CPP_PROBLEMS_DIR)
            filepath = os.path.join(CPP_PROBLEMS_DIR, filename)
            create_cpp_file(filepath, title)
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
