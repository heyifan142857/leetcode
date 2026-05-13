// 222. Count Complete Tree Nodes
// Created automatically
// Created at 2026-05-13 11:44:02

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: Option<Rc<RefCell<TreeNode>>>,
  pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
  #[inline]
  pub fn new(val: i32) -> Self {
    TreeNode {
      val,
      left: None,
      right: None
    }
  }
}

#[allow(dead_code)]
struct Solution;

use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    pub fn count_nodes(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if root.is_none() {
            return 0;
        }
        1 + Self::count_nodes(root.as_ref().unwrap().borrow().left.clone()) + Self::count_nodes(root.as_ref().unwrap().borrow().right.clone())
    }
}

fn main() {
}
