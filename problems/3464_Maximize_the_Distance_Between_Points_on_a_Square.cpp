// 3464. Maximize the Distance Between Points on a Square
// Created automatically
// Created at 2026-04-25 14:58:43

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long getPos(int side, int x, int y) {
        if (x == 0) return y;
        if (y == side) return 1LL * side + x;
        if (x == side) return 3LL * side - y;
        return 4LL * side - x;
    }

    bool canPick(const vector<long long>& pos, int k, long long dist, long long perimeter) {
        int n = pos.size();
        vector<long long> ext(2 * n);
        for (int i = 0; i < n; ++i) {
            ext[i] = pos[i];
            ext[i + n] = pos[i] + perimeter;
        }

        for (int start = 0; start < n; ++start) {
            int cur = start;
            bool ok = true;
            for (int taken = 1; taken < k; ++taken) {
                long long need = ext[cur] + dist;
                cur = lower_bound(ext.begin() + cur + 1, ext.begin() + start + n, need) - ext.begin();
                if (cur >= start + n) {
                    ok = false;
                    break;
                }
            }
            if (ok && ext[cur] - ext[start] <= perimeter - dist) {
                return true;
            }
        }
        return false;
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> pos;
        pos.reserve(points.size());
        for (const auto& p : points) {
            pos.push_back(getPos(side, p[0], p[1]));
        }
        sort(pos.begin(), pos.end());

        long long perimeter = 4LL * side;
        long long left = 0;
        long long right = 2LL * side;
        while (left < right) {
            long long mid = (left + right + 1) >> 1;
            if (canPick(pos, k, mid, perimeter)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return (int) left;
    }
};
