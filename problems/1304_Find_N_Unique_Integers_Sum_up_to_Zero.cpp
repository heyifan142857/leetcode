//
// Created by user on 2025/9/7.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ans;

        for (int i = 1; i <= n/2; ++i) {
            ans.push_back(i);
            ans.push_back(-i);
        }

        if(n%2){
            ans.push_back(0);
        }

        return ans;
    }
};