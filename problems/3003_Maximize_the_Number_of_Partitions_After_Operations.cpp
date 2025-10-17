//
// Created by user on 2025/10/17.
//
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.size();
        if (k == 26) return 1; // 全部字符可共存，只能有 1 段

        // left[i] = 处理到 s[i-1] 的状态
        vector<vector<int>> left(n, vector<int>(3, 0));  // [段数, 当前mask, 当前不同字符数]
        int seg = 0, mask = 0, distinct = 0;
        for (int i = 0; i < n - 1; ++i) {
            int bit = 1 << (s[i] - 'a');
            if (!(mask & bit)) {
                distinct++;
                if (distinct > k) {
                    seg++;
                    mask = bit;
                    distinct = 1;
                } else {
                    mask |= bit;
                }
            }
            left[i + 1][0] = seg;
            left[i + 1][1] = mask;
            left[i + 1][2] = distinct;
        }

        // right[i] = 从 s[i+1] 到结尾的状态
        vector<vector<int>> right(n, vector<int>(3, 0));
        seg = mask = distinct = 0;
        for (int i = n - 1; i > 0; --i) {
            int bit = 1 << (s[i] - 'a');
            if (!(mask & bit)) {
                distinct++;
                if (distinct > k) {
                    seg++;
                    mask = bit;
                    distinct = 1;
                } else {
                    mask |= bit;
                }
            }
            right[i - 1][0] = seg;
            right[i - 1][1] = mask;
            right[i - 1][2] = distinct;
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            // 左右分割数相加 + 当前字符所在段
            int curSeg = left[i][0] + right[i][0] + 2;

            // 合并左右字符集合
            int combinedMask = left[i][1] | right[i][1];
            int combinedCount = __builtin_popcount(combinedMask);

            // 判断能否合并、增加或减少一段
            if (left[i][2] == k && right[i][2] == k && combinedCount < 26)
                curSeg++;  // 两边都满还能加一个新字符，多一段
            else if (combinedCount + 1 <= k)
                curSeg--;  // 修改后两边能合并，少一段

            ans = max(ans, curSeg);
        }
        return ans;
    }
};
