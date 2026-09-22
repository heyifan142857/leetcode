// 3525. Find X Value of Array II
// Created automatically
// Created at 2026-09-22 21:35:08

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        const int n = nums.size();
        int size = 1;
        while (size < n) {
            size *= 2;
        }

        vector<int> product(2 * size, 1 % k);
        // counts[node * k + r] counts non-empty prefixes with remainder r.
        vector<int> counts(2 * size * k, 0);
        auto pull = [&](int node) {
            const int left = 2 * node, right = left + 1;
            product[node] = 1LL * product[left] * product[right] % k;
            for (int r = 0; r < k; ++r) {
                counts[node * k + r] = counts[left * k + r];
            }
            // A longer prefix contains all of the left child and a right prefix.
            for (int r = 0; r < k; ++r) {
                const int remainder = 1LL * product[left] * r % k;
                counts[node * k + remainder] += counts[right * k + r];
            }
        };

        for (int i = 0; i < n; ++i) {
            product[size + i] = nums[i] % k;
            counts[(size + i) * k + product[size + i]] = 1;
        }
        for (int node = size - 1; node > 0; --node) {
            pull(node);
        }

        vector<int> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            const int index = query[0], value = query[1];
            const int start = query[2], target = query[3];
            nums[index] = value;
            int node = size + index;
            --counts[node * k + product[node]];
            product[node] = value % k;
            ++counts[node * k + product[node]];
            for (node /= 2; node > 0; node /= 2) {
                pull(node);
            }

            int prefixProduct = 1 % k, answer = 0;
            // Visit the suffix's segments left to right, extending its prefixes.
            auto collect = [&](auto&& self, int current, int left, int right) -> void {
                if (right <= start) {
                    return;
                }
                if (left >= start) {
                    for (int r = 0; r < k; ++r) {
                        if (1LL * prefixProduct * r % k == target) {
                            answer += counts[current * k + r];
                        }
                    }
                    prefixProduct = 1LL * prefixProduct * product[current] % k;
                    return;
                }
                const int mid = left + (right - left) / 2;
                self(self, 2 * current, left, mid);
                self(self, 2 * current + 1, mid, right);
            };
            collect(collect, 1, 0, size);
            result.push_back(answer);
        }
        return result;
    }
};
