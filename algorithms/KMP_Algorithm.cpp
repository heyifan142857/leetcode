#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 构建 LPS（Longest Proper Prefix which is also Suffix）数组。
// lps[i] 表示 pattern[0..i] 的最长相等真前缀和真后缀的长度。
vector<size_t> buildLps(const string& pattern) {
    vector<size_t> lps(pattern.size(), 0);

    for (size_t i = 1, length = 0; i < pattern.size();) {
        if (pattern[i] == pattern[length]) {
            lps[i++] = ++length;
        } else if (length > 0) {
            // 利用已经计算出的结果继续匹配，无需回退 i。
            length = lps[length - 1];
        } else {
            lps[i++] = 0;
        }
    }

    return lps;
}

// 返回 pattern 在 text 中首次出现的位置；未找到时返回 string::npos。
size_t kmpSearch(const string& text, const string& pattern) {
    if (pattern.empty()) {
        return 0;
    }

    const vector<size_t> lps = buildLps(pattern);

    for (size_t i = 0, j = 0; i < text.size();) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;

            if (j == pattern.size()) {
                return i - j;
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }

    return string::npos;
}

// 返回 pattern 在 text 中的全部匹配位置，包括重叠匹配。
vector<size_t> kmpSearchAll(const string& text, const string& pattern) {
    vector<size_t> matches;
    if (pattern.empty()) {
        return matches;
    }

    const vector<size_t> lps = buildLps(pattern);

    for (size_t i = 0, j = 0; i < text.size();) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;

            if (j == pattern.size()) {
                matches.push_back(i - j);
                j = lps[j - 1];
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }

    return matches;
}

int main() {
    const string text = "ABABDABACDABABCABAB";
    const string pattern = "ABABCABAB";

    const size_t position = kmpSearch(text, pattern);
    if (position == string::npos) {
        cout << "未找到模式串" << endl;
    } else {
        cout << "模式串首次出现的位置: " << position << endl;
    }

    const string overlappingText = "AAAAA";
    const string overlappingPattern = "AAA";
    const vector<size_t> matches = kmpSearchAll(overlappingText, overlappingPattern);

    cout << "重叠匹配的位置:";
    for (size_t index : matches) {
        cout << ' ' << index;
    }
    cout << endl;

    return 0;
}
