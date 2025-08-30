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
public:
    bool isSymmetric(TreeNode* root) {
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        return _isSymmetric(left,right);
    }

    bool _isSymmetric(TreeNode* left, TreeNode* right){
        if(left == nullptr && right == nullptr){
            return true;
        }else if(left == nullptr || right == nullptr){
            return false;
        }else if(left->val != right->val){
            return false;
        }else{
            return (_isSymmetric(left->left,right->right) && _isSymmetric(left->right,right->left));
        }
    }
};