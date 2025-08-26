//
// Created by user on 2025/7/25.
//

#include <string>
using namespace std;

class Solution {
public:
    int percentageLetter(string s, char letter) {
        int len = s.length();
        if(len <= 0){
            return 0;
        }

        int count = 0;
        for (char c:s) {
            if(c == letter){
                count++;
            }
        }
        return 100 * count / len;
    }
};