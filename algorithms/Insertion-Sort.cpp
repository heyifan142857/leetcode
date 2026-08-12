// 插入排序逐个取出元素，并将其插入前方已经有序的区间。
// 它实现简单且适合小规模或接近有序的数据。

#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {5, 2, 4, 6, 1, 3};

    printArray(arr);

    insertionSort(arr);

    printArray(arr);

    return 0;
}
