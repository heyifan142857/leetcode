// 835. Image Overlap
// Created automatically
// Created at 2026-09-13 22:16:59

#include <algorithm>
#include <map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>> &img1, vector<vector<int>> &img2) {
        int n = img1.size();

        map<pair<int, int>, int> cnt;
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 0) continue;

                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        if (img2[k][l] == 0) continue;

                        int dr = k - i;
                        int dc = l - j;

                        res = max(res, ++cnt[make_pair(dr, dc)]);
                    }
                }
            }
        }
        return res;
    }
};
