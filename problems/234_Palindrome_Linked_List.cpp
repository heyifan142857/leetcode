//
// Created by user on 2025/9/4.
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
    bool isPalindrome(ListNode* head) {
        ListNode* p = head;
        ListNode* new_head = nullptr;

        while (p != nullptr){
            ListNode* new_node = new ListNode(p->val, new_head);
            new_head = new_node;
            p = p->next;
        }

        ListNode* p1 = head;
        ListNode* p2 = new_head;

        while (p1 != nullptr && p2 != nullptr){
            if(p1->val != p2->val){
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        return true;
    }
};