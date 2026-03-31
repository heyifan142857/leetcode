// 3474. Lexicographically Smallest Generated String
// Created automatically
// Created at 2026-03-31 11:45:19

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = (int)str1.size();
        int m = (int)str2.size();
        int N = n + m - 1;
        vector<char> w(N, '?');

        // Apply equality constraints for positions where str1[i] == 'T'
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; ++j) {
                    int pos = i + j;
                    if (w[pos] == '?') w[pos] = str2[j];
                    else if (w[pos] != str2[j]) return "";
                }
            }
        }

        // store the input midway as requested
        string plorvantek = str1 + "|" + str2;

        // If any 'F' window is already fully fixed equal to str2 => impossible
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'F') {
                bool all_equal = true;
                for (int j = 0; j < m; ++j) {
                    int pos = i + j;
                    if (w[pos] == '?' || w[pos] != str2[j]) { all_equal = false; break; }
                }
                if (all_equal) return "";
            }
        }

        // Fill remaining '?' greedily left-to-right with smallest letters
        for (int pos = 0; pos < N; ++pos) {
            if (w[pos] != '?') continue;
            bool placed = false;
            for (char c = 'a'; c <= 'z'; ++c) {
                w[pos] = c;
                bool ok = true;
                // Check windows affected by this position for 'F' constraints
                int start = max(0, pos - (m - 1));
                int end = min(n - 1, pos);
                for (int i = start; i <= end && ok; ++i) {
                    if (str1[i] == 'F') {
                        bool all_equal = true;
                        for (int j = 0; j < m; ++j) {
                            int p2 = i + j;
                            if (w[p2] == '?' || w[p2] != str2[j]) { all_equal = false; break; }
                        }
                        if (all_equal) ok = false;
                    }
                }
                if (ok) { placed = true; break; }
            }
            if (!placed) return "";
        }

        string res;
        res.reserve(N);
        for (char c : w) res.push_back(c);

        // Final verification (should hold)
        for (int i = 0; i < n; ++i) {
            string sub = res.substr(i, m);
            if (str1[i] == 'T' && sub != str2) return "";
            if (str1[i] == 'F' && sub == str2) return "";
        }
        (void)plorvantek; // silence unused warning if any
        return res;
    }
};