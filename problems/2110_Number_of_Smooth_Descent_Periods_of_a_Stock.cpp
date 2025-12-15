//
// Created by azote on 12/15/25.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
    long long sdpCount(int len) {
        return (static_cast<long long>(len) + 1) * static_cast<long long>(len) / 2;
    }

public:
    long long getDescentPeriods(vector<int> &prices) {
        long long cnt = 0;
        vector<int> sdps;

        int curLen = 0;
        int pre = INT_MIN;

        for (const auto price: prices) {
            if (price + 1 == pre) {
                curLen++;
                pre = price;
                continue;
            }
            sdps.push_back(curLen);
            pre = price;
            curLen = 1;
        }
        if (curLen) {
            sdps.push_back(curLen);
        }

        for (const auto sdp: sdps) {
            cnt += sdpCount(sdp);
        }

        return cnt;
    }
};
