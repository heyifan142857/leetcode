//
// Created by user on 2025/8/26.
//

#include <vector>
using namespace std;

class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
       long long t = k;
       int count = 0;
       while(t > 0){
           count++;
           t = t >> 1;
       }

       int offset = 0;
       long long flag = k;
       for (int i = count-1; i >= 0; --i) {
           if(flag == 1){
               break;
           }
           if(flag > (1LL << i)){
               if(operations[i] == 1){
                   offset++;
               }
               flag -= (1LL << i);
           }
       }
       offset %= 26;
       return (char)('a'+offset);
    }
};
