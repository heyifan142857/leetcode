#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        long long maximumProfit(vector<int>& prices, int k) {
            const int n = (int)prices.size();
            if (k <= 0 || n < 2) return 0LL;

            const long long NEG = LLONG_MIN / 4;

            // dp0[t]     = max profit up to current day, with t completed transactions, holding nothing
            // dpLong[t]  = max profit up to current day, with t completed transactions, holding a long position
            // dpShort[t] = max profit up to current day, with t completed transactions, holding a short position
            vector<long long> dp0(k + 1, NEG), dpLong(k + 1, NEG), dpShort(k + 1, NEG);
            dp0[0] = 0;

            for (int day = 0; day < n; ++day) {
                const long long p = prices[day];

                vector<long long> ndp0 = dp0;
                vector<long long> ndpLong = dpLong;
                vector<long long> ndpShort = dpShort;

                // Close positions (must have been opened on an earlier day).
                for (int t = 0; t < k; ++t) {
                    if (dpLong[t] != NEG) ndp0[t + 1] = max(ndp0[t + 1], dpLong[t] + p);   // sell
                    if (dpShort[t] != NEG) ndp0[t + 1] = max(ndp0[t + 1], dpShort[t] - p); // buy back
                }

                // Open positions (cannot use profits from closing on the same day).
                for (int t = 0; t <= k; ++t) {
                    if (dp0[t] == NEG) continue;
                    ndpLong[t] = max(ndpLong[t], dp0[t] - p);  // buy -> long
                    ndpShort[t] = max(ndpShort[t], dp0[t] + p); // sell -> short
                }

                dp0.swap(ndp0);
                dpLong.swap(ndpLong);
                dpShort.swap(ndpShort);
            }

            long long ans = 0;
            for (int t = 0; t <= k; ++t) ans = max(ans, dp0[t]);
            return ans;
        }
    };
