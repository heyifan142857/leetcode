// 查找长度是查找过程中比较关键字的次数；平均查找长度 ASL 是各关键字
// 查找长度按其查找概率得到的加权平均值。红黑树不追求严格高度平衡，
// 但最长根到叶路径不超过最短路径的两倍，树高至多为 2log2(n + 1)，
// 因而查找、插入、删除的最坏时间复杂度均为 O(log n)。

#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class RedBlackTree {
public:
    RedBlackTree() {
        nil_ = new Node(0, Color::Black);
        nil_->left = nil_;
        nil_->right = nil_;
        nil_->parent = nil_;
        root_ = nil_;
    }

    // 构造：按照给定顺序逐个插入，并在每次插入后修复红黑性质。
    explicit RedBlackTree(const vector<int> &values) : RedBlackTree() {
        for (int value : values) {
            insert(value);
        }
    }

    RedBlackTree(const RedBlackTree &) = delete;
    RedBlackTree &operator=(const RedBlackTree &) = delete;

    ~RedBlackTree() {
        destroy(root_);
        delete nil_;
    }

    // 查找。
    bool contains(int key) const { return findNode(key) != nil_; }

    // 插入：重复关键字不插入。
    bool insert(int key) {
        Node *parent = nil_;
        Node *current = root_;
        while (current != nil_) {
            parent = current;
            if (key == current->key) {
                return false;
            }
            current = key < current->key ? current->left : current->right;
        }

        Node *node = new Node(key, Color::Red);
        node->left = nil_;
        node->right = nil_;
        node->parent = parent;

        if (parent == nil_) {
            root_ = node;
        } else if (key < parent->key) {
            parent->left = node;
        } else {
            parent->right = node;
        }

        insertFix(node);
        ++size_;
        return true;
    }

    // 删除：先按 BST 规则删除，再修复可能被破坏的红黑性质。
    bool erase(int key) {
        Node *target = findNode(key);
        if (target == nil_) {
            return false;
        }

        Node *moved = target;
        Color removedColor = moved->color;
        Node *fixFrom = nil_;

        if (target->left == nil_) {
            fixFrom = target->right;
            transplant(target, target->right);
        } else if (target->right == nil_) {
            fixFrom = target->left;
            transplant(target, target->left);
        } else {
            moved = minimum(target->right);
            removedColor = moved->color;
            fixFrom = moved->right;

            if (moved->parent == target) {
                fixFrom->parent = moved;
            } else {
                transplant(moved, moved->right);
                moved->right = target->right;
                moved->right->parent = moved;
            }

            transplant(target, moved);
            moved->left = target->left;
            moved->left->parent = moved;
            moved->color = target->color;
        }

        delete target;
        --size_;
        if (removedColor == Color::Black) {
            eraseFix(fixFrom);
        }
        return true;
    }

    vector<int> inorder() const {
        vector<int> result;
        inorder(root_, result);
        return result;
    }

    size_t size() const { return size_; }

    // 用于示例和调试：同时检查 BST 次序及所有红黑树性质。
    bool isValid() const {
        if (root_ == nil_) {
            return size_ == 0;
        }
        if (root_->color != Color::Black || root_->parent != nil_) {
            return false;
        }

        int expectedBlackHeight = -1;
        size_t nodeCount = 0;
        const bool valid = validate(
            root_, numeric_limits<long long>::lowest(),
            numeric_limits<long long>::max(), 0, expectedBlackHeight,
            nodeCount);
        return valid && nodeCount == size_;
    }

