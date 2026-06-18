// 1344. Angle Between Hands of a Clock
// Created automatically
// Created at 2026-06-18 10:29:52

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double angleClock(int hour, int minutes) {
        double hourAngle = (hour % 12) * 30 + minutes * 0.5;
        double minuteAngle = minutes * 6;
        double angle = abs(hourAngle - minuteAngle);
        return min(angle, 360 - angle);
    }
};