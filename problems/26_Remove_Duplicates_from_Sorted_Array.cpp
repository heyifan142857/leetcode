//
// Created by user on 2025/10/13.
//
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();

        int fast = 0;
        int slow = 0;

        while (fast < n){
            int next = fast+1;
            while (next < n){
                if(nums[fast] == nums[next]){
                    next++;
                }else{
                    break;
                }
            }
            swap(nums[fast], nums[slow]);
            slow++;
            fast = next;
        }
        return slow;
    }
};