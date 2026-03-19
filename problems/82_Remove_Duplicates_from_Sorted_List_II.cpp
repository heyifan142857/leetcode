// 82. Remove Duplicates from Sorted List II
// Created automatically
// Created at 2026-03-19 11:24:57

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* temp = new ListNode(0, head);
        ListNode* prev = temp;
        while (prev->next) {
            ListNode* current = prev->next;
            while (current->next && current->val == current->next->val) {
                current = current->next;
            }
            if (prev->next != current) {
                prev->next = current->next;
            } else {
                prev = prev->next;
            }
        }
        return temp->next;
    }
};