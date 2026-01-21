//
// Created by azote on 1/21/26.
//
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> minBitwiseArray(vector<int> &nums) {
        vector<int> ans;
        for (const auto num: nums) {
            if (num % 2 == 0) {
                // x OR (x+1) is always odd, so even numbers have no solution
                ans.push_back(-1);
            } else {
                // For odd n, find minimum x such that x OR (x+1) == n
                // x OR (x+1) fills all trailing zeros in x with ones
                
                // Count trailing ones in n
                int temp = num;
                int trailing_ones = 0;
                while (temp & 1) {
                    trailing_ones++;
                    temp >>= 1;
                }
                
                if (temp == 0) {
                    // n is all ones (like 7 = 111, 15 = 1111)
                    // For n = 2^k - 1, x = 2^(k-1) - 1 = n / 2
                    // Example: n = 7 (111), x = 3 (011): 3 OR 4 = 7
                    ans.push_back(num / 2);
                } else {
                    // n has k trailing ones, followed by a 0-bit
                    // x should have k-1 trailing ones, then 0, then same upper bits as n
                    // Formula: keep upper bits, set trailing k bits to: (2^(k-1) - 1)
                    int mask = (1 << trailing_ones) - 1; // mask for trailing k bits
                    int x = (num & ~mask) | ((1 << (trailing_ones - 1)) - 1);
                    
                    // Verify the result
                    if ((x | (x + 1)) == num) {
                        ans.push_back(x);
                    } else {
                        // Fallback: search for minimum x (shouldn't happen with correct formula)
                        int min_x = -1;
                        for (int candidate = 0; candidate < num; candidate++) {
                            if ((candidate | (candidate + 1)) == num) {
                                min_x = candidate;
                                break;
                            }
                        }
                        ans.push_back(min_x);
                    }
                }
            }
        }
        return ans;
    }
};
