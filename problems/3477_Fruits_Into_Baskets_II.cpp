//
// Created by user on 2025/8/5.
//

#include <vector>
using namespace std;

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        int sum = 0;
        vector<bool> fruit_placed(n, false);

        for (int i = 0; i < n; ++i) {
            bool placed = false;
            for (int j = 0; j < n; ++j) {
                if(fruit_placed[j]){
                    continue;
                }
                if(baskets[j]>=fruits[i]){
                    fruit_placed[j] = true;
                    placed = true;
                    break;
                }
            }
            if(!placed){
                sum++;
            }
        }
        return sum;
    }
};