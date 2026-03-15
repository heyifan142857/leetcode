// 1622. Fancy Sequence
// Created automatically
// Created at 2026-03-15 16:22:07

#include <bits/stdc++.h>
using namespace std;

class Fancy {
public:
    Fancy() {
        const long long MOD = 1000000007;
        (void)MOD;
        M.clear(); A.clear(); vals.clear();
        M.push_back(1); // initial multiplier
        A.push_back(0); // initial add
        opCount = 0;
    }
    
    void append(int val) {
        vals.emplace_back(((long long)val % MOD + MOD) % MOD, opCount);
    }
    
    void addAll(int inc) {
        long long a = (A.back() + inc) % MOD;
        if (a < 0) a += MOD;
        A.push_back(a);
        M.push_back(M.back());
        opCount++;
    }
    
    void multAll(int m) {
        long long mll = m % MOD;
        if (mll < 0) mll += MOD;
        long long mn = (M.back() * mll) % MOD;
        long long an = (A.back() * mll) % MOD;
        M.push_back(mn);
        A.push_back(an);
        opCount++;
    }
    
    int getIndex(int idx) {
        if (idx < 0 || idx >= (int)vals.size()) return -1;
        int k = vals[idx].second; // op snapshot at append
        int n = opCount;
        long long v = vals[idx].first;
        if (k == n) return (int)(v % MOD);
        // if multiplier at append was zero, then for any n>k multiplier stays zero
        // and the value after operations is simply A[n]
        if (M[k] == 0) return (int)(A[n] % MOD);
        long long ratio = M[n] * modInv(M[k]) % MOD;
        long long res = (v * ratio) % MOD;
        long long tmp = (A[n] - (A[k] * ratio) % MOD) % MOD;
        res = (res + tmp) % MOD;
        if (res < 0) res += MOD;
        return (int)res;
    }

private:
    static const long long MOD = 1000000007LL;
    vector<long long> M; // prefix multipliers
    vector<long long> A; // prefix adds
    vector<pair<long long,int>> vals; // (value at append, opIndex)
    int opCount;

    static long long modPow(long long a, long long e) {
        long long r = 1;
        a %= MOD;
        while (e > 0) {
            if (e & 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return r;
    }

    static long long modInv(long long a) {
        return modPow((a%MOD+MOD)%MOD, MOD-2);
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */