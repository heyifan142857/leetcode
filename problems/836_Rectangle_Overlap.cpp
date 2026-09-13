// 836. Rectangle Overlap
// Created automatically
// Created at 2026-09-14 02:05:34

#include <vector>
using namespace std;

class Solution {
public:
    bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2) {
        if (rec1[2] > rec2[0] && rec1[3] > rec2[1] && rec1[0] < rec2[2] &&
            rec1[1] < rec2[3]) {
            return true;
        }
        return false;
    }
};
