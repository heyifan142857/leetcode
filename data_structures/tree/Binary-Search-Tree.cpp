// 查找长度是查找过程中比较关键字的次数；平均查找长度 ASL 是各关键字
// 查找长度按其查找概率得到的加权平均值。等概率时，就是所有节点深度
// （根节点按第 1 层计算）的算术平均值。
// BST 的查找、插入和删除均为 O(h)。随机构造时平均为 O(log n)，但按有序
// 序列构造会退化成链：最坏一次查找需要 n 次比较，成功查找的 ASL 为
// (n + 1) / 2，操作复杂度退化为 O(n)。

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class BinarySearchTree {
public:
    BinarySearchTree() = default;

    // 构造：按照给定顺序逐个插入关键字。
    explicit BinarySearchTree(const vector<int> &values) {
        for (int value : values) {
            insert(value);
        }
    }

    // 查找：返回树中是否存在 key。
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
    bool insert(int key) { return insert(root_, key); }

    // 删除：不存在的关键字不改变树。
    bool erase(int key) { return erase(root_, key); }

    vector<int> inorder() const {
        vector<int> result;
        inorder(root_.get(), result);
        return result;
    }

    size_t size() const { return size_; }

    // 假设每个关键字被查找的概率相同，返回成功查找的 ASL。
    double averageSearchLength() const {
        if (size_ == 0) {
            return 0.0;
        }
        return static_cast<double>(sumSearchLengths(root_.get(), 1)) /
               static_cast<double>(size_);
    }

private:
    struct Node {
        explicit Node(int key) : key(key) {}

        int key;
        unique_ptr<Node> left;
        unique_ptr<Node> right;
    };

    unique_ptr<Node> root_;
    size_t size_ = 0;

    bool insert(unique_ptr<Node> &node, int key) {
        if (node == nullptr) {
            node = make_unique<Node>(key);
            ++size_;
            return true;
        }
        if (key == node->key) {
            return false;
        }
        return key < node->key ? insert(node->left, key)
                               : insert(node->right, key);
    }

    bool erase(unique_ptr<Node> &node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key < node->key) {
            return erase(node->left, key);
        }
        if (key > node->key) {
            return erase(node->right, key);
        }

        if (node->left == nullptr) {
            node = move(node->right);
        } else if (node->right == nullptr) {
            node = move(node->left);
        } else {
            Node *successor = node->right.get();
            while (successor->left != nullptr) {
                successor = successor->left.get();
            }
            node->key = successor->key;
            eraseNodeWithoutCounting(node->right, successor->key);
        }
        --size_;
        return true;
    }

    static void eraseNodeWithoutCounting(unique_ptr<Node> &node, int key) {
        if (key < node->key) {
            eraseNodeWithoutCounting(node->left, key);
        } else if (key > node->key) {
            eraseNodeWithoutCounting(node->right, key);
        } else if (node->left == nullptr) {
            node = move(node->right);
        } else {
            node = move(node->left);
        }
    }

    static void inorder(const Node *node, vector<int> &result) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left.get(), result);
        result.push_back(node->key);
        inorder(node->right.get(), result);
    }

    static size_t sumSearchLengths(const Node *node, size_t level) {
        if (node == nullptr) {
            return 0;
        }
        return level + sumSearchLengths(node->left.get(), level + 1) +
               sumSearchLengths(node->right.get(), level + 1);
    }
};

int main() {
    BinarySearchTree tree({8, 3, 10, 1, 6, 14, 4, 7, 13});

    assert(tree.contains(6));
    assert(!tree.contains(2));
    assert(tree.insert(2));
    assert(!tree.insert(2));
    assert(tree.erase(3));       // 删除有两个孩子的节点
    assert(!tree.erase(100));

    cout << "中序遍历: ";
    for (int value : tree.inorder()) {
        cout << value << ' ';
    }
    cout << "\n节点数: " << tree.size()
         << "\n成功查找的 ASL: " << tree.averageSearchLength() << '\n';
    return 0;
}
