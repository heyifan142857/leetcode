// 简单选择排序每轮从未排序区间中选出最小元素，并放到区间开头。
// 最好、平均和最坏时间复杂度均为 O(n^2)；
// 空间复杂度 O(1)，通常是不稳定排序。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int> &values) {
    for (size_t i = 0; i < values.size(); ++i) {
        size_t minimum = i;
        for (size_t j = i + 1; j < values.size(); ++j) {
            if (values[j] < values[minimum]) {
                minimum = j;
            }
        }
        if (minimum != i) {
            swap(values[i], values[minimum]);
        }
    }
}

int main() {
    vector<int> values = {64, 25, 12, 22, 11};
    selectionSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "简单选择排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
