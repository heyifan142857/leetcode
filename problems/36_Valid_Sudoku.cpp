//
// Created by user on 2025/8/30.
//

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
            unordered_set<char> set;
            for (int j = 0; j < 9; ++j) {
                char cur = board[i][j];
                if(cur != '.'){
                    if(set.find(cur)==set.end()){
                        set.insert(cur);
                    }else{
                        return false;
                    }
                }
            }
        }
        for (int i = 0; i < 9; ++i) {
            unordered_set<char> set;
            for (int j = 0; j < 9; ++j) {
                char cur = board[j][i];
                if(cur != '.'){
                    if(set.find(cur)==set.end()){
                        set.insert(cur);
                    }else{
                        return false;
                    }
                }
            }
        }
        for (int i = 0; i < 9; i+=3) {
            for (int j = 0; j < 9; j+=3) {
                unordered_set<char> set;
                for (int k = 0; k < 3; ++k) {
                    for (int l = 0; l < 3; ++l) {
                        char cur = board[i+k][j+l];
                        if(cur != '.'){
                            if(set.find(cur)==set.end()){
                                set.insert(cur);
                            }else{
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
};