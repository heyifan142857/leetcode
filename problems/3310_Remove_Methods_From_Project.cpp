// 3310. Remove Methods From Project
// Created automatically
// Created at 2026-08-05 16:28:51

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
      
        for (auto& inv : invocations) {
            graph[inv[0]].push_back(inv[1]);
        }
        unordered_set<int> visited;
        dfs(k, graph, visited);
        vector<int> result;
        bool can_remove = true;
        for (int i = 0; i < n; ++i) {
            if (visited.find(i) == visited.end()) {
                result.push_back(i);
      
                for (int next : graph[i]) {
                    if (visited.find(next) != visited.end()) {
                        can_remove = false;
                    }
                }
            }
        }
        if (can_remove) {
            return result;
        }
        for (auto &i : visited) {
            result.push_back(i);
        }
        return result;
    }

    void dfs(int node, vector<vector<int>>& graph, unordered_set<int>& visited) {
        if (visited.find(node) != visited.end()) {
            return;
        }
        visited.insert(node);
        if (graph[node].empty()) {
            return;
        }
        for (auto &i : graph[node]) {
            dfs(i, graph, visited);
        }
    }
};