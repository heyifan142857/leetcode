//
// Created by azote on 11/25/25.
//
#include <unordered_set>

class Solution {
public:
    int smallestRepunitDivByK(int k) {
        int len = 1;
        std::unordered_set<int> st;
        int resid = 1 % k;

        while (resid) {
            if (st.contains(resid)) {
                return -1;
            }
            st.insert(resid);
            resid = (resid * 10 + 1) % k;
            len++;
        }
        return len;
    }
};
