//
// Created by user on 2025/9/18.
//
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class TaskManager {
    unordered_map<int, int> tp;
    unordered_map<int, int> tu;
    priority_queue<pair<int, int>> pq;

public:
    TaskManager(vector<vector<int>>& tasks) {
        for(auto task: tasks){
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];
            tp[taskId] = priority;
            tu[taskId] = userId;
            pq.push({priority, taskId});
        }
    }

    void add(int userId, int taskId, int priority) {
        tp[taskId] = priority;
        tu[taskId] = userId;
        pq.push({priority, taskId});
    }

    void edit(int taskId, int newPriority) {
        tp[taskId] = newPriority;
        pq.push({newPriority, taskId});
    }

    void rmv(int taskId) {
        tp.erase(taskId);
        tu.erase(taskId);
    }

    int execTop() {
        if(tp.empty()){
            return -1;
        }
        while(!tp.contains(pq.top().second) || tp[pq.top().second]!=pq.top().first){
            pq.pop();
        }
        int id = pq.top().second;
        int user = tu[id];
        rmv(id);
        return user;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */