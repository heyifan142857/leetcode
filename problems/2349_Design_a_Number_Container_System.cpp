//
// Created by user on 2025/9/17.
//
#include <unordered_map>
#include <set>
using namespace std;

class NumberContainers {
    unordered_map<int, int> mp;
    unordered_map<int, set<int>> order;
public:
    NumberContainers() {

    }

    void change(int index, int number) {
        if(mp.contains(index)){
            int former = mp[index];
            order[former].erase(index);
            if(order[former].empty()){
                order.erase(former);
            }
        }
        mp[index] = number;
        order[number].insert(index);
    }

    int find(int number) {
        if(order.contains(number)){
            return *order[number].begin();
        }else{
            return -1;
        }
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */