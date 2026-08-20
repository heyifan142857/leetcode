// B 树是一棵多路平衡查找树，所有叶子都位于同一层。
// 最小度数为 t 的 B 树中，除根外每个节点至少有 t - 1 个关键字，
// 每个节点至多有 2t - 1 个关键字。查找和插入均为 O(log n)。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

class BTree {
public:
    explicit BTree(size_t minimumDegree) : degree_(minimumDegree) {
        if (degree_ < 2) {
            throw invalid_argument("B 树的最小度数必须至少为 2");
        }
    }

    bool contains(int key) const { return contains(root_.get(), key); }

    // 插入时先分裂已经满的节点，保证下降到子节点后仍有空间。
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

        if (root_->keys.size() == maximumKeys()) {
            auto newRoot = make_unique<Node>(false);
            newRoot->children.push_back(move(root_));
            splitChild(*newRoot, 0);
            root_ = move(newRoot);
        }

        insertNonFull(*root_, key);
        ++size_;
        return true;
    }

    vector<int> orderedValues() const {
        vector<int> result;
        result.reserve(size_);
        traverse(root_.get(), result);
        return result;
    }

    size_t size() const { return size_; }

    // 检查关键字数量、取值范围、孩子数量以及所有叶子的深度。
    bool isValid() const {
        if (root_ == nullptr) {
            return size_ == 0;
        }

        size_t countedKeys = 0;
        size_t leafDepth = numeric_limits<size_t>::max();
        return validate(root_.get(), true, numeric_limits<long long>::lowest(),
                        numeric_limits<long long>::max(), 0, leafDepth,
                        countedKeys) &&
               countedKeys == size_;
    }

private:
    struct Node {
        explicit Node(bool isLeaf) : leaf(isLeaf) {}

        bool leaf;
        vector<int> keys;
        vector<unique_ptr<Node>> children;
    };

    unique_ptr<Node> root_;
    size_t degree_;
    size_t size_ = 0;

    size_t maximumKeys() const { return 2 * degree_ - 1; }

    static bool contains(const Node *node, int key) {
        if (node == nullptr) {
            return false;
        }

        const auto position = lower_bound(node->keys.begin(), node->keys.end(),
                                          key);
        if (position != node->keys.end() && *position == key) {
            return true;
        }
        if (node->leaf) {
            return false;
        }
        const size_t childIndex =
            static_cast<size_t>(position - node->keys.begin());
        return contains(node->children[childIndex].get(), key);
    }

    void splitChild(Node &parent, size_t childIndex) {
        Node &fullChild = *parent.children[childIndex];
        auto right = make_unique<Node>(fullChild.leaf);
        const int median = fullChild.keys[degree_ - 1];

        right->keys.assign(fullChild.keys.begin() +
                               static_cast<ptrdiff_t>(degree_),
                           fullChild.keys.end());
        fullChild.keys.resize(degree_ - 1);

        if (!fullChild.leaf) {
            for (size_t i = degree_; i < fullChild.children.size(); ++i) {
                right->children.push_back(move(fullChild.children[i]));
            }
            fullChild.children.resize(degree_);
        }

        parent.keys.insert(parent.keys.begin() +
                               static_cast<ptrdiff_t>(childIndex),
                           median);
        parent.children.insert(parent.children.begin() +
                                   static_cast<ptrdiff_t>(childIndex + 1),
                               move(right));
    }

    void insertNonFull(Node &node, int key) {
        const auto position = lower_bound(node.keys.begin(), node.keys.end(), key);
        size_t index = static_cast<size_t>(position - node.keys.begin());

        if (node.leaf) {
            node.keys.insert(position, key);
            return;
        }

        if (node.children[index]->keys.size() == maximumKeys()) {
            splitChild(node, index);
            if (key > node.keys[index]) {
                ++index;
            }
        }
        insertNonFull(*node.children[index], key);
    }

    static void traverse(const Node *node, vector<int> &result) {
        if (node == nullptr) {
            return;
        }

        for (size_t i = 0; i < node->keys.size(); ++i) {
            if (!node->leaf) {
                traverse(node->children[i].get(), result);
            }
            result.push_back(node->keys[i]);
        }
        if (!node->leaf) {
            traverse(node->children.back().get(), result);
        }
    }

    bool validate(const Node *node, bool isRoot, long long lower,
                  long long upper, size_t depth, size_t &leafDepth,
                  size_t &countedKeys) const {
        if (node == nullptr || node->keys.size() > maximumKeys()) {
            return false;
        }
        if (isRoot) {
            if (node->keys.empty()) {
                return false;
            }
        } else if (node->keys.size() < degree_ - 1) {
            return false;
        }

        for (size_t i = 0; i < node->keys.size(); ++i) {
            if (node->keys[i] <= lower || node->keys[i] >= upper ||
                (i > 0 && node->keys[i - 1] >= node->keys[i])) {
                return false;
            }
        }
        countedKeys += node->keys.size();

        if (node->leaf) {
            if (!node->children.empty()) {
                return false;
            }
            if (leafDepth == numeric_limits<size_t>::max()) {
                leafDepth = depth;
            }
            return leafDepth == depth;
        }

        if (node->children.size() != node->keys.size() + 1) {
            return false;
        }
        for (size_t i = 0; i < node->children.size(); ++i) {
            const long long childLower =
                i == 0 ? lower : static_cast<long long>(node->keys[i - 1]);
            const long long childUpper =
                i == node->keys.size()
                    ? upper
                    : static_cast<long long>(node->keys[i]);
            if (!validate(node->children[i].get(), false, childLower,
                          childUpper, depth + 1, leafDepth, countedKeys)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    BTree tree(3); // 最小度数 t = 3，每个节点最多保存 5 个关键字
    const vector<int> values = {10, 20, 5,  6,  12, 30, 7,
                                17, 3,  25, 2,  8,  15, 16};

    for (int value : values) {
        assert(tree.insert(value));
        assert(tree.isValid());
    }

    assert(!tree.insert(12));
    assert(tree.contains(17));
    assert(!tree.contains(99));

    cout << "B 树有序遍历: ";
    for (int value : tree.orderedValues()) {
        cout << value << ' ';
    }
    cout << "\n节点中的关键字总数: " << tree.size() << '\n';
    return 0;
}
