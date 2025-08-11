//
// Created by user on 2025/8/11.
//

#include <vector>
using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> powers;
        int d = n;
        int rate = 1;
        while (d > 0){
            int t = d >> 1;
            int diff = d - (t << 1);
            if(diff != 0){
                powers.push_back(rate);
            }
            d = t;
            rate *= 2;
        }
        vector<int> ans;
        for (auto query: queries) {
            long long mul = 1;
            for (int i = query[0]; i <= query[1]; ++i) {
                mul = (mul * powers[i]) % MOD;
            }
            ans.push_back((int)mul);
        }
        return ans;
    }
};
