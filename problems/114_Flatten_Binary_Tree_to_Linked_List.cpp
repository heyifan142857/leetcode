//
// Created by user on 2025/9/8.
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
    TreeNode* new_root = nullptr;
    TreeNode* p = nullptr;
    void pre(TreeNode* root){
        if(root == nullptr){
            return;
        }
        if(p == nullptr){
            p = root;
        }else{
            p->right = root;
            p = p->right;
        }
        TreeNode* l = root->left;
        TreeNode* r = root->right;
        root->left = nullptr;
        root->right = nullptr;
        pre(l);
        pre(r);
    }
public:
    void flatten(TreeNode* root) {
        new_root = root;
        pre(root);
    }
};