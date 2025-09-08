//
// Created by user on 2025/9/8.
//
#include <climits>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    bool _isValidBST(TreeNode* root, long long min, long long max) {
        if(root== nullptr){
            return true;
        }
        if(root->left != nullptr && (root->left->val >= root->val || root->left->val <= min)){
            return false;
        }
        if(root->right != nullptr && (root->right->val <= root->val || root->right->val >= max)){
            return false;
        }
        return (_isValidBST(root->left, min, root->val) && _isValidBST((root->right), root->val, max));
    }
public:
    bool isValidBST(TreeNode* root) {
        return _isValidBST(root, LONG_LONG_MIN, LONG_LONG_MAX);
    }
};