#!/usr/bin/env python3

from datetime import datetime
import os
import re
import sys


WEEKLY_CONTESTS_DIR = "weekly_contests"


def normalize_contest_id(raw: str) -> str:
    contest_id = raw.strip()
    if not re.fullmatch(r"\d+", contest_id):
        raise ValueError("Contest ID must be a positive integer, e.g. 493")
    return contest_id


def ensure_weekly_contests_dir():
    os.makedirs(WEEKLY_CONTESTS_DIR, exist_ok=True)


def create_cpp_file(filepath: str, contest_id: str, question_index: int):
    if os.path.exists(filepath):
        print(f"File already exists: {filepath}")
        return

    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    template = f"""// Weekly Contest {contest_id} - Q{question_index}
// Created automatically
// Created at {now}
"""

    with open(filepath, "w", encoding="utf-8") as file:
        file.write(template)

    print(f"File created: {filepath}")


def create_cmakelists(filepath: str):
    if os.path.exists(filepath):
        print(f"File already exists: {filepath}")
        return

    content = """get_filename_component(CONTEST_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCES "Q*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(contest_${CONTEST_ID}_${name} ${src})
endforeach()
"""

    with open(filepath, "w", encoding="utf-8") as file:
        file.write(content)

    print(f"File created: {filepath}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 create_weekly_contest.py 493")
        sys.exit(1)

    try:
        contest_id = normalize_contest_id(sys.argv[1])
    except ValueError as error:
        print(f"Error: {error}")
        sys.exit(1)

    ensure_weekly_contests_dir()

    contest_dir = os.path.join(WEEKLY_CONTESTS_DIR, contest_id)
    os.makedirs(contest_dir, exist_ok=True)
    print(f"Directory ready: {contest_dir}")

    for question_index in range(1, 5):
        create_cpp_file(
            os.path.join(contest_dir, f"Q{question_index}.cpp"),
            contest_id,
            question_index,
        )

    create_cmakelists(os.path.join(contest_dir, "CMakeLists.txt"))


if __name__ == "__main__":
    main()
