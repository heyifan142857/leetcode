#pragma once

#include <limits>
#include <stdexcept>
#include <vector>

namespace algo {

using Weight = long long;

inline constexpr Weight kInfinity = std::numeric_limits<Weight>::max() / 4;

// 图中的一条逻辑边。无向图的边只在 edges() 中保存一次。
struct Edge {
    int from;
    int to;
    Weight weight;
};

// 邻接表中的边，只需记录目标顶点和边权。
struct AdjacentEdge {
    int to;
    Weight weight;
};

// 基于邻接表的通用图结构，同时提供逻辑边和有向弧两种视图。
class Graph {
public:
    explicit Graph(int vertexCount, bool directed = false)
        : directed_(directed) {
        if (vertexCount < 0) {
            throw std::invalid_argument("顶点数不能为负数");
        }
        adjacencyList_.resize(vertexCount);
    }

    int vertexCount() const noexcept {
        return static_cast<int>(adjacencyList_.size());
    }

    bool isDirected() const noexcept { return directed_; }

    void addEdge(int from, int to, Weight weight = 1) {
        checkVertex(from);
        checkVertex(to);

        edges_.push_back({from, to, weight});
        arcs_.push_back({from, to, weight});
        adjacencyList_[from].push_back({to, weight});

        if (!directed_ && from != to) {
            arcs_.push_back({to, from, weight});
            adjacencyList_[to].push_back({from, weight});
        }
    }

    const std::vector<AdjacentEdge> &neighbors(int vertex) const {
        checkVertex(vertex);
        return adjacencyList_[vertex];
    }

    // 每条添加的边只出现一次，适合 Kruskal 等按逻辑边处理的算法。
    const std::vector<Edge> &edges() const noexcept { return edges_; }

    // 无向边会展开为两个方向的弧，适合 Bellman-Ford 等松弛算法。
    const std::vector<Edge> &arcs() const noexcept { return arcs_; }

private:
    bool directed_;
    std::vector<std::vector<AdjacentEdge>> adjacencyList_;
    std::vector<Edge> edges_;
    std::vector<Edge> arcs_;

    void checkVertex(int vertex) const {
        if (vertex < 0 || vertex >= vertexCount()) {
            throw std::out_of_range("顶点编号超出范围");
        }
    }
};

} // namespace algo
