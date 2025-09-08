//
// Created by user on 2025/9/8.
//

#include <unordered_map>
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
    int res = 0;
    int target = 0;
    void _pathSum(TreeNode* root, long long sum, unordered_map<long long, int> map) {
        if(root == nullptr){
            return;
        }
        sum += root->val;
        res += map[sum-target];
        map[sum]++;
        _pathSum(root->left, sum, map);
        _pathSum(root->right, sum, map);
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        target = targetSum;
        unordered_map<long long, int> map;
        map[0] = 1;
        _pathSum(root, 0, map);
        return res;
    }
};