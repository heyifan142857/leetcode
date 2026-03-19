// 92. Reverse Linked List II
// Created automatically
// Created at 2026-03-19 10:56:12

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* temp = new ListNode(0, head);
        ListNode* prev = temp;

        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }

        ListNode* current = prev->next;

        for (int i = 0; i < right - left; ++i) {
            ListNode* nextNode = current->next;
            current->next = nextNode->next;
            nextNode->next = prev->next;
            prev->next = nextNode;
        }

        return temp->next;
    }
};