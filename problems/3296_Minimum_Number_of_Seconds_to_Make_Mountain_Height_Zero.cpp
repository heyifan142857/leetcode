// 3296. Minimum Number of Seconds to Make Mountain Height Zero
// Created automatically
// Created at 2026-03-13 10:22:54

#include <bits/stdc++.h>
using namespace std;

//作者：灵茶山艾府
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        priority_queue<tuple<long long, long long, int>, vector<tuple<long long, long long, int>>, greater<>> pq;
        for (int t : workerTimes) {
            pq.emplace(t, t, t);
        }

        long long ans = 0;
        while (mountainHeight--) {
            auto [total, cur, base] = pq.top(); pq.pop();
            ans = total;
            pq.emplace(total + cur + base, cur + base, base);
        }
        return ans;
    }
};