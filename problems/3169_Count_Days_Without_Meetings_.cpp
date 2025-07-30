//
// Created by user on 2025/7/24.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        vector<int> start;
        vector<int> end;
        for (vector<int> meeting: meetings) {
            start.push_back(meeting[0]);
            end.push_back(meeting[1]);
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int count = 0;

        int flag1 = 0, flag2 = 0;
        int ongoing = 0;

        for (int i = 1; i <= days; ++i) {
            while(flag1 < start.size() && start[flag1] == i){
                ongoing++;
                flag1++;
            }

            if(flag1 == start.size()){
                count += (days-end[end.size()-1]);//what can i say
                break;
            }

            if(ongoing == 0){
                count++;
            }

            while(flag2 < end.size() && end[flag2] == i){
                ongoing--;
                flag2++;
            }
        }

        return count;
    }
};