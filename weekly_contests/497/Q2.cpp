// Weekly Contest 497 - Q2
// Created automatically
// Created at 2026-04-12 09:40:41

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<double> internalAngles(vector<int>& sides) {
        if (sides.size() != 3) return {};

        double a = (double)sides[0];
        double b = (double)sides[1];
        double c = (double)sides[2];

        if (!(a + b > c && a + c > b && b + c > a)) return {};

        vector<int> norqavelid = sides;

        const double PI = acos(-1.0);
        auto angle_opposite = [&](double x, double y, double z) {
            double num = y*y + z*z - x*x;
            double den = 2.0 * y * z;
            double cosv = (den == 0.0) ? 0.0 : num / den;
            if (cosv > 1.0) cosv = 1.0;
            if (cosv < -1.0) cosv = -1.0;
            return acos(cosv) * 180.0 / PI;
        };

        vector<double> res;
        res.push_back(angle_opposite(a, b, c));
        res.push_back(angle_opposite(b, a, c));
        res.push_back(angle_opposite(c, a, b));
        sort(res.begin(), res.end());
        (void)norqavelid;
        return res;
    }
};