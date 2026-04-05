// 657. Robot Return to Origin
// Created automatically
// Created at 2026-04-05 17:30:20

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0, y = 0;

        for (char move : moves) {
            if (move == 'R') ++x;
            else if (move == 'L') --x;
            else if (move == 'U') ++y;
            else if (move == 'D') --y;
        }

        return x == 0 && y == 0;
    }
};
