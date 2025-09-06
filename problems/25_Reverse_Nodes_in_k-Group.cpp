//
// Created by user on 2025/9/6.
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == nullptr){
            return head;
        }
        ListNode* new_head = nullptr;
        ListNode* cur = head;

        int length = k;

        while (length--){
            if(cur != nullptr){
                ListNode* temp = cur->next;
                cur->next = new_head;
                new_head = cur;
                cur = temp;
            }else{
                ListNode* p = new_head;
                new_head = nullptr;
                while (p != nullptr){
                    ListNode* temp = p->next;
                    p->next = new_head;
                    new_head = p;
                    p = temp;
                }
                return new_head;
            }
        }
        head->next = reverseKGroup(cur, k);
        return new_head;
    }
};