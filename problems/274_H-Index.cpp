//
// Created by user on 2025/10/13.
//
#include <vector>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();

        int h = n;
        while (h>0){
            int cnt = 0;
            for (auto citation: citations) {
                if(citation >= h){
                    cnt++;
                }
            }
            if(cnt>=h){
                return h;
            }
            h--;
        }
        return 0;
    }
};