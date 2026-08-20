// LSD 基数排序从最低有效位开始，逐位执行稳定的计数分配。
// 时间复杂度在最好、平均和最坏情况下均为 O(d(n + r))，其中 d 为位数、
// r 为基数；空间复杂度 O(n + r)，是稳定排序。
// 本实现以字节为“位”（d = 4、r = 256），并支持全部 32 位有符号整数。

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void radixSort(vector<int> &values) {
    static_assert(sizeof(int) == sizeof(uint32_t),
                  "此示例要求 int 为 32 位");
    constexpr size_t radix = 256;
    vector<int> buffer(values.size());

    for (unsigned shift = 0; shift < 32; shift += 8) {
        array<size_t, radix> count{};

        for (int value : values) {
            // 翻转符号位，把有符号整数次序映射到无符号整数次序。
            const uint32_t orderedKey = static_cast<uint32_t>(value) ^
                                        uint32_t{0x80000000};
            ++count[(orderedKey >> shift) & 0xFFU];
        }

        size_t offset = 0;
        for (size_t &frequency : count) {
            const size_t occurrences = frequency;
            frequency = offset;
            offset += occurrences;
        }

        for (int value : values) {
            const uint32_t orderedKey = static_cast<uint32_t>(value) ^
                                        uint32_t{0x80000000};
            buffer[count[(orderedKey >> shift) & 0xFFU]++] = value;
        }
        values.swap(buffer);
    }
}

int main() {
    vector<int> values = {170,
                          45,
                          75,
                          -90,
                          -802,
                          24,
                          2,
                          66,
                          0,
                          numeric_limits<int>::min(),
                          numeric_limits<int>::max()};
    radixSort(values);
    assert(is_sorted(values.begin(), values.end()));

    cout << "基数排序: ";
    for (int value : values) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
