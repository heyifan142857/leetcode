//
// Created by user on 2025/9/8.
//
#include <unordered_map>
#include <climits>
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
    unordered_map<TreeNode*, int> prefix;
    int maxSum = INT_MIN;
    int post(TreeNode* root){
        if(root == nullptr){
            return 0;
        }
        post(root->left);
        post(root->right);
        int cur = root->val + max(max(0, prefix[root->left]), max(0, prefix[root->right]));
        prefix[root] = cur;
        if(cur >= maxSum){
            maxSum = cur;
        }
        return cur;
    }

    void dfs(TreeNode* root){
        if(root == nullptr){
            return;
        }
        int cur = root->val + max(0, prefix[root->left]) + max(0, prefix[root->right]);
        if(cur >= maxSum){
            maxSum = cur;
        }
        dfs(root->left);
        dfs(root->right);
    }

public:
    int maxPathSum(TreeNode* root) {
        post(root);

        dfs(root);

        return maxSum;
    }
};