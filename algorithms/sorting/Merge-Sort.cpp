// 归并排序将序列递归拆分，再合并两个已经有序的子序列。
// 它的时间复杂度稳定为 O(n log n)，但需要额外存储空间。

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// 合并 [left, middle) 和 [middle, right) 两个有序区间。
void mergeRanges(vector<int> &values, size_t left, size_t middle,
                 size_t right) {
    const vector<int> leftValues(values.begin() + static_cast<ptrdiff_t>(left),
                                 values.begin() +
                                     static_cast<ptrdiff_t>(middle));
    const vector<int> rightValues(
        values.begin() + static_cast<ptrdiff_t>(middle),
        values.begin() + static_cast<ptrdiff_t>(right));

    size_t leftIndex = 0;
    size_t rightIndex = 0;
    size_t destination = left;

    while (leftIndex < leftValues.size() && rightIndex < rightValues.size()) {
        if (leftValues[leftIndex] <= rightValues[rightIndex]) {
            values[destination++] = leftValues[leftIndex++];
        } else {
            values[destination++] = rightValues[rightIndex++];
        }
    }

    while (leftIndex < leftValues.size()) {
        values[destination++] = leftValues[leftIndex++];
    }
    while (rightIndex < rightValues.size()) {
        values[destination++] = rightValues[rightIndex++];
    }
}

void mergeSortRange(vector<int> &values, size_t left, size_t right) {
    if (right - left <= 1) {
        return;
    }

    const size_t middle = left + (right - left) / 2;
    mergeSortRange(values, left, middle);
    mergeSortRange(values, middle, right);
    mergeRanges(values, left, middle, right);
}

// 时间复杂度为 O(n log n)，空间复杂度为 O(n)。
void mergeSort(vector<int> &values) {
    mergeSortRange(values, 0, values.size());
}

void printValues(const vector<int> &values) {
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << values[i];
    }
    cout << '\n';
}

int main() {
    vector<int> values = {12, 11, 13, 5, 6, 7};

    cout << "排序前: ";
    printValues(values);

    mergeSort(values);

    cout << "排序后: ";
    printValues(values);

    return 0;
}
