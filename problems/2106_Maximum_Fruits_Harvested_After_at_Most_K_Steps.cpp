//
// Created by user on 2025/8/3.
//

#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<int> pos(n), sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pos[i] = fruits[i][0];
            sum[i + 1] = sum[i] + fruits[i][1];
        }

        int res = 0;
        for (int l = 0, r = 0; l < n; ++l) {
            while (r < n) {
                int left = fruits[l][0], right = fruits[r][0];
                int dist = min(abs(startPos - left) + (right - left),
                               abs(startPos - right) + (right - left));
                if (dist > k) break;
                ++r;
            }
            res = max(res, sum[r] - sum[l]);
        }

        return res;
    }
};

