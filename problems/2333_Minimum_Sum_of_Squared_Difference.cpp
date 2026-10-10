// 2333. Minimum Sum of Squared Difference
// Created automatically
// Created at 2026-10-10 14:16:32

#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<long long> diff(n);
        long long left = 0, right = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            right = max(right, diff[i]);
        }

        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long need = 0;

            for (long long d : diff) {
                need += max(0LL, d - mid);

                if (need > k) {
                    break;
                }
            }

            if (need <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        long long x = left;
        long long need = 0;
        long long res = 0;

        for (long long d : diff) {
            need += max(0LL, d - x);

            long long v = min(d, x);
            res += v * v;
        }

        long long remain = k - need;

        if (x > 0) {
            res -= remain * (2 * x - 1);
        }

        return res;
    }
};
