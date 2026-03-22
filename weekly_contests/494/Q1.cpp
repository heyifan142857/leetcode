// Weekly Contest 494 - Q1
// Created automatically
// Created at 2026-03-22 11:55:26

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        // If nums1[i] is already odd, keep it.
        // If nums1[i] is even, subtract any odd nums1[j] to get an odd number.
        // Therefore:
        // - if there is at least one odd element, we can make the whole array odd;
        // - otherwise every element is already even, so we can keep the whole array even.
        (void)nums1;
        return true;
    }
};
