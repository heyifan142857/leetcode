//
// Created by user on 2025/10/20.
//
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int val = 0;

        for (auto operate: operations) {
            if(operate == "X++" || operate == "++X"){
                val++;
            }else{
                val--;
            }
        }

        return val;
    }
};