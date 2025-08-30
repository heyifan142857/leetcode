//
// Created by user on 2025/8/30.
//

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    int _count;
    int res;
    bool found;
public:
    void _kthSmallest(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        if (found == true) {
            return;
        }
        _kthSmallest(root->left);

        if (_count > 1) {
            _count--;
        }else {
            if (found == true) {
                return;
            }
            res = root->val;
            found = true;
            return;
        }

        _kthSmallest(root->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        _count = k;
        res = -1;
        found = false;
        _kthSmallest(root);
        return res;
    }
};