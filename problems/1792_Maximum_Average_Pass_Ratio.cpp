//
// Created by user on 2025/9/1.
//

#include <vector>
#include <queue>
using namespace std;

class Solution {
    struct ClassRatio {
        int pass;
        int total;

        bool operator<(const ClassRatio& other) const {
            long long left = (long long)(other.total + 1) * other.total * (total - pass);
            long long right = (long long)(total + 1) * total * (other.total - other.pass);
            return left < right;
        }
    };

public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<ClassRatio> pq;

        for (const auto& cls : classes) {
            pq.push({cls[0], cls[1]});
        }

        for (int i = 0; i < extraStudents; ++i) {
            ClassRatio cur = pq.top();
            pq.pop();
            pq.push({cur.pass + 1, cur.total + 1});
        }

        double totalRatio = 0.0;
        int size = classes.size();

        while (!pq.empty()) {
            ClassRatio cur = pq.top();
            pq.pop();
            totalRatio += static_cast<double>(cur.pass) / cur.total;
        }

        return totalRatio / size;
    }
};

//时间超限了
//class Solution {
//    struct Compare {
//        bool operator()(vector<int> a, vector<int> b) {
//            return (b[1]*(b[1]+1)*(a[1]-a[0])<a[1]*(a[1]+1)*(b[1]-b[0]));
//        }
//    };
//public:
//    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
//        int total_class = classes.size();
//
//        priority_queue<vector<int>, vector<vector<int>>, Compare> pq(classes.begin(), classes.end());
//
//        for (int i = 0; i < extraStudents; ++i) {
//            vector<int> cur = pq.top();
//            pq.pop();
//            cur[0]++;
//            cur[1]++;
//            pq.push(cur);
//        }
//
//        double ans = 0;
//        while (!pq.empty()){
//            vector<int> cur = pq.top();
//            pq.pop();
//            ans += (double)cur[0] / (double)cur[1];
//        }
//
//        return ans / total_class;
//    }
//};
