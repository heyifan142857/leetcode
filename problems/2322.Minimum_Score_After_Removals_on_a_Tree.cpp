//
// Created by user on 2025/7/24.
//
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> xorSubtree;
    vector<vector<int>> tree;
    vector<int> parent;
    int n;

    void dfs(int u, int p, const vector<int>& nums){
        xorSubtree[u] = nums[u];
        parent[u] = p;
        for (int v:tree[u]) {
            if(v != p){
                dfs(v, u, nums);
                xorSubtree[u] ^= xorSubtree[v];
            }
        }
    }

    bool isAncestor(int u, int v){
        while(v != -1){
            if(u == v){
                return true;
            }
            v = parent[v];
        }
        return false;
    }

    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        n = nums.size();
        xorSubtree.resize(n);
        tree.resize(n, {});
        parent.resize(n, -1);

        for (vector<int> e:edges) {
            tree[e[0]].push_back(e[1]);
            tree[e[1]].push_back(e[0]);
        }

        dfs(0, -1, nums);

        int minScore = INT_MAX;

        for (int u = 1; u < n; ++u) {
            for (int v = 1; v < u; ++v) {
                if (u == v){
                    continue;
                }
                if(isAncestor(u, v)){
                    int x = xorSubtree[v];
                    int y = xorSubtree[u] ^ xorSubtree[v];
                    int z = xorSubtree[0] ^ xorSubtree[u];
                    minScore = min(minScore, max({x, y, z}) - min({x, y, z}));
                }else if(isAncestor(v, u)){
                    int x = xorSubtree[u];
                    int y = xorSubtree[v] ^ xorSubtree[u];
                    int z = xorSubtree[0] ^ xorSubtree[v];
                    minScore = min(minScore, max({x, y, z}) - min({x, y, z}));
                }else{
                    int x = xorSubtree[u];
                    int y = xorSubtree[v];
                    int z = xorSubtree[0] ^ xorSubtree[u] ^ xorSubtree[v];
                    minScore = min(minScore, max({x, y, z}) - min({x, y, z}));
                }
            }
        }

        return minScore;
    }
};