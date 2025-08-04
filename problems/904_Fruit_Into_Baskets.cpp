//
// Created by user on 2025/8/4.
//

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> count; // 水果种类和数量
        int left = 0, maxLen = 0;

        for (int right = 0; right < fruits.size(); ++right) {
            count[fruits[right]]++;

            // 如果超过两个种类，就缩小窗口
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0) {
                    count.erase(fruits[left]);
                }
                ++left;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};