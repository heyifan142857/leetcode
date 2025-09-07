//
// Created by user on 2025/9/7.
//

#include <deque>
#include <unordered_map>
using namespace std;

class LRUCache {
    int cnt = 0;
    int size = 0;
    deque<pair<int, int>> history;
    unordered_map<int, pair<int, int>> map;

public:
    LRUCache(int capacity) {
        size = capacity;
    }

    int get(int key) {
        if(map.contains(key)){
            history.emplace_back(key, cnt);
            map[key].second = cnt;
            cnt++;
            return map[key].first;
        }else{
            return -1;
        }
    }

    void put(int key, int value) {
        if(map.contains(key) || map.size() < size){
            history.emplace_back(key, cnt);
            map[key] = make_pair(value, cnt);
            cnt++;
        }else{
            while (!history.empty() && (!map.contains(history.front().first) || map[history.front().first].second != history.front().second)){
                history.pop_front();
            }
            if(!history.empty()){
                map.erase(history.front().first);
                history.pop_front();
                history.emplace_back(key, cnt);
                map[key] = make_pair(value, cnt);
                cnt++;
            }
        }
    }
};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */