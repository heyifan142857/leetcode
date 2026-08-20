// 快速排序选择枢轴并把序列划分为两部分，再递归排序。
// 最好和平均时间复杂度 O(n log n)，划分极不均衡时最坏为 O(n^2)；
// 递归栈平均 O(log n)、最坏 O(n)，是不稳定排序。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// 使用末尾元素作为枢轴，返回枢轴最终位置。
size_t partition(vector<int> &values, size_t left, size_t right) {
    const int pivot = values[right - 1];
    size_t boundary = left;
    for (size_t i = left; i + 1 < right; ++i) {
        if (values[i] < pivot) {
            swap(values[boundary], values[i]);
            ++boundary;
        }
    }
    swap(values[boundary], values[right - 1]);
    return boundary;
}

void quickSortRange(vector<int> &values, size_t left, size_t right) {
    if (right - left <= 1) {
        return;
    }
    const size_t pivot = partition(values, left, right);
    quickSortRange(values, left, pivot);
    quickSortRange(values, pivot + 1, right);
}

void quickSort(vector<int> &values) {
    quickSortRange(values, 0, values.size());
}

int main() {
    vector<int> values = {10, 7, 8, 9, 1, 5, 7};
    quickSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "快速排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
