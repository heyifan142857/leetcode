// B+ 树的内部节点只保存索引，全部数据关键字都保存在叶子节点中；
// 叶子通过链表相连，因此既能 O(log n) 查找，也适合顺序和范围访问。
// 下面实现插入、查找与闭区间范围查询，单次查找和插入均为 O(log n)。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

using namespace std;

class BPlusTree {
public:
    // order 表示内部节点最多拥有的孩子数，也就是最多有 order - 1 个索引。
    explicit BPlusTree(size_t order) : order_(order) {
        if (order_ < 3) {
            throw invalid_argument("B+ 树的阶数必须至少为 3");
        }
    }

    bool contains(int key) const {
        const Node *leaf = findLeaf(key);
        return leaf != nullptr &&
               binary_search(leaf->keys.begin(), leaf->keys.end(), key);
    }

    // 重复关键字不插入。
    bool insert(int key) {
        if (contains(key)) {
            return false;
        }
        if (root_ == nullptr) {
            root_ = make_unique<Node>(true);
            root_->keys.push_back(key);
            ++size_;
            return true;
        }

        optional<Split> split = insert(*root_, key);
        if (split.has_value()) {
            auto newRoot = make_unique<Node>(false);
            newRoot->keys.push_back(split->separator);
            newRoot->children.push_back(move(root_));
            newRoot->children.push_back(move(split->right));
            root_ = move(newRoot);
        }
        ++size_;
        return true;
    }

    vector<int> orderedValues() const {
        vector<int> result;
        result.reserve(size_);
        const Node *leaf = leftmostLeaf();
        while (leaf != nullptr) {
            result.insert(result.end(), leaf->keys.begin(), leaf->keys.end());
            leaf = leaf->next;
        }
        return result;
    }

    // 返回 [lower, upper] 内的全部关键字，复杂度为 O(log n + k)。
    vector<int> rangeQuery(int lower, int upper) const {
        vector<int> result;
        if (lower > upper) {
            return result;
        }

        const Node *leaf = findLeaf(lower);
        while (leaf != nullptr) {
            for (int key : leaf->keys) {
                if (key > upper) {
                    return result;
                }
                if (key >= lower) {
                    result.push_back(key);
                }
            }
            leaf = leaf->next;
        }
        return result;
    }

    size_t size() const { return size_; }

    bool isValid() const {
        if (root_ == nullptr) {
            return size_ == 0;
        }

        size_t leafDepth = numeric_limits<size_t>::max();
        size_t countedKeys = 0;
        vector<const Node *> leaves;
        Validation summary;
        if (!validate(root_.get(), true, 0, leafDepth, countedKeys, leaves,
                      summary) ||
            countedKeys != size_) {
            return false;
        }

        for (size_t i = 0; i < leaves.size(); ++i) {
            const Node *expected = i + 1 < leaves.size() ? leaves[i + 1] : nullptr;
            if (leaves[i]->next != expected) {
                return false;
            }
        }
        return true;
    }

private:
    struct Node {
        explicit Node(bool isLeaf) : leaf(isLeaf) {}

        bool leaf;
        vector<int> keys;
        vector<unique_ptr<Node>> children;
        Node *next = nullptr; // 只供叶子节点使用，不拥有下一个叶子
    };

    struct Split {
        int separator;
        unique_ptr<Node> right;
    };

    struct Validation {
        int minimum = 0;
        int maximum = 0;
        bool hasValue = false;
    };

    unique_ptr<Node> root_;
    size_t order_;
    size_t size_ = 0;

    size_t maximumKeys() const { return order_ - 1; }

    Node *findLeaf(int key) {
        return const_cast<Node *>(
            static_cast<const BPlusTree &>(*this).findLeaf(key));
    }

    const Node *findLeaf(int key) const {
        const Node *node = root_.get();
        while (node != nullptr && !node->leaf) {
            const auto position = upper_bound(node->keys.begin(),
                                              node->keys.end(), key);
            const size_t index =
                static_cast<size_t>(position - node->keys.begin());
            node = node->children[index].get();
        }
        return node;
    }

    const Node *leftmostLeaf() const {
        const Node *node = root_.get();
        while (node != nullptr && !node->leaf) {
            node = node->children.front().get();
        }
        return node;
    }

