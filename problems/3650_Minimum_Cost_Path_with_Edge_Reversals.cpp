//
// Created by azote on 1/27/26.
//
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(int n, vector<vector<int> > &edges) {
        vector<vector<pair<int, int> > > g(n), rg(n);
        for (auto &e: edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            rg[v].push_back({u, w}); // 反向边
        }

        const long long INF = 1e18;
        vector<vector<long long> > dist(n, vector<long long>(2, INF));

        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int> >,
            greater<>
        > pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0}); // cost, node, used

        while (!pq.empty()) {
            auto [d, u, used] = pq.top();
            pq.pop();
            if (d > dist[u][used]) continue;

            for (auto &[v, w]: g[u]) {
                if (dist[v][0] > d + w) {
                    dist[v][0] = d + w;
                    pq.push({dist[v][0], v, 0});
                }
            }

            if (used == 0) {
                for (auto &[v, w]: rg[u]) {
                    if (dist[v][0] > d + 2LL * w) {
                        dist[v][0] = d + 2LL * w;
                        pq.push({dist[v][0], v, 0});
                    }
                }
            }
        }

        long long ans = min(dist[n - 1][0], dist[n - 1][1]);
        return ans == INF ? -1 : ans;
    }
};

