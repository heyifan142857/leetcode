//
// Created by user on 2025/7/3.
//
#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // 左子数组大小
    int n2 = right - mid;     // 右子数组大小

    // 创建临时数组
    vector<int> L(n1), R(n2);

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并两个有序数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 处理剩余元素（如果有）
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // 防止溢出
        mergeSort(arr, left, mid);      // 递归排序左半部分
        mergeSort(arr, mid + 1, right); // 递归排序右半部分
        merge(arr, left, mid, right);   // 合并两个有序子数组
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};

    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    printArray(arr);

    return 0;
}
