// 1594. Maximum Non Negative Product in a Matrix
// Created automatically
// Created at 2026-03-23 16:24:39

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        const long long MOD = 1000000007LL;
        int m = grid.size();
        int n = grid[0].size();

        struct State {
            bool valid = false;
            bool isZero = false;
            bool isNeg = false; // true if negative
            long double logAbs = -INFINITY; // log of absolute value
            long long modAbs = 0; // absolute value modulo MOD
        };

        auto better = [&](const State &a, const State &b)->bool {
            // return true if a > b (numerically)
            if (!a.valid) return false;
            if (!b.valid) return true;
            if (a.isZero) {
                if (b.isZero) return false;
                return b.isNeg; // zero > negative, zero < positive
            }
            if (b.isZero) {
                return !a.isNeg; // positive > zero, negative < zero
            }
            if (a.isNeg == b.isNeg) {
                if (!a.isNeg) return a.logAbs > b.logAbs; // larger positive
                return a.logAbs < b.logAbs; // for negatives, smaller abs is larger numerically
            }
            return !a.isNeg; // if a positive and b negative, a > b
        };

        auto worse = [&](const State &a, const State &b)->bool {
            // return true if a < b (numerically)
            if (!a.valid) return false;
            if (!b.valid) return true;
            if (a.isZero) {
                if (b.isZero) return false;
                return b.isNeg == false; // zero < positive, zero > negative
            }
            if (b.isZero) {
                return a.isNeg; // negative < zero, positive > zero
            }
            if (a.isNeg == b.isNeg) {
                if (a.isNeg) return a.logAbs > b.logAbs; // both negative: larger abs -> more negative -> smaller
                return a.logAbs < b.logAbs; // both positive: smaller abs -> smaller
            }
            return a.isNeg; // if a negative and b positive, a < b
        };

        vector<vector<State>> dpMax(m, vector<State>(n)), dpMin(m, vector<State>(n));

        auto makeStateFromValue = [&](int v)->State{
            State s; s.valid = true;
            if (v == 0) { s.isZero = true; s.isNeg = false; s.logAbs = -INFINITY; s.modAbs = 0; }
            else { s.isZero = false; s.isNeg = (v < 0); s.logAbs = logl((long double)llabs((long long)v)); s.modAbs = (llabs((long long)v)) % MOD; }
            return s;
        };

        // initialize (0,0)
        State init = makeStateFromValue(grid[0][0]);
        dpMax[0][0] = dpMin[0][0] = init;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                State bestMax, bestMin;

                auto processPred = [&](const State &pred) {
                    if (!pred.valid) return;
                    int v = grid[i][j];
                    State cand; cand.valid = true;
                    if (pred.isZero || v == 0) {
                        cand.isZero = true; cand.isNeg = false; cand.logAbs = -INFINITY; cand.modAbs = 0;
                    } else {
                        cand.isZero = false;
                        cand.isNeg = pred.isNeg ^ (v < 0);
                        cand.logAbs = pred.logAbs + logl((long double)llabs((long long)v));
                        cand.modAbs = (pred.modAbs * (llabs((long long)v) % MOD)) % MOD;
                    }

                    if (!bestMax.valid || better(cand, bestMax)) bestMax = cand;
                    if (!bestMin.valid || worse(cand, bestMin)) bestMin = cand;
                };

                if (i > 0) {
                    processPred(dpMax[i-1][j]);
                    processPred(dpMin[i-1][j]);
                }
                if (j > 0) {
                    processPred(dpMax[i][j-1]);
                    processPred(dpMin[i][j-1]);
                }

                dpMax[i][j] = bestMax;
                dpMin[i][j] = bestMin;
            }
        }

        State &res = dpMax[m-1][n-1];
        if (!res.valid) return -1;
        if (res.isZero) return 0;
        if (res.isNeg) return -1;
        return (int)(res.modAbs % MOD);
    }
};