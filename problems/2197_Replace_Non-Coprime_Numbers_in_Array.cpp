//
// Created by user on 2025/9/16.
//
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> ans;
        for (auto num: nums) {
            if(ans.empty()){
                ans.push_back(num);
            } else{
                int last = ans.back();
                int GCD = gcd(last, num);
                while (GCD > 1){
                    num = lcm(last, num);
                    ans.pop_back();
                    if(!ans.empty()){
                        last = ans.back();
                    }else{
                        break;
                    }
                    GCD = gcd(last, num);
                }
                ans.push_back(num);
            }
        }
        return ans;
    }
};
