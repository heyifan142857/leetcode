//
// Created by user on 2025/10/19.
//
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        queue<string> q;
        unordered_set<string> vis;
        string ans = s;
        q.push(s);
        vis.insert(s);

        while (!q.empty()) {
            string cur = q.front(); q.pop();
            ans = min(ans, cur);

            // 操作1：加a到奇数位
            string add = cur;
            for (int i = 1; i < add.size(); i += 2) {
                add[i] = ((add[i] - '0' + a) % 10) + '0';
            }
            if (!vis.count(add)) {
                vis.insert(add);
                q.push(add);
            }

            // 操作2：右移b位
            string rot = cur.substr(cur.size() - b) + cur.substr(0, cur.size() - b);
            if (!vis.count(rot)) {
                vis.insert(rot);
                q.push(rot);
            }
        }
        return ans;
    }
};
