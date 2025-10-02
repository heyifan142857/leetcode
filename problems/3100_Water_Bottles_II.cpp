//
// Created by user on 2025/10/2.
//
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int cnt = numBottles;

        int emptyBottle = numBottles;

        while (emptyBottle/numExchange){
            emptyBottle = emptyBottle - numExchange + 1;
            cnt++;
            numExchange++;
        }

        return cnt;
    }
};