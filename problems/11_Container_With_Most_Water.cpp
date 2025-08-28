//
// Created by user on 2025/8/28.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        int left = 0;
        int right = height.size()-1;

        while (left != right){
            int cur_area = min(height[left], height[right]) * (right - left);
            if(cur_area > max_area){
                max_area = cur_area;
            }
            if(height[left] >= height[right]){
                right--;
            }else{
                left++;
            }
        }


        return max_area;
    }
};