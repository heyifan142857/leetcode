//
// Created by user on 2025/7/30.
//
#include <vector>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int maxAND = 0;
        int maxLength = 0;
        int length = 0;
        for (int num:nums) {
           if(maxAND == 0){
               maxAND = num;
               length++;
               continue;
           }
           if(num < maxAND){
               if(length > maxLength){
                   maxLength = length;
               }
               length = 0;
               continue;
           }else if(num == maxAND){
               length++;
           }else{
               length = 1;
               maxAND = num;
               maxLength = 0;
           }
        }
        if(length>maxLength){
            maxLength = length;
        }
        return maxLength;
    }
};