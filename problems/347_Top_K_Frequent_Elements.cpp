//
// Created by user on 2025/8/30.
//

#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> frequency;
        for (auto num : nums) {
            frequency[num]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

        for (auto& elem : frequency) {
            min_heap.push({elem.second, elem.first});
            if (min_heap.size() > k) {
                min_heap.pop();
            }
        }

        vector<int> result;
        while (!min_heap.empty()) {
            result.push_back(min_heap.top().second);
            min_heap.pop();
        }

        return result;
    }
};