    optional<Split> insert(Node &node, int key) {
        if (node.leaf) {
            const auto position = lower_bound(node.keys.begin(), node.keys.end(),
                                              key);
            node.keys.insert(position, key);
            if (node.keys.size() <= maximumKeys()) {
                return nullopt;
            }
            return splitLeaf(node);
        }

        const auto position = upper_bound(node.keys.begin(), node.keys.end(), key);
        const size_t childIndex =
            static_cast<size_t>(position - node.keys.begin());
        optional<Split> childSplit = insert(*node.children[childIndex], key);
        if (!childSplit.has_value()) {
            return nullopt;
        }

        node.keys.insert(node.keys.begin() +
                             static_cast<ptrdiff_t>(childIndex),
                         childSplit->separator);
        node.children.insert(node.children.begin() +
                                 static_cast<ptrdiff_t>(childIndex + 1),
                             move(childSplit->right));
        if (node.keys.size() <= maximumKeys()) {
            return nullopt;
        }
        return splitInternal(node);
    }

    optional<Split> splitLeaf(Node &leaf) {
        const size_t middle = (leaf.keys.size() + 1) / 2;
        auto right = make_unique<Node>(true);
        right->keys.assign(leaf.keys.begin() + static_cast<ptrdiff_t>(middle),
                           leaf.keys.end());
        leaf.keys.resize(middle);

        right->next = leaf.next;
        leaf.next = right.get();
        return Split{right->keys.front(), move(right)};
    }

    optional<Split> splitInternal(Node &node) {
        const size_t middle = node.keys.size() / 2;
        const int promoted = node.keys[middle];
        auto right = make_unique<Node>(false);

        right->keys.assign(node.keys.begin() +
                               static_cast<ptrdiff_t>(middle + 1),
                           node.keys.end());
        node.keys.resize(middle);

        for (size_t i = middle + 1; i < node.children.size(); ++i) {
            right->children.push_back(move(node.children[i]));
        }
        node.children.resize(middle + 1);
        return Split{promoted, move(right)};
    }

    size_t minimumLeafKeys() const { return (maximumKeys() + 1) / 2; }
    size_t minimumInternalChildren() const { return (order_ + 1) / 2; }

    bool validate(const Node *node, bool isRoot, size_t depth,
                  size_t &leafDepth, size_t &countedKeys,
                  vector<const Node *> &leaves, Validation &summary) const {
        if (node == nullptr || node->keys.empty() ||
            node->keys.size() > maximumKeys() ||
            !is_sorted(node->keys.begin(), node->keys.end()) ||
            adjacent_find(node->keys.begin(), node->keys.end()) !=
                node->keys.end()) {
            return false;
        }

        if (node->leaf) {
            if (!node->children.empty() ||
                (!isRoot && node->keys.size() < minimumLeafKeys())) {
                return false;
            }
            if (leafDepth == numeric_limits<size_t>::max()) {
                leafDepth = depth;
            }
            if (leafDepth != depth) {
                return false;
            }
            countedKeys += node->keys.size();
            leaves.push_back(node);
            summary = {node->keys.front(), node->keys.back(), true};
            return true;
        }

        if (node->next != nullptr ||
            node->children.size() != node->keys.size() + 1 ||
            (!isRoot &&
             node->children.size() < minimumInternalChildren())) {
            return false;
        }

        vector<Validation> childSummaries(node->children.size());
        for (size_t i = 0; i < node->children.size(); ++i) {
            if (!validate(node->children[i].get(), false, depth + 1, leafDepth,
                          countedKeys, leaves, childSummaries[i])) {
                return false;
            }
        }
        for (size_t i = 0; i < node->keys.size(); ++i) {
            // 索引等于右侧孩子（子树）中的最小关键字。
            if (!childSummaries[i].hasValue ||
                !childSummaries[i + 1].hasValue ||
                childSummaries[i].maximum >= childSummaries[i + 1].minimum ||
                node->keys[i] != childSummaries[i + 1].minimum) {
                return false;
            }
        }

        summary = {childSummaries.front().minimum,
                   childSummaries.back().maximum, true};
        return true;
    }
};

int main() {
    BPlusTree tree(4); // 4 阶 B+ 树：内部节点最多有 4 个孩子
    const vector<int> values = {15, 5,  1,  20, 25, 10, 30, 8,
                                12, 18, 22, 28, 35, 3,  6,  16};

    for (int value : values) {
        assert(tree.insert(value));
        assert(tree.isValid());
    }

    assert(!tree.insert(20));
    assert(tree.contains(12));
    assert(!tree.contains(99));
    assert((tree.rangeQuery(8, 22) ==
            vector<int>{8, 10, 12, 15, 16, 18, 20, 22}));

    cout << "B+ 树叶子链表: ";
    for (int value : tree.orderedValues()) {
        cout << value << ' ';
    }
    cout << "\n[8, 22] 范围查询: ";
    for (int value : tree.rangeQuery(8, 22)) {
        cout << value << ' ';
    }
    cout << '\n';
    return 0;
}
