//
// Created by user on 2025/7/31.
//

#include <vector>
using namespace std;

class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived) {
        int n = derived.size();
        vector<int> ini_derived(n, -1);
        ini_derived[0] = 0;
        for (int i = 1; i < n; ++i) {
            ini_derived[i] = ini_derived[i-1] ^ derived[i-1];
        }
        if((ini_derived[0] ^ ini_derived[n-1]) == derived[n-1]){
            return true;
        } else{
            return false;
        }
    }
};