//
// Created by azote on 11/18/25.
//
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        vector<vector<char> > zigzag(numRows, vector<char>());
        string res;
        int direction = 1;
        int pos = 0;

        for (auto c: s) {
            zigzag[pos].push_back(c);

            if (numRows == 1) {
                continue;
            }
            if (pos + direction < 0 || pos + direction >= numRows) {
                direction = -direction;
            }

            pos += direction;
        }

        for (auto vector: zigzag) {
            for (auto c: vector) {
                res += c;
            }
        }

        return res;
    }
};
