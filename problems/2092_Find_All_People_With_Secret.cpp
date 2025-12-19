#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // Sort meetings by time
        sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        // Track who has the secret
        unordered_set<int> hasSecret;
        hasSecret.insert(0);
        hasSecret.insert(firstPerson);
        
        int i = 0;
        while (i < meetings.size()) {
            int currentTime = meetings[i][2];
            
            // Build graph for all meetings at current time
            unordered_map<int, vector<int>> graph;
            unordered_set<int> peopleAtTime;
            
            while (i < meetings.size() && meetings[i][2] == currentTime) {
                int x = meetings[i][0];
                int y = meetings[i][1];
                graph[x].push_back(y);
                graph[y].push_back(x);
                peopleAtTime.insert(x);
                peopleAtTime.insert(y);
                i++;
            }
            
            // Find all connected components using BFS
            unordered_set<int> visited;
            
            for (int person : peopleAtTime) {
                if (visited.find(person) != visited.end()) {
                    continue;
                }
                
                // BFS to find all people in this component
                queue<int> q;
                unordered_set<int> component;
                
                q.push(person);
                visited.insert(person);
                component.insert(person);
                
                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    
                    for (int neighbor : graph[curr]) {
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            component.insert(neighbor);
                            q.push(neighbor);
                        }
                    }
                }
                
                // If any person in component has secret, all get it
                bool componentHasSecret = false;
                for (int p : component) {
                    if (hasSecret.find(p) != hasSecret.end()) {
                        componentHasSecret = true;
                        break;
                    }
                }
                
                if (componentHasSecret) {
                    for (int p : component) {
                        hasSecret.insert(p);
                    }
                }
            }
        }
        
        // Convert set to vector
        vector<int> result(hasSecret.begin(), hasSecret.end());
        return result;
    }
};