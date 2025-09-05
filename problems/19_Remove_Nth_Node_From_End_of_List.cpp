//
// Created by user on 2025/9/5.
//
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;

        ListNode* last = nullptr;

        for (int i = 0; i < n; ++i) {
            fast = fast->next;
        }

        while (fast != nullptr){
            fast = fast->next;
            last = slow;
            slow = slow->next;
        }

        if(last == nullptr){
            return head->next;
        }

        last->next = slow->next;

        delete slow;

        return head;
    }
};