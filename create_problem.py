#!/usr/bin/env python3

from datetime import datetime
import os
import re
import sys


def format_filename(title: str) -> str:
    """
    Convert:
    '1582. Special Positions in a Binary Matrix'
    -> '1582_Special_Positions_in_a_Binary_Matrix.cpp'
    """

    match = re.match(r"^\s*(\d+)\.\s*(.*)$", title)
    if not match:
        raise ValueError("Input must be in format: 'Number. Problem Title'")

    problem_id = match.group(1)
    problem_name = match.group(2)

    # Replace non-alphanumeric characters with underscore
    problem_name = re.sub(r"[^A-Za-z0-9]+", "_", problem_name)

    # Remove leading/trailing underscores
    problem_name = problem_name.strip("_")

    return f"{problem_id}_{problem_name}.cpp"


def ensure_problems_dir():
    if not os.path.exists("problems"):
        os.makedirs("problems")


def create_cpp_file(filepath: str, title: str):
    if os.path.exists(filepath):
        print(f"File already exists: {filepath}")
        return

    # Get current time
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    template = f"""// {title}
// Created automatically
// Created at {now}
"""

    with open(filepath, "w", encoding="utf-8") as f:
        f.write(template)

    print(f"File created: {filepath}")


def main():
    if len(sys.argv) != 2:
        print('Usage: python3 create_problem.py "1582. Special Positions in a Binary Matrix"')
        sys.exit(1)

    title = sys.argv[1]

    try:
        filename = format_filename(title)
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)

    ensure_problems_dir()

    filepath = os.path.join("problems", filename)

    create_cpp_file(filepath, title)


if __name__ == "__main__":
    main()