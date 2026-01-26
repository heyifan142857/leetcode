//
// Created by azote on 1/26/26.
//
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int> > minimumAbsDifference(vector<int> &arr) {
        ranges::sort(arr);

        int minDiff = INT_MAX;
        const int n = arr.size();

        for (int i = 1; i < n; i++) {
            minDiff = min(minDiff, arr[i] - arr[i - 1]);
        }

        vector<vector<int> > result;

        for (int i = 1; i < n; i++) {
            if (arr[i] - arr[i - 1] == minDiff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }

        return result;
    }
};
