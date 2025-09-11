//
// Created by user on 2025/9/11.
//

#include <vector>
#include <list>
using namespace std;

class Solution {
    vector<list<int>> adj;
    bool isCyclicDFS(int node, vector<bool>& visited, vector<bool>& recStack) {
        if (!visited[node]) {
            visited[node] = true;
            recStack[node] = true;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    if (isCyclicDFS(neighbor, visited, recStack)) {
                        return true;
                    }
                }
                else if (recStack[neighbor]) {
                    return true;
                }
            }
        }

        recStack[node] = false;
        return false;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        adj.resize(numCourses);
        for (auto prerequisite: prerequisites) {
            adj[prerequisite[0]].push_back(prerequisite[1]);
        }
        vector<bool> visited(numCourses, false);
        vector<bool> recStack(numCourses, false);

        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                if (isCyclicDFS(i, visited, recStack)) {
                    return false;
                }
            }
        }
        return true;
    }
};