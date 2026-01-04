#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int totalSum = 0;
        
        for (int num : nums) {
            set<int> divisors;
            
            // Find all divisors by iterating up to sqrt(num)
            for (int i = 1; i * i <= num; i++) {
                if (num % i == 0) {
                    divisors.insert(i);
                    divisors.insert(num / i);
                }
            }
            
            // If exactly 4 divisors, sum them
            if (divisors.size() == 4) {
                for (int d : divisors) {
                    totalSum += d;
                }
            }
        }
        
        return totalSum;
    }
};