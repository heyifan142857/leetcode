# leetcode

This repository stores my LeetCode problem-solving practice in C++ and Rust.

## Structure

- `algorithms/`: standalone C++ algorithm examples
- `data_structures/`: standalone C++ data structure examples
- `problems/`: regular C++ LeetCode problems
- `rust/src/bin/`: regular Rust LeetCode problems managed by Cargo
- `weekly_contests/`: C++ weekly contest folders
- `scripts/`: Python helper scripts

## Data Structures

The `data_structures/` directory currently contains:

- `Huffman-Tree.cpp`: builds a Huffman tree and demonstrates encoding and decoding
- `Threaded-Binary-Tree.cpp`: creates an inorder-threaded binary tree and traverses it without a stack
- `Union-Find.cpp`: implements disjoint-set union with path compression and union by rank

Each file is an independent executable. Build all C++ examples with CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Scripts

Install Python dependencies for chart generation:

```bash
python3 -m pip install -r requirements.txt
```

Create a normal C++ problem file:

```bash
python3 scripts/create_problem.py "1582. Special Positions in a Binary Matrix"
```

Create a normal Rust problem file:

```bash
python3 scripts/create_problem.py --lang rust "1582. Special Positions in a Binary Matrix"
```

Run a Rust problem locally:

```bash
cd rust
cargo run --bin p1582_special_positions_in_a_binary_matrix
```

Create a weekly contest folder with `Q1.cpp` to `Q4.cpp`:

```bash
python3 scripts/create_weekly_contest.py 493
```

Generate LeetCode statistics and charts:

```bash
python3 scripts/leetcode_stats.py
```

Print statistics without generating charts:

```bash
python3 scripts/leetcode_stats.py --no-plot
```
