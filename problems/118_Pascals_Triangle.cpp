//
// Created by user on 2025/8/1.
//

#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> _generate(int n, vector<vector<int>> ans = vector<vector<int>>(0)) {
        if(n <= 0){
            return ans;
        }

        vector<int> new_vec(1,1);
        if(ans.size() != 0){
            vector<int> last_vec = ans[ans.size()-1];
            for (int i = 1; i < last_vec.size(); ++i) {
                new_vec.push_back(last_vec[i-1]+last_vec[i]);
            }
            new_vec.push_back(1);
        }
        ans.push_back(new_vec);
        return _generate(n-1, ans);
    }
public:
    vector<vector<int>> generate(int numRows) {
        return _generate(numRows);
    }
};
