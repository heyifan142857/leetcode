//
// Created by user on 2025/10/1.
//
class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int remain = numBottles;
        int drink = numBottles;
        while (remain >= numExchange){
            int exchange = remain / numExchange;
            remain %= numExchange;
            remain += exchange;
            drink += exchange;
        }
        return drink;
    }
};