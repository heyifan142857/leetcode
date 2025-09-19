//
// Created by user on 2025/9/19.
//
#include <vector>
#include <string>
using namespace std;

class Spreadsheet {
    vector<vector<int>> sheet;
public:
    Spreadsheet(int rows) {
        sheet.resize(rows, vector<int>(26, 0));
    }

    void setCell(string cell, int value) {
        int y = cell[0] - 'A';
        string num = "";
        for (int i = 1; i < cell.size(); ++i) {
            num += cell[i];
        }
        int x = stoi(num);
        sheet[x-1][y] = value;
    }

    void resetCell(string cell) {
        setCell(cell, 0);
    }

    int getSheetValue(string cell) {
        int y = cell[0] - 'A';
        if(y >= 26 || y < 0){
            return stoi(cell);
        }
        string num = "";
        for (int i = 1; i < cell.size(); ++i) {
            num += cell[i];
        }
        int x = stoi(num);
        return sheet[x-1][y];
    }

    int getValue(string formula) {
        int plus = formula.find('+');
        string str1 = formula.substr(1, plus - 1);
        string str2 = formula.substr(plus+1, formula.size() - plus - 1);

        return getSheetValue(str1)+ getSheetValue(str2);
    }
};