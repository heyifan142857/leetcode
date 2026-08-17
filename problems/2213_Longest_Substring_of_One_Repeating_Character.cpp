// 2213. Longest Substring of One Repeating Character
// Created automatically
// Created at 2026-08-13 19:37:00

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Solution {
    struct Node {
        int len = 0;
        int prefix = 0;
        int suffix = 0;
        int best = 0;
        char leftChar = 0;
        char rightChar = 0;
    };

    vector<Node> tree;
    string current;

    Node merge(const Node &left, const Node &right) {
        if (left.len == 0)
            return right;
        if (right.len == 0)
            return left;

        Node result;
        result.len = left.len + right.len;
        result.leftChar = left.leftChar;
        result.rightChar = right.rightChar;
        result.prefix = left.prefix;
        result.suffix = right.suffix;
        result.best = max(left.best, right.best);

        if (left.rightChar == right.leftChar) {
            result.best = max(result.best, left.suffix + right.prefix);

            if (left.prefix == left.len) {
                result.prefix = left.len + right.prefix;
            }
            if (right.suffix == right.len) {
                result.suffix = right.len + left.suffix;
            }
        }

        return result;
    }

    void build(int node, int left, int right) {
        if (left == right) {
            tree[node] = {1, 1, 1, 1, current[left], current[left]};
            return;
        }

        int middle = left + (right - left) / 2;
        build(node * 2, left, middle);
        build(node * 2 + 1, middle + 1, right);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int left, int right, int index, char character) {
        if (left == right) {
            tree[node] = {1, 1, 1, 1, character, character};
            return;
        }

        int middle = left + (right - left) / 2;
        if (index <= middle) {
            update(node * 2, left, middle, index, character);
        } else {
            update(node * 2 + 1, middle + 1, right, index, character);
        }
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int> &queryIndices) {
        current = move(s);
        int n = current.size();
        tree.assign(n * 4, Node{});
        build(1, 0, n - 1);

        vector<int> answer;
        answer.reserve(queryIndices.size());

        for (int i = 0; i < static_cast<int>(queryIndices.size()); ++i) {
            int index = queryIndices[i];
            char character = queryCharacters[i];

            if (current[index] != character) {
                current[index] = character;
                update(1, 0, n - 1, index, character);
            }
            answer.push_back(tree[1].best);
        }

        return answer;
    }
};
