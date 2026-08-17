// 3348. Smallest Divisible Digit Product II
// Created automatically
// Created at 2026-08-07 14:12:05

#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <string>
#include <vector>
using namespace std;

class Solution {
    struct Need {
        int two = 0;
        int three = 0;
        int five = 0;
        int seven = 0;
    };

    // primeCount[d] stores the exponents of 2, 3, 5 and 7 in digit d.
    static constexpr int primeCount[10][4] = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {2, 0, 0, 0},
        {0, 0, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 1}, {3, 0, 0, 0}, {0, 2, 0, 0}};

    vector<vector<int>> minDigits23;

    Need useDigit(Need need, int digit) const {
        need.two = max(0, need.two - primeCount[digit][0]);
        need.three = max(0, need.three - primeCount[digit][1]);
        need.five = max(0, need.five - primeCount[digit][2]);
        need.seven = max(0, need.seven - primeCount[digit][3]);
        return need;
    }

    bool canFill(const Need &need, int positions) const {
        return need.five + need.seven + minDigits23[need.two][need.three] <=
               positions;
    }

    string smallestSuffix(Need need, int length) const {
        string suffix;
        suffix.reserve(length);

        for (int i = 0; i < length; ++i) {
            int positionsLeft = length - i - 1;
            for (int digit = 1; digit <= 9; ++digit) {
                Need next = useDigit(need, digit);
                if (canFill(next, positionsLeft)) {
                    suffix.push_back(char('0' + digit));
                    need = next;
                    break;
                }
            }
        }
        return suffix;
    }

public:
    string smallestNumber(string num, long long t) {
        Need target;
        long long remainingT = t;
        const int primes[4] = {2, 3, 5, 7};
        int *exponents[4] = {&target.two, &target.three, &target.five,
                             &target.seven};

        for (int i = 0; i < 4; ++i) {
            while (remainingT % primes[i] == 0) {
                ++*exponents[i];
                remainingT /= primes[i];
            }
        }
        if (remainingT != 1) {
            return "-1";
        }

        // Only digit 6 contains both 2 and 3.  If we use sixCount copies
        // of it, the remaining exponents are covered optimally by 8 and 9.
        minDigits23.assign(target.two + 1,
                           vector<int>(target.three + 1, INT_MAX));
        for (int two = 0; two <= target.two; ++two) {
            for (int three = 0; three <= target.three; ++three) {
                for (int sixCount = 0; sixCount <= min(two, three);
                     ++sixCount) {
                    int count = sixCount + (two - sixCount + 2) / 3 +
                                (three - sixCount + 1) / 2;
                    minDigits23[two][three] =
                        min(minDigits23[two][three], count);
                }
            }
        }

        int n = num.size();
        vector<Need> prefixNeed(n + 1);
        prefixNeed[0] = target;

        int firstZero = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                firstZero = i;
                break;
            }
            prefixNeed[i + 1] = useDigit(prefixNeed[i], num[i] - '0');
        }

        if (firstZero == n && canFill(prefixNeed[n], 0)) {
            return num;
        }

        // Keep the longest possible prefix equal to num.  At the first
        // changed position, try the smallest larger digit, then complete
        // the suffix lexicographically.
        int lastChangePosition = min(firstZero, n - 1);
        for (int i = lastChangePosition; i >= 0; --i) {
            for (int digit = num[i] - '0' + 1; digit <= 9; ++digit) {
                Need need = useDigit(prefixNeed[i], digit);
                int suffixLength = n - i - 1;
                if (!canFill(need, suffixLength)) {
                    continue;
                }

                string answer = num.substr(0, i);
                answer.push_back(char('0' + digit));
                answer += smallestSuffix(need, suffixLength);
                return answer;
            }
        }

        // Every number with more digits is greater than num.  Extra places
        // can always be padded with digit 1.
        int requiredDigits =
            target.five + target.seven + minDigits23[target.two][target.three];
        int answerLength = max(n + 1, requiredDigits);
        return smallestSuffix(target, answerLength);
    }
};
