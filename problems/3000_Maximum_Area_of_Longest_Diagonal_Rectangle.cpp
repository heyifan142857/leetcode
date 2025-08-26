//
// Created by user on 2025/8/26.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int max_diagonal = 0;
        int max_area = 0;

        for (auto dimension: dimensions){
            int cur_diagonal = dimension[0]*dimension[0] + dimension[1]*dimension[1];
            if(cur_diagonal >= max_diagonal){
                int cur_area = dimension[0]*dimension[1];
                if(cur_diagonal == max_diagonal){
                    max_area = max(max_area, cur_area);
                }else{
                    max_diagonal = cur_diagonal;
                    max_area = cur_area;
                }
            }
        }
        return max_area;
    }
};