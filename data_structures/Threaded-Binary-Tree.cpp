// 线索二叉树利用空孩子指针保存节点的中序前驱或后继。
// 线索化后，无需递归或辅助栈即可完成中序遍历。

#include <iostream>

using namespace std;

// 指针域的类型：Link 表示指向孩子，Thread 表示指向前驱或后继。
enum class PointerTag { Link, Thread };

struct ThreadedTreeNode {
    int value;
    ThreadedTreeNode *left;
    ThreadedTreeNode *right;
    PointerTag leftTag;
    PointerTag rightTag;

    explicit ThreadedTreeNode(int value)
        : value(value), left(nullptr), right(nullptr),
          leftTag(PointerTag::Link), rightTag(PointerTag::Link) {}
};

// 教材中的全局变量 pre：始终指向中序遍历时刚访问过的节点。
ThreadedTreeNode *pre = nullptr;

class InorderThreadedBinaryTree {
public:
    explicit InorderThreadedBinaryTree(ThreadedTreeNode *root)
        : root_(root), threaded_(false) {}

    InorderThreadedBinaryTree(const InorderThreadedBinaryTree &) = delete;
    InorderThreadedBinaryTree &
    operator=(const InorderThreadedBinaryTree &) = delete;

    ~InorderThreadedBinaryTree() { destroy(root_); }

    // 按中序遍历的顺序建立前驱、后继线索。
    void createInThread() {
        if (threaded_) {
            return;
        }

        pre = nullptr;
        if (root_ != nullptr) {
            inThread(root_);

            // 中序遍历的最后一个节点没有后继，单独补上右线索标志。
            if (pre->right == nullptr) {
                pre->rightTag = PointerTag::Thread;
            }
        }
        threaded_ = true;
    }

    // 利用线索完成中序遍历，不需要递归或辅助栈。
    void inorderTraversal() const {
        ThreadedTreeNode *current = first(root_);

        while (current != nullptr) {
            cout << current->value << ' ';

            if (current->rightTag == PointerTag::Thread) {
                // right 是后继线索，可直接到达下一个节点。
                current = current->right;
            } else {
                // right 是右孩子，下一个节点是右子树最左侧的节点。
                current = first(current->right);
            }
        }
        cout << endl;
    }

private:
    ThreadedTreeNode *root_;
    bool threaded_;

    // 中序遍历二叉树，并在访问节点时完成线索化。
    static void inThread(ThreadedTreeNode *node) {
        if (node != nullptr) {
            inThread(node->left);
            visit(node);
            inThread(node->right);
        }
    }

    // 建立当前节点的前驱线索，以及前驱节点的后继线索。
    static void visit(ThreadedTreeNode *node) {
        if (node->left == nullptr) {
            node->left = pre;
            node->leftTag = PointerTag::Thread;
        }

        if (pre != nullptr && pre->right == nullptr) {
            pre->right = node;
            pre->rightTag = PointerTag::Thread;
        }

        pre = node;
    }

    static ThreadedTreeNode *first(ThreadedTreeNode *node) {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->leftTag == PointerTag::Link && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 释放节点时只沿孩子指针递归，不能沿线索递归，否则会重复访问节点。
    static void destroy(ThreadedTreeNode *node) {
        if (node == nullptr) {
            return;
        }

        if (node->leftTag == PointerTag::Link) {
            destroy(node->left);
        }
        if (node->rightTag == PointerTag::Link) {
            destroy(node->right);
        }
        delete node;
    }
};

int main() {
    // 用于演示的二叉树：
    //
    //             1
    //          ┌──┴──┐
    //          2     3
    //        ┌─┴─┐   └─┐
    //        4   5     6
    //           ┌┘
    //           7
    //
    // 中序遍历结果：4 2 7 5 1 3 6
    auto *root = new ThreadedTreeNode(1);
    root->left = new ThreadedTreeNode(2);
    root->right = new ThreadedTreeNode(3);
    root->left->left = new ThreadedTreeNode(4);
    root->left->right = new ThreadedTreeNode(5);
    root->right->right = new ThreadedTreeNode(6);
    root->left->right->left = new ThreadedTreeNode(7);

    InorderThreadedBinaryTree tree(root);
    tree.createInThread();

    cout << "中序遍历: ";
    tree.inorderTraversal();

    return 0;
}
