// 1594. Maximum Non Negative Product in a Matrix
// Created automatically
// Created at 2026-05-12 15:10:37

#[allow(dead_code)]
struct Solution;

impl Solution {
    pub fn max_product_path(grid: Vec<Vec<i32>>) -> i32 {
        const MOD: i128 = 1_000_000_007;

        let rows = grid.len();
        let cols = grid[0].len();
        let mut dp = vec![(0_i128, 0_i128); cols];

        for r in 0..rows {
            for c in 0..cols {
                let value = grid[r][c] as i128;

                dp[c] = match (r, c) {
                    (0, 0) => (value, value),
                    (0, _) => {
                        let (min_prev, max_prev) = dp[c - 1];
                        let candidates = [min_prev * value, max_prev * value];
                        (
                            *candidates.iter().min().unwrap(),
                            *candidates.iter().max().unwrap(),
                        )
                    }
                    (_, 0) => {
                        let (min_prev, max_prev) = dp[c];
                        let candidates = [min_prev * value, max_prev * value];
                        (
                            *candidates.iter().min().unwrap(),
                            *candidates.iter().max().unwrap(),
                        )
                    }
                    _ => {
                        let (top_min, top_max) = dp[c];
                        let (left_min, left_max) = dp[c - 1];
                        let candidates = [
                            top_min * value,
                            top_max * value,
                            left_min * value,
                            left_max * value,
                        ];
                        (
                            *candidates.iter().min().unwrap(),
                            *candidates.iter().max().unwrap(),
                        )
                    }
                };
            }
        }

        let result = dp[cols - 1].1;
        if result < 0 {
            -1
        } else {
            (result % MOD) as i32
        }
    }
}

fn main() {
}
