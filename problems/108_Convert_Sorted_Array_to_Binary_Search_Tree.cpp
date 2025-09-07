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
    TreeNode* _sortedArrayToBST(int l, int r, vector<int>& nums){
        if(r<l){
            return nullptr;
        }
        int mid = l + (r - l) / 2;
        return new TreeNode(nums[mid],
                            _sortedArrayToBST(l, mid-1, nums),
                            _sortedArrayToBST(mid+1, r, nums));
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = _sortedArrayToBST(0, nums.size()-1, nums);

        return root;
    }
};