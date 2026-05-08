// 3629. Minimum Jumps to Reach End via Prime Teleportation
// Created automatically
// Created at 2026-05-08 09:11:27

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        int maxNum = *max_element(nums.begin(), nums.end());
        vector<int> spf(maxNum + 1);
        for (int i = 0; i <= maxNum; ++i) spf[i] = i;
        if (maxNum >= 1) spf[1] = 1;

        for (long long i = 2; i * i <= maxNum; ++i) {
            if (spf[i] != i) continue;
            for (long long j = i * i; j <= maxNum; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }

        unordered_map<int, vector<int>> indicesByFactor;
        indicesByFactor.reserve(n * 3);
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            while (x > 1) {
                int p = spf[x];
                indicesByFactor[p].push_back(i);
                while (x % p == 0) x /= p;
            }
        }

        vector<int> dist(n, -1);
        vector<char> usedPrime(maxNum + 1, false);
        queue<int> q;
        dist[0] = 0;
        q.push(0);

        auto visit = [&](int next, int cur) {
            if (next < 0 || next >= n || dist[next] != -1) return;
            dist[next] = dist[cur] + 1;
            q.push(next);
        };

        while (!q.empty()) {
            int i = q.front();
            q.pop();
            if (i == n - 1) return dist[i];

            visit(i - 1, i);
            visit(i + 1, i);

            int p = nums[i];
            if (p >= 2 && spf[p] == p && !usedPrime[p]) {
                usedPrime[p] = true;
                auto it = indicesByFactor.find(p);
                if (it != indicesByFactor.end()) {
                    for (int j : it->second) visit(j, i);
                    indicesByFactor.erase(it);
                }
            }
        }

        return dist[n - 1];
    }
};
