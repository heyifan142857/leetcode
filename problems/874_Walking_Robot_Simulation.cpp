// 874. Walking Robot Simulation
// Created automatically
// Created at 2026-04-06 14:13:04

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<long long> blocked;
        blocked.reserve(obstacles.size() * 2);

        for (const auto& obstacle : obstacles) {
            long long x = obstacle[0];
            long long y = obstacle[1];
            blocked.insert((x << 32) ^ (y & 0xffffffffLL));
        }

        const int dx[4] = {0, 1, 0, -1};
        const int dy[4] = {1, 0, -1, 0};

        int dir = 0;
        int x = 0, y = 0;
        long long best = 0;

        for (int command : commands) {
            if (command == -2) {
                dir = (dir + 3) % 4;
                continue;
            }
            if (command == -1) {
                dir = (dir + 1) % 4;
                continue;
            }

            for (int step = 0; step < command; ++step) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                long long key = (static_cast<long long>(nx) << 32) ^ (static_cast<unsigned int>(ny));
                if (blocked.count(key)) break;

                x = nx;
                y = ny;
                best = max(best, 1LL * x * x + 1LL * y * y);
            }
        }

        return static_cast<int>(best);
    }
};
