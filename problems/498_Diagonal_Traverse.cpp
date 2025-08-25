//
// Created by user on 2025/8/25.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        vector<pair<int, int>> directions = {make_pair(-1, 1), make_pair(1, -1)};
        int direction = 0;

        vector<int> ans;

        pair<int, int> pos = make_pair(0, 0);

        int total = 0;

        while (total <= m+n-2) {
            ans.push_back(mat[pos.first][pos.second]);
            pair<int, int> newPos = make_pair(pos.first+directions[direction].first, pos.second+directions[direction].second);
            if(newPos.first<0 || newPos.first>=m || newPos.second<0 || newPos.second >= n){
                //newPos=
                if(pos.first == 0 && pos.second < n-1){
                    newPos = make_pair(0, pos.second+1);
                }else if(pos.second == n-1){
                    newPos = make_pair(pos.first+1, n-1);
                }else if(pos.second == 0 && pos.first < m-1){
                    newPos = make_pair(pos.first+1, 0);
                }else{
                    newPos = make_pair(m-1, pos.second+1);
                }
                total++;
                direction = (direction+1)%2;
            }
            pos = newPos;
        }

        return ans;
    }
};