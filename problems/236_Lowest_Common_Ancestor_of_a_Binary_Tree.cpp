//
// Created by user on 2025/9/8.
//

#include <deque>
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
    deque<TreeNode*> p_list;
    deque<TreeNode*> q_list;
    bool find_p = false;
    bool find_q = false;
    void dfs(TreeNode* root, TreeNode* p, TreeNode* q){
        if(find_p && find_q){
            return;
        }
        if(root == nullptr){
            return;
        }
        if(!find_p){
            p_list.emplace_back(root);
        }
        if(!find_q){
            q_list.emplace_back(root);
        }
        if(root == p){
            find_p = true;
        }
        if(root == q){
            find_q = true;
        }
        dfs(root->left, p, q);
        dfs(root->right, p, q);
        if(!find_p){
            p_list.pop_back();
        }
        if(!find_q){
            q_list.pop_back();
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);

        int len = min(p_list.size(), q_list.size());

        TreeNode* ancestor = nullptr;

        for (int i = 0; i < len; ++i) {
            if(p_list[i]==q_list[i]){
                ancestor = p_list[i];
            }else{
                break;
            }
        }

        return ancestor;
    }
};

int main(){
    TreeNode* son = new TreeNode(2);
    TreeNode* root = new TreeNode(1, son, nullptr);
    Solution s;
    s.lowestCommonAncestor(root, root, son);
}