// 61. Rotate List
// Created automatically
// Created at 2026-03-19 11:35:56

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // Find the length of the list and the last node
        int len = 1;
        ListNode* last = head;
        while (last->next) {
            last = last->next;
            len++;
        }

        // Adjust k to be within the bounds of the list length
        k %= len;
        if (k == 0) return head;

        // Find the new tail (the node at position len - k - 1)
        ListNode* newTail = head;
        for (int i = 0; i < len - k - 1; ++i) {
            newTail = newTail->next;
        }

        // The new head is the node after the new tail
        ListNode* newHead = newTail->next;

        // Break the list at the new tail
        newTail->next = nullptr;

        // Connect the last node to the original head
        last->next = head;

        return newHead;

    }
};