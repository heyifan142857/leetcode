// 插入排序逐个取出元素，并将其插入前方已经有序的区间。
// 它实现简单且适合小规模或接近有序的数据。

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// 时间复杂度为 O(n^2)，空间复杂度为 O(1)。
void insertionSort(vector<int> &values) {
    for (size_t i = 1; i < values.size(); ++i) {
        const int current = values[i];
        size_t position = i;

        while (position > 0 && values[position - 1] > current) {
            values[position] = values[position - 1];
            --position;
        }
        values[position] = current;
    }
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
    vector<int> values = {5, 2, 4, 6, 1, 3};

    cout << "排序前: ";
    printValues(values);

    insertionSort(values);

    cout << "排序后: ";
    printValues(values);

    return 0;
}
