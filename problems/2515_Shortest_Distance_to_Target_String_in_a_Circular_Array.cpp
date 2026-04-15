// 2515. Shortest Distance to Target String in a Circular Array
// Created automatically
// Created at 2026-04-15 10:16:58

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int minDist = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (words[i] == target) {
                int dist = abs(i - startIndex);
                minDist = min(minDist, min(dist, n - dist));
            }
        }
        
        return minDist == INT_MAX ? -1 : minDist;
    }
};