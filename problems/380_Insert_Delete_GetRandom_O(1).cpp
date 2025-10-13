//
// Created by user on 2025/10/13.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
using namespace std;

class RandomizedSet {
    unordered_map<int, int> mp;
    vector<int> v;
public:
    RandomizedSet() {
        srand(time(nullptr));
    }

    bool insert(int val) {
        if(mp.contains(val)){
            return false;
        }
        v.push_back(val);
        mp[val] = v.size()-1;
        return true;
    }

    bool remove(int val) {
        if(mp.contains(val)){
            int index = mp[val];
            mp.erase(val);
            swap(v[index], v.back());
            v.pop_back();
            return true;
        } else{
            return false;
        }
    }

    int getRandom() {
        int idx = rand() % v.size();
        return v[idx];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */