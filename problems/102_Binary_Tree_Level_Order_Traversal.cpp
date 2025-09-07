//
// Created by user on 2025/9/7.
//
#include <vector>
#include <queue>
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr){
            return {};
        }

        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);

        vector<vector<int>> ans;

        vector<int> level;

        while (!q.empty()){
            TreeNode* cur = q.front();
            q.pop();

            if(cur == nullptr){
                ans.push_back(level);
                level.clear();
                if(q.empty()){
                    break;
                }

                q.push(nullptr);
                continue;
            }

            level.push_back(cur->val);
            if(cur->left != nullptr){
                q.push(cur->left);
            }
            if(cur->right != nullptr){
                q.push(cur->right);
            }
        }
        return ans;
    }
};