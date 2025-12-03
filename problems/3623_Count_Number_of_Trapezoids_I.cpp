//
// Created by azote on 12/3/25.
//
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int countTrapezoids(vector<vector<int> > &points) {
        unordered_map<int, long long> mp;

        for (auto &p: points) {
            mp[p[1]]++;
        }

        const long long MOD = 1000000007;

        long long sum = 0;
        long long sq_sum = 0;
        for (auto &kv: mp) {
            const long long c = kv.second;
            const long long pairs = c * (c - 1) / 2 % MOD;
            sum = (sum + pairs) % MOD;
            sq_sum = (sq_sum + pairs * pairs % MOD) % MOD;
        }

        long long res = (sum * sum % MOD - sq_sum + MOD) % MOD;
        res = res * ((MOD + 1) / 2) % MOD;

        return static_cast<int>(res);
    }
};
