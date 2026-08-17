// 查找长度是查找过程中比较关键字的次数；平均查找长度 ASL 是各关键字
// 查找长度按其查找概率得到的加权平均值。AVL 树要求每个节点左右子树的
// 高度差不超过 1，因此查找、插入、删除的最坏时间复杂度均为 O(log n)。

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class AVLTree {
public:
    AVLTree() = default;

    // 构造：按照给定顺序逐个插入，并在每次插入后恢复平衡。
    explicit AVLTree(const vector<int> &values) {
        for (int value : values) {
            insert(value);
        }
    }

    // 查找。
    bool contains(int key) const {
        const Node *current = root_.get();
        while (current != nullptr) {
            if (key == current->key) {
                return true;
            }
            current = key < current->key ? current->left.get()
                                         : current->right.get();
        }
        return false;
    }

    // 插入：重复关键字不插入。
    bool insert(int key) {
        bool inserted = false;
        root_ = insert(move(root_), key, inserted);
        if (inserted) {
            ++size_;
        }
        return inserted;
    }

    // 删除：删除后通过旋转恢复平衡。
    bool erase(int key) {
        bool erased = false;
        root_ = erase(move(root_), key, erased);
        if (erased) {
            --size_;
        }
        return erased;
    }

    vector<int> inorder() const {
        vector<int> result;
        inorder(root_.get(), result);
        return result;
    }

    size_t size() const { return size_; }
    int height() const { return nodeHeight(root_); }

private:
    struct Node {
        explicit Node(int key) : key(key) {}

        int key;
        int height = 1;
        unique_ptr<Node> left;
        unique_ptr<Node> right;
    };

    unique_ptr<Node> root_;
    size_t size_ = 0;

    static int nodeHeight(const unique_ptr<Node> &node) {
        return node == nullptr ? 0 : node->height;
    }

    static void updateHeight(Node *node) {
        node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    }

    static int balanceFactor(const unique_ptr<Node> &node) {
        return nodeHeight(node->left) - nodeHeight(node->right);
    }

    static unique_ptr<Node> rotateRight(unique_ptr<Node> root) {
        unique_ptr<Node> newRoot = move(root->left);
        root->left = move(newRoot->right);
        newRoot->right = move(root);

        updateHeight(newRoot->right.get());
        updateHeight(newRoot.get());
        return newRoot;
    }

    static unique_ptr<Node> rotateLeft(unique_ptr<Node> root) {
        unique_ptr<Node> newRoot = move(root->right);
        root->right = move(newRoot->left);
        newRoot->left = move(root);

        updateHeight(newRoot->left.get());
        updateHeight(newRoot.get());
        return newRoot;
    }

    static unique_ptr<Node> rebalance(unique_ptr<Node> node) {
        updateHeight(node.get());
        const int balance = balanceFactor(node);

        if (balance > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(move(node->left));
            }
            return rotateRight(move(node));
        }
        if (balance < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(move(node->right));
            }
            return rotateLeft(move(node));
        }
        return node;
    }

    static unique_ptr<Node> insert(unique_ptr<Node> node, int key,
                                   bool &inserted) {
        if (node == nullptr) {
            inserted = true;
            return make_unique<Node>(key);
        }
        if (key < node->key) {
            node->left = insert(move(node->left), key, inserted);
        } else if (key > node->key) {
            node->right = insert(move(node->right), key, inserted);
        } else {
            return node;
        }
        return rebalance(move(node));
    }

    static unique_ptr<Node> erase(unique_ptr<Node> node, int key,
                                  bool &erased) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = erase(move(node->left), key, erased);
        } else if (key > node->key) {
            node->right = erase(move(node->right), key, erased);
        } else {
            erased = true;
            if (node->left == nullptr) {
                return move(node->right);
            }
            if (node->right == nullptr) {
                return move(node->left);
            }

            Node *successor = node->right.get();
            while (successor->left != nullptr) {
                successor = successor->left.get();
            }
            node->key = successor->key;
            bool ignored = false;
            node->right = erase(move(node->right), successor->key, ignored);
        }
        return rebalance(move(node));
    }

    static void inorder(const Node *node, vector<int> &result) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left.get(), result);
        result.push_back(node->key);
        inorder(node->right.get(), result);
    }
};

int main() {
    AVLTree tree({30, 20, 40, 10, 25, 35, 50, 5});

    assert(tree.contains(25));
    assert(!tree.contains(99));
    assert(tree.insert(45));
    assert(!tree.insert(45));
    assert(tree.erase(40));      // 删除有两个孩子的节点
    assert(tree.erase(5));       // 删除叶子节点
    assert(!tree.erase(99));

    cout << "中序遍历: ";
    for (int value : tree.inorder()) {
        cout << value << ' ';
    }
    cout << "\n节点数: " << tree.size() << "\n树高: " << tree.height() << '\n';
    return 0;
}
