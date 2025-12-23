#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();
        if (n == 0) return 0;
        
        // Sort events by start time
        sort(events.begin(), events.end());
        
        // Track the maximum value we can get with events ending at or before time t
        map<int, int> bestValue;
        int maxSoFar = 0;
        
        // First pass: build map of best value at each end time
        for (const auto& event : events) {
            int endTime = event[1];
            int value = event[2];
            maxSoFar = max(maxSoFar, value);
            bestValue[endTime] = max(bestValue[endTime], value);
        }
        
        // Propagate maximum values forward: ensure bestValue[t] = max value for events ending <= t
        int currentMax = 0;
        for (auto& pair : bestValue) {
            currentMax = max(currentMax, pair.second);
            pair.second = currentMax;
        }
        
        // Second pass: for each event, find best non-overlapping event
        int result = maxSoFar; // Best single event
        
        for (const auto& event : events) {
            int startTime = event[0];
            int value = event[2];
            
            // Find the best event that ends before this event starts
            // Events are non-overlapping if endTime < startTime
            // So we look for the best value with endTime <= startTime - 1
            auto it = bestValue.upper_bound(startTime - 1);
            if (it != bestValue.begin()) {
                --it;
                result = max(result, it->second + value);
            }
        }
        
        return result;
    }
};