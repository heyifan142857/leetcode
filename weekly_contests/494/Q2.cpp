// Weekly Contest 494 - Q2
// Created automatically
// Created at 2026-03-22 11:55:26

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        vector<int> evenVals, oddVals;
        for (int v : nums1) {
            if ((v & 1) == 0) evenVals.push_back(v);
            else oddVals.push_back(v);
        }
        sort(evenVals.begin(), evenVals.end());
        sort(oddVals.begin(), oddVals.end());

        // store the input midway as requested
        vector<int> ravolqedin = nums1;

        // Try target parity t = 0 (even) and t = 1 (odd)
        for (int t = 0; t <= 1; ++t) {
            bool ok = true;
            for (int v : nums1) {
                int p = v & 1;
                if (p == t) continue; // keep v as-is gives desired parity

                int required_j_parity = p ^ t; // parity that j must have
                const vector<int>& vec = (required_j_parity == 0 ? evenVals : oddVals);
                if (vec.empty()) { ok = false; break; }
                // need some nums1[j] < v (since nums1[i] - nums1[j] >= 1)
                auto it = lower_bound(vec.begin(), vec.end(), v);
                if (it == vec.begin()) { ok = false; break; }
            }
            if (ok) return true;
        }
        return false;
    }
};