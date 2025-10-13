//
// Created by user on 2025/10/13.
//
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> hill(n, 0);

        for (int i = 1; i < n; ++i) {
            if(prices[i]>prices[i-1]){
                hill[i]++;
            }else if(prices[i]<prices[i-1]){
                hill[i]--;
            }
        }

        for (int i = n-2; i >= 0; --i) {
            if(prices[i]>prices[i+1]){
                hill[i]++;
            }else if(prices[i]<prices[i+1]){
                hill[i]--;
            }
        }

        int res = 0;
        stack<int> s;

        for (int i = 0; i < n; ++i) {
            if(hill[i]<0){
                s.push(prices[i]);
            }
            if(hill[i]>0 && !s.empty()){
                int bottom = s.top();
                res += (prices[i]-bottom);
                s.pop();
            }
        }

        return res;
    }
};