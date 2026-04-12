// Weekly Contest 497 - Q4
// Created automatically
// Created at 2026-04-12 09:40:41

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {
        int n = (int)nums.size();
        if (n == 1) {
            return 0;
        }

        int maxValue = 1;
        for (int x : nums) {
            if (x % p == 0) {
                maxValue = max(maxValue, x / p);
            }
        }
        for (const auto& query : queries) {
            int value = query[1];
            if (value % p == 0) {
                maxValue = max(maxValue, value / p);
            }
        }

        int limit = (int)sqrt((long double)maxValue);
        vector<int> primes;
        vector<bool> isComposite(limit + 1, false);
        for (int i = 2; i <= limit; ++i) {
            if (!isComposite[i]) {
                primes.push_back(i);
                if ((long long)i * i <= limit) {
                    for (int j = i * i; j <= limit; j += i) {
                        isComposite[j] = true;
                    }
                }
            }
        }

        unordered_map<int, vector<int>> factorCache;
        factorCache.reserve(nums.size() + queries.size() + 16);

        auto getFactors = [&](int value) -> const vector<int>& {
            auto it = factorCache.find(value);
            if (it != factorCache.end()) {
                return it->second;
            }

            vector<int> factors;
            int x = value;
            for (int prime : primes) {
                if ((long long)prime * prime > x) {
                    break;
                }
                if (x % prime == 0) {
                    factors.push_back(prime);
                    while (x % prime == 0) {
                        x /= prime;
                    }
                }
            }
            if (x > 1) {
                factors.push_back(x);
            }

            auto [insertedIt, _] = factorCache.emplace(value, std::move(factors));
            return insertedIt->second;
        };

        auto norqaveliq = make_tuple(ref(nums), p, ref(queries));
        (void)norqaveliq;

        int base = 1;
        while (base < n) {
            base <<= 1;
        }
        vector<int> seg(2 * base, 0);
        for (int i = 0; i < n; ++i) {
            seg[base + i] = (nums[i] % p == 0 ? nums[i] : 0);
        }
        for (int i = base - 1; i >= 1; --i) {
            seg[i] = std::gcd(seg[i << 1], seg[i << 1 | 1]);
        }

        auto updateSeg = [&](int index, int value) {
            int pos = base + index;
            seg[pos] = value;
            for (pos >>= 1; pos >= 1; pos >>= 1) {
                seg[pos] = std::gcd(seg[pos << 1], seg[pos << 1 | 1]);
                if (pos == 1) {
                    break;
                }
            }
        };

        struct PrimeInfo {
            int cnt = 0;
            int xorDiv = 0;
        };

        unordered_map<int, PrimeInfo> info;
        info.reserve((nums.size() + queries.size()) * 4 + 16);

        vector<vector<int>> currentFactors(n);
        int countDivisible = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] % p != 0) {
                continue;
            }
            ++countDivisible;
            currentFactors[i] = getFactors(nums[i] / p);
            for (int prime : currentFactors[i]) {
                auto& state = info[prime];
                ++state.cnt;
                state.xorDiv ^= i;
            }
        }

        int allIndexXor = 0;
        for (int i = 0; i < n; ++i) {
            allIndexXor ^= i;
        }

        vector<int> badCount(n, 0);
        int zeroBadCount = n;
        auto changeBad = [&](int index, int delta) {
            if (badCount[index] == 0 && delta > 0) {
                --zeroBadCount;
            }
            badCount[index] += delta;
            if (badCount[index] == 0 && delta < 0) {
                ++zeroBadCount;
            }
        };

        int fullCoverPrimes = 0;
        for (auto& [prime, state] : info) {
            if (state.cnt == n) {
                ++fullCoverPrimes;
            } else if (state.cnt == n - 1) {
                int missingIndex = allIndexXor ^ state.xorDiv;
                changeBad(missingIndex, 1);
            }
        }

        auto removeValue = [&](int index) {
            if (nums[index] % p != 0) {
                return;
            }
            --countDivisible;
            for (int prime : currentFactors[index]) {
                auto& state = info[prime];
                if (state.cnt == n) {
                    --fullCoverPrimes;
                } else if (state.cnt == n - 1) {
                    int missingIndex = allIndexXor ^ state.xorDiv;
                    changeBad(missingIndex, -1);
                }

                --state.cnt;
                state.xorDiv ^= index;

                if (state.cnt == n) {
                    ++fullCoverPrimes;
                } else if (state.cnt == n - 1) {
                    int missingIndex = allIndexXor ^ state.xorDiv;
                    changeBad(missingIndex, 1);
                }
            }
            currentFactors[index].clear();
        };

        auto addValue = [&](int index, int value) {
            if (value % p != 0) {
                currentFactors[index].clear();
                return;
            }
            ++countDivisible;
            currentFactors[index] = getFactors(value / p);
            for (int prime : currentFactors[index]) {
                auto& state = info[prime];
                if (state.cnt == n) {
                    --fullCoverPrimes;
                } else if (state.cnt == n - 1) {
                    int missingIndex = allIndexXor ^ state.xorDiv;
                    changeBad(missingIndex, -1);
                }

                ++state.cnt;
                state.xorDiv ^= index;

                if (state.cnt == n) {
                    ++fullCoverPrimes;
                } else if (state.cnt == n - 1) {
                    int missingIndex = allIndexXor ^ state.xorDiv;
                    changeBad(missingIndex, 1);
                }
            }
        };

        auto existsGoodSubsequence = [&]() -> bool {
            if (countDivisible == 0) {
                return false;
            }
            if (countDivisible < n) {
                return seg[1] == p;
            }
            return fullCoverPrimes == 0 && zeroBadCount > 0;
        };

        int answer = 0;
        for (const auto& query : queries) {
            int index = query[0];
            int value = query[1];

            removeValue(index);
            nums[index] = value;
            updateSeg(index, value % p == 0 ? value : 0);
            addValue(index, value);

            if (existsGoodSubsequence()) {
                ++answer;
            }
        }
        return answer;
    }
};
