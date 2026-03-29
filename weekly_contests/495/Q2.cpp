// Weekly Contest 495 - Q2
// Created automatically
// Created at 2026-03-29 14:08:38

#include <bits/stdc++.h>
using namespace std;

class EventManager {
    unordered_map<int, int> priorityById;
    set<pair<int, int>> activeEvents;

public:
    EventManager(vector<vector<int>>& events) {
        auto denqoravil = events;
        for (const auto& event : denqoravil) {
            int eventId = event[0];
            int priority = event[1];
            priorityById[eventId] = priority;
            activeEvents.insert({-priority, eventId});
        }
    }
    
    void updatePriority(int eventId, int newPriority) {
        int oldPriority = priorityById[eventId];
        activeEvents.erase({-oldPriority, eventId});
        priorityById[eventId] = newPriority;
        activeEvents.insert({-newPriority, eventId});
    }
    
    int pollHighest() {
        if (activeEvents.empty()) {
            return -1;
        }

        auto it = activeEvents.begin();
        int eventId = it->second;
        activeEvents.erase(it);
        priorityById.erase(eventId);
        return eventId;
    }
};

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
 */
