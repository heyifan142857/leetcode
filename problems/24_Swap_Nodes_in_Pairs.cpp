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
    ListNode* swapPairs(ListNode* head) {
        ListNode* p = head;
        ListNode* tail = nullptr;

        while (p != nullptr && p->next != nullptr){
            if(tail == nullptr){
                ListNode* temp = p->next;
                head->next = temp->next;
                temp->next = head;
                head = temp;
                tail = head->next;
                p = head->next->next;
            }else{
                ListNode* temp = p->next;
                p->next = p->next->next;
                temp->next = p;
                tail->next = temp;
                tail = p;
                p = p->next;
            }
        }

        return head;
    }
};