//
// Created by user on 2025/11/1.
//
#include <vector>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *modifiedList(vector<int> &nums, ListNode *head) {
        unordered_set<int> set(nums.begin(), nums.end());

        ListNode *p = head;
        ListNode *newHead = nullptr;
        ListNode *tail = nullptr;
        while (p != nullptr) {
            if (!set.contains(p->val)) {
                if (newHead && tail) {
                    tail->next = new ListNode(p->val);
                    tail = tail->next;
                } else {
                    newHead = new ListNode(p->val);
                    tail = newHead;
                }
            }
            p = p->next;
        }
        return newHead;
    }
};