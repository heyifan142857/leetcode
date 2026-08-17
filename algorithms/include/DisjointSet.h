#pragma once

#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace algo {

// 并查集：使用路径压缩和按秩合并维护互不相交的集合。
class DisjointSet {
public:
    explicit DisjointSet(int elementCount) : componentCount_(elementCount) {
        if (elementCount < 0) {
            throw std::invalid_argument("元素数量不能为负数");
        }

        parent_.resize(elementCount);
        rank_.assign(elementCount, 0);
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int element) {
        checkElement(element);
        if (parent_[element] != element) {
            parent_[element] = find(parent_[element]);
        }
        return parent_[element];
    }

    // 合并两个集合；原本不连通时返回 true，否则返回 false。
    bool unite(int first, int second) {
        int firstRoot = find(first);
        int secondRoot = find(second);
        if (firstRoot == secondRoot) {
            return false;
        }

        if (rank_[firstRoot] < rank_[secondRoot]) {
            std::swap(firstRoot, secondRoot);
        }
        parent_[secondRoot] = firstRoot;
        if (rank_[firstRoot] == rank_[secondRoot]) {
            ++rank_[firstRoot];
        }

        --componentCount_;
        return true;
    }

    bool connected(int first, int second) {
        return find(first) == find(second);
    }

    int componentCount() const noexcept { return componentCount_; }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;
    int componentCount_;

    void checkElement(int element) const {
        if (element < 0 || element >= static_cast<int>(parent_.size())) {
            throw std::out_of_range("并查集元素编号超出范围");
        }
    }
};

} // namespace algo
