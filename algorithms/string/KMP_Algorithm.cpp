// KMP 算法利用模式串的前后缀信息避免文本指针回退。
// 本示例包含 next、nextval 的构建以及字符串匹配过程。

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 构建经典 next 数组。
// 当 text[i] 与 pattern[j] 失配时，令 j = next[j]，文本指针 i 不回退。
// next[0] = -1 表示模式串已经无法继续回退，此时 i 和 j 都向后移动一位。
vector<ptrdiff_t> buildNext(const string &pattern) {
    if (pattern.empty()) {
        return {};
    }

    // 多出的最后一项 next[pattern.size()] 表示完整匹配后的回退位置，
    // 用于继续寻找重叠匹配；经典 next 数组本身是前 pattern.size() 项。
    vector<ptrdiff_t> next(pattern.size() + 1, -1);
    ptrdiff_t j = 0;
    ptrdiff_t candidate = -1;

    while (j < static_cast<ptrdiff_t>(pattern.size())) {
        if (candidate == -1 || pattern[static_cast<size_t>(j)] ==
                                   pattern[static_cast<size_t>(candidate)]) {
            ++j;
            ++candidate;
            next[static_cast<size_t>(j)] = candidate;
        } else {
            candidate = next[static_cast<size_t>(candidate)];
        }
    }

    return next;
}

// 构建优化后的 nextval 数组。
// nextval[j] 表示 pattern[j] 失配后，模式串指针 j 应回退到的位置；-1 表示
// 模式串需要从头开始匹配，同时文本串指针向后移动一位。
//
// 与普通 next 数组相比，如果回退后 pattern[j] 仍与失配前的字符相同，
// 那么该字符必然再次失配。nextval 会继续沿 next 链回退，跳过这次无效比较。
vector<ptrdiff_t> buildNextVal(const string &pattern) {
    if (pattern.empty()) {
        return {};
    }

    // 与 buildNext 相同，最后一项用于完整匹配后的回退。
    vector<ptrdiff_t> nextval(pattern.size() + 1, -1);
    size_t j = 0;
    ptrdiff_t candidate = -1;

    while (j < pattern.size()) {
        if (candidate == -1 ||
            pattern[j] == pattern[static_cast<size_t>(candidate)]) {
            ++j;
            ++candidate;

            if (j == pattern.size() ||
                pattern[j] != pattern[static_cast<size_t>(candidate)]) {
                nextval[j] = candidate;
            } else {
                // 回退后仍会比较相同字符，直接继承更早的回退位置。
                nextval[j] = nextval[static_cast<size_t>(candidate)];
            }
        } else {
            candidate = nextval[static_cast<size_t>(candidate)];
        }
    }

    return nextval;
}

// 返回 pattern 在 text 中首次出现的位置；未找到时返回 string::npos。
size_t kmpSearch(const string &text, const string &pattern) {
    if (pattern.empty()) {
        return 0;
    }

    const vector<ptrdiff_t> next = buildNext(pattern);
    size_t i = 0;
    ptrdiff_t j = 0;

    while (i < text.size() && j < static_cast<ptrdiff_t>(pattern.size())) {
        if (j == -1 || text[i] == pattern[static_cast<size_t>(j)]) {
            ++i;
            ++j;
        } else {
            j = next[static_cast<size_t>(j)];
        }
    }

    if (j == static_cast<ptrdiff_t>(pattern.size())) {
        return i - pattern.size();
    }
    return string::npos;
}

// 使用 nextval 数组返回 pattern 在 text 中首次出现的位置。
size_t kmpSearchNextVal(const string &text, const string &pattern) {
    if (pattern.empty()) {
        return 0;
    }

    const vector<ptrdiff_t> nextval = buildNextVal(pattern);
    size_t i = 0;
    ptrdiff_t j = 0;

    while (i < text.size() && j < static_cast<ptrdiff_t>(pattern.size())) {
        if (j == -1 || text[i] == pattern[static_cast<size_t>(j)]) {
            ++i;
            ++j;
        } else {
            j = nextval[static_cast<size_t>(j)];
        }
    }

    if (j == static_cast<ptrdiff_t>(pattern.size())) {
        return i - pattern.size();
    }
    return string::npos;
}

// 返回 pattern 在 text 中的全部匹配位置，包括重叠匹配。
vector<size_t> kmpSearchAll(const string &text, const string &pattern) {
    vector<size_t> matches;
    if (pattern.empty()) {
        return matches;
    }

    const vector<ptrdiff_t> next = buildNext(pattern);
    size_t i = 0;
    ptrdiff_t j = 0;

    while (i < text.size()) {
        if (j == -1 || text[i] == pattern[static_cast<size_t>(j)]) {
            ++i;
            ++j;

            if (j == static_cast<ptrdiff_t>(pattern.size())) {
                matches.push_back(i - pattern.size());
                j = next[pattern.size()];
            }
        } else {
            j = next[static_cast<size_t>(j)];
        }
    }

    return matches;
}

int main() {
    const string text = "ABABDABACDABABCABAB";
    const string pattern = "ABABCABAB";

    const size_t position = kmpSearch(text, pattern);
    if (position == string::npos) {
        cout << "未找到模式串" << '\n';
    } else {
        cout << "模式串首次出现的位置: " << position << '\n';
    }

    const vector<ptrdiff_t> next = buildNext(pattern);
    cout << "next 数组:";
    for (size_t i = 0; i < pattern.size(); ++i) {
        cout << ' ' << next[i];
    }
    cout << '\n';

    const size_t optimizedPosition = kmpSearchNextVal(text, pattern);
    cout << "nextval 优化后首次出现的位置: " << optimizedPosition << '\n';

    const vector<ptrdiff_t> nextval = buildNextVal(pattern);
    cout << "nextval 数组:";
    for (size_t i = 0; i < pattern.size(); ++i) {
        cout << ' ' << nextval[i];
    }
    cout << '\n';

    const string overlappingText = "AAAAA";
    const string overlappingPattern = "AAA";
    const vector<size_t> matches =
        kmpSearchAll(overlappingText, overlappingPattern);

    cout << "重叠匹配的位置:";
    for (size_t index : matches) {
        cout << ' ' << index;
    }
    cout << '\n';

    return 0;
}
