// 冒泡排序重复比较相邻元素，将较大元素逐步交换到末尾。
// 使用提前退出优化后，最好时间复杂度 O(n)，平均和最坏 O(n^2)；
// 空间复杂度 O(1)，是稳定排序。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &values) {
    for (size_t unsorted = values.size(); unsorted > 1; --unsorted) {
        bool exchanged = false;
        for (size_t i = 1; i < unsorted; ++i) {
            if (values[i - 1] > values[i]) {
                swap(values[i - 1], values[i]);
                exchanged = true;
            }
        }
        if (!exchanged) {
            return;
        }
    }
}

int main() {
    vector<int> values = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "冒泡排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
