//
// Created by user on 2025/9/12.
//
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Solution {
    string w;
    bool _exist(const vector<vector<char>>& board, pair<int, int> pos, int p, vector<vector<int>>& visited) {
        if(p >= w.size()){
            return true;
        }
        if(pos.first < 0 || pos.first >= board.size() ||
        pos.second < 0 || pos.second >= board[0].size() ||
        board[pos.first][pos.second] != w[p] || visited[pos.first][pos.second]){
            return false;
        }

        visited[pos.first][pos.second] = 1;

        if(_exist(board, {pos.first-1, pos.second}, p+1, visited) ||
                _exist(board, {pos.first+1, pos.second}, p+1, visited) ||
                _exist(board, {pos.first, pos.second-1}, p+1, visited) ||
                _exist(board, {pos.first, pos.second+1}, p+1, visited)){
            visited[pos.first][pos.second] = 0;
            return true;
        }

        visited[pos.first][pos.second] = 0;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        w = word;
        int m = board.size();
        int n = board[0].size();
        vector<vector<int>> visited = vector(m, vector<int>(n, 0));
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if(_exist(board, {i, j}, 0, visited)){
                    return true;
                }
            }
        }
        return false;
    }
};