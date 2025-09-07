//
// Created by user on 2025/9/7.
//

#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    int diameter = 0;
    int maxDepth(TreeNode* root) {
        if(root == nullptr){
            return 0;
        }
        int left = 1+maxDepth(root->left);
        int right = 1+maxDepth(root->right);
        int cur = left+right-2;
        if(cur > diameter){
            diameter = cur;
        }
        return max(left, right);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDepth(root);
        return diameter;
    }
};