// 折半查找（二分查找）每次将有序查找区间缩小一半。
// 它要求数据按升序排列，时间复杂度为 O(log n)，空间复杂度为 O(1)。

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// 返回 target 第一次出现的下标；未找到时返回 -1。
ptrdiff_t binarySearch(const vector<int> &sortedValues, int target) {
    size_t left = 0;
    size_t right = sortedValues.size(); // 查找区间为 [left, right)

    // 找到第一个大于或等于 target 的位置。
    while (left < right) {
        const size_t middle = left + (right - left) / 2;
        if (sortedValues[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    if (left < sortedValues.size() && sortedValues[left] == target) {
        return static_cast<ptrdiff_t>(left);
    }
    return -1;
}

int main() {
    const vector<int> sortedValues = {2, 4, 7, 7, 7, 10, 13, 18, 25};

    for (int target : {7, 8}) {
        const ptrdiff_t position = binarySearch(sortedValues, target);
        if (position == -1) {
            cout << "二分查找：未找到 " << target << '\n';
        } else {
            cout << "二分查找：" << target << " 第一次出现于下标 " << position
                 << '\n';
        }
    }

    return 0;
}
