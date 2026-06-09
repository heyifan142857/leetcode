// 67. Add Binary
// Created automatically
// Created at 2026-05-13 11:48:32

#[allow(dead_code)]
struct Solution;

impl Solution {
    pub fn add_binary(a: String, b: String) -> String {
        let mut result = String::new();
        let mut i = a.len();
        let mut j = b.len();
        let mut carry = 0;

        while i > 0 || j > 0 || carry > 0 {
            let sum = carry
                + if i > 0 { a.chars().nth(i - 1).unwrap() - '0' } else { 0 }
                + if j > 0 { b.chars().nth(j - 1).unwrap() - '0' } else { 0 };

            result.insert(0, if sum % 2 == 1 { '1' } else { '0' });
            carry = sum / 2;

            if i > 0 {
                i -= 1;
            }
            if j > 0 {
                j -= 1;
            }
        }

        result
    }
}

fn main() {
}
