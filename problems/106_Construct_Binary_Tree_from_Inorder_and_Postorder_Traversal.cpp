// 106. Construct Binary Tree from Inorder and Postorder Traversal
// Created automatically
// Created at 2026-03-19 11:50:31

#include <bits/stdc++.h>
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
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty()) return nullptr;

        unordered_map<int,int> idx;
        for (int i = 0; i < (int)inorder.size(); ++i) idx[inorder[i]] = i;

        function<TreeNode*(int,int,int,int)> build = [&](int inL, int inR, int postL, int postR) -> TreeNode* {
            if (inL > inR || postL > postR) return nullptr;
            int rootVal = postorder[postR];
            TreeNode* root = new TreeNode(rootVal);
            int inRoot = idx[rootVal];
            int leftSize = inRoot - inL;
            root->left = build(inL, inRoot - 1, postL, postL + leftSize - 1);
            root->right = build(inRoot + 1, inR, postL + leftSize, postR - 1);
            return root;
        };

        return build(0, (int)inorder.size() - 1, 0, (int)postorder.size() - 1);
    }
};