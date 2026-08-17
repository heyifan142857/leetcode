// 分块查找（索引顺序查找）先通过索引确定目标所在的块，再在块内顺序查找。
// 数据只需满足“块间有序”，块内元素可以无序。

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

struct BlockIndex {
    int maxValue; // 当前块的最大值
    size_t begin; // 当前块的起始下标（包含）
    size_t end;   // 当前块的结束下标（不包含）
};

class BlockSearch {
private:
    vector<int> values_;
    vector<BlockIndex> index_;

    void buildIndex(size_t blockSize) {
        if (blockSize == 0) {
            throw invalid_argument("块大小必须大于 0");
        }

        for (size_t begin = 0; begin < values_.size(); begin += blockSize) {
            const size_t end = min(begin + blockSize, values_.size());
            const auto [minimum, maximum] =
                minmax_element(values_.begin() + static_cast<ptrdiff_t>(begin),
                               values_.begin() + static_cast<ptrdiff_t>(end));

            // 只有块间有序，才能根据各块最大值定位候选块。
            if (!index_.empty() && *minimum < index_.back().maxValue) {
                throw invalid_argument("数据不满足块间有序的要求");
            }

            index_.push_back({*maximum, begin, end});
        }
    }

public:
    BlockSearch(vector<int> data, size_t blockSize) : values_(move(data)) {
        buildIndex(blockSize);
    }

    // 返回 target 第一次出现的下标；未找到时返回 -1。
    ptrdiff_t search(int target) const {
        // 索引按块的最大值升序排列，先二分找到第一个可能包含目标的块。
        const auto block = lower_bound(index_.begin(), index_.end(), target,
                                       [](const BlockIndex &item, int value) {
                                           return item.maxValue < value;
                                       });

        if (block == index_.end()) {
            return -1;
        }

        // 块内可以无序，因此使用顺序查找。
        for (size_t i = block->begin; i < block->end; ++i) {
            if (values_[i] == target) {
                return static_cast<ptrdiff_t>(i);
            }
        }
        return -1;
    }

    void printIndex() const {
        cout << "分块索引（最大值, 下标范围）:" << '\n';
        for (const BlockIndex &block : index_) {
            cout << "  (" << block.maxValue << ", [" << block.begin << ", "
                 << block.end << "))" << '\n';
        }
    }
};

int main() {
    // 每三个元素组成一块：块间有序，块内无序。
    BlockSearch blockSearch({1, 4, 3, 8, 6, 7, 12, 11, 10, 18, 16, 15}, 3);
    blockSearch.printIndex();

    for (int target : {11, 14}) {
        const ptrdiff_t position = blockSearch.search(target);
        if (position == -1) {
            cout << "分块查找：未找到 " << target << '\n';
        } else {
            cout << "分块查找：" << target << " 位于下标 " << position << '\n';
        }
    }

    return 0;
}
