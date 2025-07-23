//
// Created by user on 2025/7/22.
//
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
private:
    struct node{
        map<string, node*> children;
        bool deleted = false;
    };

    void mark_sig(node * root, unordered_map<string, vector<node *>> &sigs){
        if(!root->children.empty()){
            sigs[generate_sig(root)].push_back(root);
            if(sigs[generate_sig(root)].size() > 1){
                for (node * n:sigs[generate_sig(root)]) {
                    n->deleted = true;
                }
            }
        }
        for (const auto& pair: root->children) {
            mark_sig(root->children[pair.first], sigs);
        }
    }

    string generate_sig(node * root){
        string sig = "(";
        for (const auto& pair: root->children) {
            sig += pair.first;
            sig += generate_sig(pair.second);
        }
        sig += ")";
        return sig;
    }

    void dfs(node * root, vector<vector<string>> &remaining, vector<string> path = {}){
        for (const auto& pair: root->children) {
            if(pair.second->deleted){
                continue;
            }
            vector<string> cur_path = path;
            cur_path.push_back(pair.first);
            remaining.push_back(cur_path);
            dfs(root->children[pair.first], remaining, cur_path);
        }
    }

public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        node *root = new node;
        for (const vector<string>& path:paths) {
            node * cur = root;
            for (const string& s:path) {
                if(not cur->children[s]){
                    cur->children[s] = new node;
                }
                cur = cur->children[s];
            }
        }

        unordered_map<string, vector<node *>> sigs;

        mark_sig(root, sigs);

        vector<vector<string>> remaining;

        dfs(root, remaining);

        return remaining;
    }
};

/*
官方题解
struct Trie {
    // 当前节点结构的序列化表示
    string serial;
    // 当前节点的子节点
    unordered_map<string, Trie*> children;
};

class Solution {
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        // 根节点
        Trie* root = new Trie();

        for (const vector<string>& path: paths) {
            Trie* cur = root;
            for (const string& node: path) {
                if (!cur->children.count(node)) {
                    cur->children[node] = new Trie();
                }
                cur = cur->children[node];
            }
        }

        // 哈希表记录每一种序列化表示的出现次数
        unordered_map<string, int> freq;
        // 基于深度优先搜索的后序遍历，计算每一个节点结构的序列化表示
        function<void(Trie*)> construct = [&](Trie* node) {
            // 如果是叶节点，那么序列化表示为空字符串，无需进行任何操作
            if (node->children.empty()) {
                return;
            }

            vector<string> v;
            // 如果不是叶节点，需要先计算子节点结构的序列化表示
            for (const auto& [folder, child]: node->children) {
                construct(child);
                v.push_back(folder + "(" + child->serial + ")");
            }
            // 防止顺序的问题，需要进行排序
            sort(v.begin(), v.end());
            for (string& s: v) {
                node->serial += move(s);
            }
            // 计入哈希表
            ++freq[node->serial];
        };

        construct(root);

        vector<vector<string>> ans;
        // 记录根节点到当前节点的路径
        vector<string> path;

        function<void(Trie*)> operate = [&](Trie* node) {
            // 如果序列化表示在哈希表中出现了超过 1 次，就需要删除
            if (freq[node->serial] > 1) {
                return;
            }
            // 否则将路径加入答案
            if (!path.empty()) {
                ans.push_back(path);
            }
            for (const auto& [folder, child]: node->children) {
                path.push_back(folder);
                operate(child);
                path.pop_back();
            }
        };

        operate(root);
        return ans;
    }
};
*/