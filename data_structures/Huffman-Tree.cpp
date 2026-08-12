// 哈夫曼树反复合并权值最小的两棵树，从而得到带权路径长度最小的二叉树。
// 本示例使用哈夫曼树生成前缀编码，并演示字符串的编码与解码。

#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct HuffmanNode {
    char symbol;
    int weight;
    size_t order;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char symbol, int weight, size_t order,
                HuffmanNode* left = nullptr, HuffmanNode* right = nullptr)
        : symbol(symbol),
          weight(weight),
          order(order),
          left(left),
          right(right) {}

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

class HuffmanTree {
public:
    explicit HuffmanTree(const vector<pair<char, int>>& frequencies)
        : root_(nullptr), nextOrder_(0) {
        build(frequencies);
        buildCodes(root_, "");
    }

    HuffmanTree(const HuffmanTree&) = delete;
    HuffmanTree& operator=(const HuffmanTree&) = delete;

    const string& codeOf(char symbol) const {
        const auto position = codes_.find(symbol);
        if (position == codes_.end()) {
            throw invalid_argument("字符不在哈夫曼树中");
        }
        return position->second;
    }

    string encode(const string& text) const {
        string result;
        for (char symbol : text) {
            result += codeOf(symbol);
        }
        return result;
    }

    string decode(const string& bits) const {
        if (root_ == nullptr) {
            if (bits.empty()) {
                return "";
            }
            throw invalid_argument("空哈夫曼树不能解码非空编码");
        }

        // 只有一种字符时，约定它的编码为 0。
        if (root_->isLeaf()) {
            string result;
            for (char bit : bits) {
                if (bit != '0') {
                    throw invalid_argument("编码只能包含 0 和 1");
                }
                result += root_->symbol;
            }
            return result;
        }

        string result;
        HuffmanNode* current = root_;
        for (char bit : bits) {
            if (bit == '0') {
                current = current->left;
            } else if (bit == '1') {
                current = current->right;
            } else {
                throw invalid_argument("编码只能包含 0 和 1");
            }

            if (current->isLeaf()) {
                result += current->symbol;
                current = root_;
            }
        }

        if (current != root_) {
            throw invalid_argument("编码在一个完整字符结束前中断");
        }
        return result;
    }

private:
    struct CompareNode {
        bool operator()(const HuffmanNode* lhs,
                        const HuffmanNode* rhs) const {
            if (lhs->weight != rhs->weight) {
                return lhs->weight > rhs->weight;
            }
            return lhs->order > rhs->order;
        }
    };

    vector<unique_ptr<HuffmanNode>> nodes_;
    HuffmanNode* root_;
    size_t nextOrder_;
    unordered_map<char, string> codes_;

    HuffmanNode* createNode(char symbol, int weight,
                            HuffmanNode* left = nullptr,
                            HuffmanNode* right = nullptr) {
        nodes_.push_back(make_unique<HuffmanNode>(
            symbol, weight, nextOrder_++, left, right));
        return nodes_.back().get();
    }

    void build(const vector<pair<char, int>>& frequencies) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> trees;

        for (const auto& [symbol, weight] : frequencies) {
            if (weight <= 0) {
                throw invalid_argument("字符权值必须为正数");
            }
            if (codes_.count(symbol) != 0) {
                throw invalid_argument("字符不能重复");
            }

            // 先借用 codes_ 记录已经出现的字符，建树后会重新写入编码。
            codes_[symbol] = "";
            trees.push(createNode(symbol, weight));
        }
        codes_.clear();

        while (trees.size() > 1) {
            HuffmanNode* left = trees.top();
            trees.pop();
            HuffmanNode* right = trees.top();
            trees.pop();

            HuffmanNode* parent = createNode(
                '\0', left->weight + right->weight, left, right);
            trees.push(parent);
        }

        if (!trees.empty()) {
            root_ = trees.top();
        }
    }

    void buildCodes(HuffmanNode* node, const string& prefix) {
        if (node == nullptr) {
            return;
        }
        if (node->isLeaf()) {
            codes_[node->symbol] = prefix.empty() ? "0" : prefix;
            return;
        }

        buildCodes(node->left, prefix + '0');
        buildCodes(node->right, prefix + '1');
    }
};

int main() {
    const vector<pair<char, int>> frequencies = {
        {'A', 5}, {'B', 9}, {'C', 12},
        {'D', 13}, {'E', 16}, {'F', 45}
    };
    HuffmanTree tree(frequencies);

    cout << "哈夫曼编码:" << endl;
    for (const auto& [symbol, weight] : frequencies) {
        cout << symbol << " (权值 " << weight << "): "
             << tree.codeOf(symbol) << endl;
    }

    const string text = "FACE";
    const string bits = tree.encode(text);
    cout << "原字符串: " << text << endl;
    cout << "编码结果: " << bits << endl;
    cout << "解码结果: " << tree.decode(bits) << endl;

    return 0;
}
