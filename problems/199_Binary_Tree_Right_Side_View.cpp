//
// Created by user on 2025/9/8.
//
#include <vector>
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
    void _rightSideView(TreeNode* root, int cnt, vector<int>& ans) {
        if(root == nullptr){
            return;
        }

        if(cnt > ans.size()){
            ans.push_back(root->val);
        }

        _rightSideView(root->right, cnt+1, ans);
        _rightSideView(root->left, cnt+1, ans);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;

        int cnt = 1;

        _rightSideView(root, cnt, ans);

        return ans;
    }
};