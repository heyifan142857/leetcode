//
// Created by user on 2025/9/7.
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
    void dfs(TreeNode* root, TreeNode* new_root){
        new_root->val = root->val;
        if(root->left != nullptr){
            new_root->right = new TreeNode;
            dfs(root->left, new_root->right);
        }
        if(root->right != nullptr){
            new_root->left = new TreeNode;
            dfs(root->right, new_root->left);
        }
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr){
            return nullptr;
        }
        TreeNode* new_root = new TreeNode;

        dfs(root, new_root);

        return new_root;
    }
};