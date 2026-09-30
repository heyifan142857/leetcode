// 1111. Maximum Nesting Depth of Two Valid Parentheses Strings
// Created automatically
// Created at 2026-09-30 15:33:45

#include <vector>
#include <string>
using namespace std;

class Solution { 
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> answer;
        answer.reserve(seq.size());
        int depth = 0;

        for (char c : seq) {
            if (c == '(') {
                ++depth;
                answer.push_back(depth % 2);
            } else {
                answer.push_back(depth % 2);
                --depth;
            }
        }

        return answer;
    }
};
