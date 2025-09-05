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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        ListNode* p1 = list1;
        ListNode* p2 = list2;

        while (p1 != nullptr || p2 != nullptr){
            if(p1 != nullptr && p2 != nullptr){
                if(p1->val < p2->val){
                    if(tail == nullptr){
                        head = p1;
                        tail = p1;
                    }else{
                        tail->next = new ListNode(p1->val);
                        tail = tail->next;
                    }
                    p1 = p1->next;
                }else{
                    if(tail == nullptr){
                        head = p2;
                        tail = p2;
                    }else{
                        tail->next = new ListNode(p2->val);
                        tail = tail->next;
                    }
                    p2 = p2->next;
                }
            }else if(p1 != nullptr){
                if(tail == nullptr){
                    head = p1;
                    tail = p1;
                }else{
                    tail->next = new ListNode(p1->val);
                    tail = tail->next;
                }
                p1 = p1->next;
            }else{
                if(tail == nullptr){
                    head = p2;
                    tail = p2;
                }else{
                    tail->next = new ListNode(p2->val);
                    tail = tail->next;
                }
                p2 = p2->next;
            }
        }

        return head;
    }
};