//
// Created by user on 2025/9/4.
//
#include <cstddef>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr){
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast != nullptr){
            if(fast == slow){
                return true;
            }
            slow = slow->next;
            fast = fast->next;
            if(slow == nullptr || fast == nullptr){
                return false;
            }
            fast = fast->next;
        }

        return false;
    }
};