//
// Created by user on 2025/9/9.
//
#include <deque>
using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        long long ans = 1;

        deque<pair<int, long long>> list; // day, count
        list.emplace_back(1, 1);

        for (int day = 2; day <= n; ++day) {
            while (!list.empty() && day - list.front().first >= forget) {
                ans = (ans - list.front().second + MOD) % MOD;
                list.pop_front();
            }

            long long newPeople = 0;
            for (auto &cur : list) {
                if (day - cur.first >= delay) {
                    newPeople = (newPeople + cur.second) % MOD;
                }
            }

            if (newPeople > 0) {
                list.emplace_back(day, newPeople);
                ans = (ans + newPeople) % MOD;
            }
        }

        return ans % MOD;
    }
};