private:
    enum class Color { Red, Black };

    struct Node {
        Node(int key, Color color) : key(key), color(color) {}

        int key;
        Color color;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
    };

    Node *root_ = nullptr;
    Node *nil_ = nullptr; // 所有空孩子共享的黑色哨兵节点
    size_t size_ = 0;

    Node *findNode(int key) const {
        Node *current = root_;
        while (current != nil_ && current->key != key) {
            current = key < current->key ? current->left : current->right;
        }
        return current;
    }

    void leftRotate(Node *root) {
        Node *newRoot = root->right;
        root->right = newRoot->left;
        if (newRoot->left != nil_) {
            newRoot->left->parent = root;
        }

        newRoot->parent = root->parent;
        if (root->parent == nil_) {
            root_ = newRoot;
        } else if (root == root->parent->left) {
            root->parent->left = newRoot;
        } else {
            root->parent->right = newRoot;
        }
        newRoot->left = root;
        root->parent = newRoot;
    }

    void rightRotate(Node *root) {
        Node *newRoot = root->left;
        root->left = newRoot->right;
        if (newRoot->right != nil_) {
            newRoot->right->parent = root;
        }

        newRoot->parent = root->parent;
        if (root->parent == nil_) {
            root_ = newRoot;
        } else if (root == root->parent->right) {
            root->parent->right = newRoot;
        } else {
            root->parent->left = newRoot;
        }
        newRoot->right = root;
        root->parent = newRoot;
    }

    void insertFix(Node *node) {
        while (node->parent->color == Color::Red) {
            if (node->parent == node->parent->parent->left) {
                Node *uncle = node->parent->parent->right;
                if (uncle->color == Color::Red) {
                    node->parent->color = Color::Black;
                    uncle->color = Color::Black;
                    node->parent->parent->color = Color::Red;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = Color::Black;
                    node->parent->parent->color = Color::Red;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node *uncle = node->parent->parent->left;
                if (uncle->color == Color::Red) {
                    node->parent->color = Color::Black;
                    uncle->color = Color::Black;
                    node->parent->parent->color = Color::Red;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = Color::Black;
                    node->parent->parent->color = Color::Red;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root_->color = Color::Black;
    }

    void transplant(Node *oldRoot, Node *newRoot) {
        if (oldRoot->parent == nil_) {
            root_ = newRoot;
        } else if (oldRoot == oldRoot->parent->left) {
            oldRoot->parent->left = newRoot;
        } else {
            oldRoot->parent->right = newRoot;
        }
        // newRoot 可能是 nil_，删除修复同样需要它的父节点。
        newRoot->parent = oldRoot->parent;
    }

    Node *minimum(Node *node) const {
        while (node->left != nil_) {
            node = node->left;
        }
        return node;
    }

    void eraseFix(Node *node) {
        while (node != root_ && node->color == Color::Black) {
            if (node == node->parent->left) {
                Node *sibling = node->parent->right;
                if (sibling->color == Color::Red) {
                    sibling->color = Color::Black;
                    node->parent->color = Color::Red;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }
                if (sibling->left->color == Color::Black &&
                    sibling->right->color == Color::Black) {
                    sibling->color = Color::Red;
                    node = node->parent;
                } else {
                    if (sibling->right->color == Color::Black) {
                        sibling->left->color = Color::Black;
                        sibling->color = Color::Red;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = Color::Black;
                    sibling->right->color = Color::Black;
                    leftRotate(node->parent);
                    node = root_;
                }
            } else {
                Node *sibling = node->parent->left;
                if (sibling->color == Color::Red) {
                    sibling->color = Color::Black;
                    node->parent->color = Color::Red;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }
                if (sibling->right->color == Color::Black &&
                    sibling->left->color == Color::Black) {
                    sibling->color = Color::Red;
                    node = node->parent;
                } else {
                    if (sibling->left->color == Color::Black) {
                        sibling->right->color = Color::Black;
                        sibling->color = Color::Red;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = Color::Black;
                    sibling->left->color = Color::Black;
                    rightRotate(node->parent);
                    node = root_;
                }
            }
        }
        node->color = Color::Black;
        nil_->color = Color::Black;
    }

    void inorder(const Node *node, vector<int> &result) const {
        if (node == nil_) {
            return;
        }
        inorder(node->left, result);
        result.push_back(node->key);
        inorder(node->right, result);
    }

    bool validate(const Node *node, long long lower, long long upper,
                  int blackCount, int &expectedBlackHeight,
                  size_t &nodeCount) const {
        if (node == nil_) {
            ++blackCount; // 黑色 NIL 叶节点也计入黑高。
            if (expectedBlackHeight == -1) {
                expectedBlackHeight = blackCount;
            }
            return blackCount == expectedBlackHeight;
        }
        if (node->key <= lower || node->key >= upper) {
            return false;
        }
        if (node->color == Color::Red &&
            (node->left->color == Color::Red ||
             node->right->color == Color::Red)) {
            return false;
        }

        ++nodeCount;
        if (node->color == Color::Black) {
            ++blackCount;
        }
        return validate(node->left, lower, node->key, blackCount,
                        expectedBlackHeight, nodeCount) &&
               validate(node->right, node->key, upper, blackCount,
                        expectedBlackHeight, nodeCount);
    }

    void destroy(Node *node) {
        if (node == nil_) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

int main() {
    RedBlackTree tree({41, 38, 31, 12, 19, 8, 50, 60});
    assert(tree.isValid());
    assert(tree.contains(19));
    assert(!tree.contains(99));

    assert(tree.insert(25));
    assert(!tree.insert(25));
    assert(tree.isValid());

    assert(tree.erase(8));       // 删除叶子节点
    assert(tree.erase(38));      // 删除内部节点
    assert(!tree.erase(99));
    assert(tree.isValid());

    cout << "中序遍历: ";
    for (int value : tree.inorder()) {
        cout << value << ' ';
    }
    cout << "\n节点数: " << tree.size() << '\n';
    return 0;
}
