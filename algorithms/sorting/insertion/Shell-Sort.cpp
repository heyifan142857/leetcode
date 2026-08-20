// 希尔排序按逐渐缩小的增量对元素进行分组插入排序。
// 复杂度取决于增量序列；本实现使用 n/2, n/4, ..., 1：
// 最好时间复杂度 O(n log n)，最坏时间复杂度 O(n^2)，平均复杂度没有
// 与输入无关的统一紧确结论；空间复杂度 O(1)，是不稳定排序。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void shellSort(vector<int> &values) {
    for (size_t gap = values.size() / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < values.size(); ++i) {
            const int current = values[i];
            size_t position = i;
            while (position >= gap && values[position - gap] > current) {
                values[position] = values[position - gap];
                position -= gap;
            }
            values[position] = current;
        }
    }
}

int main() {
    vector<int> values = {12, 34, 54, 2, 3, 9, 8, 1};
    shellSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "希尔排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
