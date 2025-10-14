//
// Created by user on 2025/10/14.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int lowest = INT_MAX;
        int lowest_index = -1;
        vector<int> prefix(n, 0);

        for (int i = 0; i < n; ++i) {
            prefix[i] = ((i==0)?0:prefix[i-1])+(gas[i] - cost[i]);
            if(prefix[i]<lowest){
                lowest = prefix[i];
                lowest_index = i;
            }
        }

        if(prefix.back()<0){
            return -1;
        }

        return (lowest_index+1)%n;
    }
};
