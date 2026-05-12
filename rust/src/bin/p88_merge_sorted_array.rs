// 88. Merge Sorted Array
// Created automatically
// Created at 2026-05-12 15:05:25

#[allow(dead_code)]
struct Solution;

impl Solution {
    #[allow(unused_variables)]
    pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
        let mut i = m as isize - 1;
        let mut j = n as isize - 1;
        let mut k = (m + n) as isize - 1;

        while j >= 0 {
            if i >= 0 && nums1[i as usize] > nums2[j as usize] {
                nums1[k as usize] = nums1[i as usize];
                i -= 1;
            } else {
                nums1[k as usize] = nums2[j as usize];
                j -= 1;
            }
            k -= 1;
        }
    }
}

fn main() {
}
