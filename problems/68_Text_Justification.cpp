//
// Created by azote on 11/29/25.
//
#include <vector>
#include <string>
using namespace std;

class Solution {
    int wordsLength(const vector<string> &words) {
        int sum = 0;
        for (const auto &w: words) sum += w.size();
        return sum;
    }

public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> res;
        vector<string> cur;
        int totalLen = 0;

        for (const string &w: words) {
            if (!cur.empty()) {
                if (totalLen + w.size() + cur.size() > maxWidth) {
                    int spaces = maxWidth - totalLen;
                    int gaps = cur.size() - 1;

                    if (gaps == 0) {
                        res.push_back(cur[0] + string(spaces, ' '));
                    } else {
                        int base = spaces / gaps;
                        int extra = spaces % gaps;
                        string line = "";
                        for (int i = 0; i < cur.size(); ++i) {
                            line += cur[i];
                            if (i < gaps) {
                                int c = base + (i < extra ? 1 : 0);
                                line.append(c, ' ');
                            }
                        }
                        res.push_back(line);
                    }

                    cur.clear();
                    totalLen = 0;
                }
            }

            cur.push_back(w);
            totalLen += w.size();
        }

        string last;
        for (int i = 0; i < cur.size(); ++i) {
            if (i) last += " ";
            last += cur[i];
        }
        last.append(maxWidth - last.size(), ' ');
        res.push_back(last);

        return res;
    }
};
