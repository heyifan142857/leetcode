//
// Created by azote on 1/17/26.
//
#include <vector>
using namespace std;

class Solution {
public:
    long long largestSquareArea(vector<vector<int> > &bottomLeft, vector<vector<int> > &topRight) {
        int n = bottomLeft.size();
        long long maxArea = 0;

        // Check all pairs of rectangles
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Calculate intersection of rectangles i and j
                int left = max(bottomLeft[i][0], bottomLeft[j][0]);
                int right = min(topRight[i][0], topRight[j][0]);
                int bottom = max(bottomLeft[i][1], bottomLeft[j][1]);
                int top = min(topRight[i][1], topRight[j][1]);
                // Check if rectangles intersect
                if (left < right && bottom < top) {
                    // Calculate the side length of the largest square that fits
                    int width = right - left;
                    int height = top - bottom;
                    int side = min(width, height);

                    // Update maximum area
                    maxArea = max(maxArea, (long long) side * side);
                }
            }
        }

        return maxArea;
    }
};
