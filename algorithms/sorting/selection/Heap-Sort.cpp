// 堆排序先在线性时间内建立最大堆，再反复取出堆顶最大值。
// 最好、平均和最坏时间复杂度均为 O(n log n)；
// 空间复杂度 O(1)，是不稳定排序。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void siftDown(vector<int> &values, size_t root, size_t heapSize) {
    while (root < heapSize / 2) { // 只有前半部分的节点可能拥有孩子
        size_t child = root * 2 + 1;
        if (child + 1 < heapSize && values[child] < values[child + 1]) {
            ++child;
        }
        if (values[root] >= values[child]) {
            return;
        }
        swap(values[root], values[child]);
        root = child;
    }
}

void heapSort(vector<int> &values) {
    // 从最后一个非叶节点开始，自底向上建最大堆。
    for (size_t i = values.size() / 2; i > 0; --i) {
        siftDown(values, i - 1, values.size());
    }
    for (size_t heapSize = values.size(); heapSize > 1; --heapSize) {
        swap(values.front(), values[heapSize - 1]);
        siftDown(values, 0, heapSize - 1);
    }
}

int main() {
    vector<int> values = {12, 11, 13, 5, 6, 7};
    heapSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "堆排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
