// 顺序查找从序列开头逐个比较元素，直到找到目标值。
// 它不要求数据有序，时间复杂度为 O(n)，空间复杂度为 O(1)。

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// 返回 target 第一次出现的下标；未找到时返回 -1。
ptrdiff_t sequentialSearch(const vector<int> &values, int target) {
    for (size_t i = 0; i < values.size(); ++i) {
        if (values[i] == target) {
            return static_cast<ptrdiff_t>(i);
        }
    }
    return -1;
}

int main() {
    const vector<int> values = {18, 5, 12, 7, 9, 21, 3};

    for (int target : {9, 10}) {
        const ptrdiff_t position = sequentialSearch(values, target);
        if (position == -1) {
            cout << "顺序查找：未找到 " << target << '\n';
        } else {
            cout << "顺序查找：" << target << " 位于下标 " << position << '\n';
        }
    }

    return 0;
}
