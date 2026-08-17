// 2492. Minimum Score of a Path Between Two Cities
// Created automatically
// Created at 2026-07-04 14:44:57

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>> &roads) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto &road : roads) {
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        }

        int answer = INT_MAX;
        vector<int> visited(n + 1, 0);
        queue<int> q;
        q.push(1);
        visited[1] = 1;

        while (!q.empty()) {
            int city = q.front();
            q.pop();

            for (const auto &[nextCity, distance] : graph[city]) {
                answer = min(answer, distance);
                if (!visited[nextCity]) {
                    visited[nextCity] = 1;
                    q.push(nextCity);
                }
            }
        }

        return answer;
    }
};
