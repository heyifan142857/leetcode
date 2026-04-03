// 3661. Maximum Walls Destroyed by Robots
// Created automatically
// Created at 2026-04-03 14:15:34

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        int m = walls.size();
        if (n == 0 || m == 0) return 0;

        vector<pair<long long,long long>> rd(n);
        for (int i = 0; i < n; ++i) rd[i] = {robots[i], distance[i]};
        sort(rd.begin(), rd.end());
        vector<long long> pos(n), dist(n);
        for (int i = 0; i < n; ++i) { pos[i] = rd[i].first; dist[i] = rd[i].second; }

        vector<long long> w = vector<long long>(walls.begin(), walls.end());
        sort(w.begin(), w.end());

        // Distribute walls into segments: index 0 = left of first robot,
        // 1..n-1 between robots, n = right of last robot.
        vector<vector<long long>> segWalls(n+1);
        vector<int> robotPosWalls(n, 0);
        int ri = 0;
        for (long long val : w) {
            while (ri < n && pos[ri] < val) ++ri;
            if (ri < n && pos[ri] == val) {
                robotPosWalls[ri]++;
            } else {
                // belongs to segment index = ri (0..n)
                segWalls[ri].push_back(val);
            }
        }

        // Precompute reach counts per segment
        vector<int> prevReach(n+1, 0), curReach(n+1, 0), bothReach(n+1, 0);
        for (int s = 0; s <= n; ++s) {
            auto &vec = segWalls[s];
            if (vec.empty()) { prevReach[s] = curReach[s] = bothReach[s] = 0; continue; }
            int prev = s - 1;
            int cur = s;
            int cntPrev = 0, cntCur = 0, cntBoth = 0;
            if (prev >= 0) {
                long long bound = pos[prev] + dist[prev];
                cntPrev = int(upper_bound(vec.begin(), vec.end(), bound) - vec.begin());
            }
            if (cur < n) {
                long long bound = pos[cur] - dist[cur];
                cntCur = int(vec.end() - lower_bound(vec.begin(), vec.end(), bound));
            }
            if (prev >= 0 && cur < n) {
                long long lo = pos[cur] - dist[cur];
                long long hi = pos[prev] + dist[prev];
                int overlap = 0;
                if (lo <= hi) {
                    auto it1 = lower_bound(vec.begin(), vec.end(), lo);
                    auto it2 = upper_bound(vec.begin(), vec.end(), hi);
                    overlap = int(it2 - it1);
                }
                cntBoth = cntPrev + cntCur - overlap;
            } else {
                cntBoth = cntPrev + cntCur;
            }
            prevReach[s] = cntPrev;
            curReach[s] = cntCur;
            bothReach[s] = cntBoth;
        }

        const long long NEG = LLONG_MIN/4;
        // DP over robots. state: last robot choice (0=L,1=R)
        long long dpL = curReach[0]; // robot0 chooses left covers leftmost segment
        long long dpR = 0; // robot0 chooses right

        for (int i = 1; i < n; ++i) {
            long long ndpL = NEG, ndpR = NEG;
            // current chooses L (0)
            // prev L (0): prev did not fire R, cur fires L -> add curReach[i]
            ndpL = max(ndpL, dpL + curReach[i]);
            // prev R (1): prev fired R, cur fires L -> add bothReach[i]
            ndpL = max(ndpL, dpR + bothReach[i]);

            // current chooses R (1)
            // prev L (0): prev did not fire R, cur not firing L -> add 0
            ndpR = max(ndpR, dpL + 0);
            // prev R (1): prev fired R, cur not firing L -> add prevReach[i]
            ndpR = max(ndpR, dpR + prevReach[i]);

            dpL = ndpL; dpR = ndpR;
        }

        // final rightmost segment (index n) is covered only if last robot fires R
        long long best = max(dpL, dpR + prevReach[n]);
        long long sumAtRobots = 0;
        for (int x : robotPosWalls) sumAtRobots += x;
        best += sumAtRobots;
        return int(best);
    }
};