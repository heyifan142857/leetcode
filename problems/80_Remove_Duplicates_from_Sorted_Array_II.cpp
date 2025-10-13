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
            int cnt = 1;
            while (next < n){
                if(nums[fast] == nums[next]){
                    next++;
                    cnt++;
                }else{
                    break;
                }
            }
            swap(nums[fast], nums[slow]);
            if(cnt>1){
                swap(nums[fast+1], nums[slow+1]);
                slow++;
            }
            slow++;
            fast = next;
        }
        return slow;
    }
};