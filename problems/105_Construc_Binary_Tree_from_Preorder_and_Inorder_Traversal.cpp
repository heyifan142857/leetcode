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
    vector<int> pre;
    vector<int> in;
    TreeNode* _buildTree(int pre_l, int pre_r, int in_l, int in_r) {
        if(in_l>in_r){
            return nullptr;
        }

        int cur = pre[pre_l];

        int in_m = 0;
        for (int i = in_l; i <= in_r; ++i) {
            if(cur == in[i]){
                in_m = i;
                break;
            }
        }

        return new TreeNode(cur,
                            _buildTree(pre_l+1, pre_l+in_m-in_l,in_l,in_m-1),
                            _buildTree(pre_l+in_m-in_l+1, pre_r, in_m+1, in_r));
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pre = preorder;
        in = inorder;
        return _buildTree(0, pre.size()-1, 0, in.size()-1);
    }
};