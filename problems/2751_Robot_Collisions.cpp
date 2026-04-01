// 2751. Robot Collisions
// Created automatically
// Created at 2026-04-01 10:02:49

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = (int)positions.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        vector<int> curHealth = healths;
        vector<int> st;

        for (int idx : order) {
            if (directions[idx] == 'R') {
                st.push_back(idx);
                continue;
            }

            while (!st.empty() && curHealth[idx] > 0) {
                int rightIdx = st.back();

                if (curHealth[rightIdx] < curHealth[idx]) {
                    st.pop_back();
                    curHealth[idx]--;
                    curHealth[rightIdx] = 0;
                } else if (curHealth[rightIdx] > curHealth[idx]) {
                    curHealth[rightIdx]--;
                    curHealth[idx] = 0;
                } else {
                    st.pop_back();
                    curHealth[rightIdx] = 0;
                    curHealth[idx] = 0;
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (curHealth[i] > 0) ans.push_back(curHealth[i]);
        }
        return ans;
    }
};
