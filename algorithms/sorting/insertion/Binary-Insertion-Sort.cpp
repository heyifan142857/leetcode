// 折半插入排序使用二分查找确定插入位置，再整体后移元素。
// 最好时间复杂度 O(n log n)，平均和最坏时间复杂度 O(n^2)；
// 空间复杂度 O(1)，是稳定排序。二分查找只减少比较次数，不能减少移动次数。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void binaryInsertionSort(vector<int> &values) {
    for (size_t i = 1; i < values.size(); ++i) {
        const int current = values[i];

        // upper_bound 将新元素放到相等元素之后，以保持稳定性。
        const auto position = upper_bound(values.begin(),
                                          values.begin() +
                                              static_cast<ptrdiff_t>(i),
                                          current);
        move_backward(position,
                      values.begin() + static_cast<ptrdiff_t>(i),
                      values.begin() + static_cast<ptrdiff_t>(i + 1));
        *position = current;
    }
}

int main() {
    vector<int> values = {5, 2, 4, 6, 1, 3, 2};
    binaryInsertionSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "折半插入排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
