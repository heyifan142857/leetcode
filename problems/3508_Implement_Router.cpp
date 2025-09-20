//
// Created by user on 2025/9/20.
//
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Router {
    int capacity = 0;
    deque<vector<int>> routes;
    unordered_map<string, int> includes;

    unordered_map<int, vector<int>> desPacket;
    unordered_map<int, int> deleted;

public:
    Router(int memoryLimit):capacity(memoryLimit) {}

    string packetId(int source, int destination, int timestamp){
        return to_string(source)+ "+"+ to_string(destination)+ "+" + to_string(timestamp);
    }

    string packetId(vector<int> packet){
        if(packet.size() < 3) return "";
        return packetId(packet[0], packet[1], packet[2]);
    }

    bool isExist(int source, int destination, int timestamp){
        return includes[packetId(source, destination, timestamp)] > 0;
    }

    bool isExist(vector<int> packet){
        if(packet.size() < 3) return false;
        return isExist(packet[0], packet[1], packet[2]);
    }

    bool addPacket(int source, int destination, int timestamp) {
        if(isExist(source, destination, timestamp)){
            return false;
        }
        if((int)routes.size() >= capacity){
            forwardPacket();
        }
        routes.push_back({source, destination, timestamp});
        includes[packetId(source, destination, timestamp)]++;
        desPacket[destination].push_back(timestamp);
        return true;
    }

    vector<int> forwardPacket() {
        if(routes.empty()){
            return {};
        }
        vector<int> front = routes.front();
        includes[packetId(front)]--;
        routes.pop_front();
        deleted[front[1]]++;
        return front;
    }

    int getCount(int destination, int startTime, int endTime) {
        auto &cur = desPacket[destination];
        if(cur.empty()) return 0;

        int del = deleted[destination];
        auto lower = lower_bound(cur.begin()+del, cur.end(), startTime);
        auto upper = upper_bound(cur.begin()+del, cur.end(), endTime);
        return upper - lower;
    }
};
/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */