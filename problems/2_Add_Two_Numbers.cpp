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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l2 != nullptr){
            l1->val += l2->val;
            if(l1->val>9){
                l1->val -= 10;
                if(l1->next == nullptr){
                    l1->next = new ListNode(1);
                }else{
                    l1->next->val++;
                }
            }
            if(l1->next == nullptr){
                l1->next = l2->next;
                return l1;
            }
        }else{
            while (l1->next != nullptr || l1->val>9){
                if(l1->val>9){
                    l1->val -= 10;
                    if(l1->next == nullptr){
                        l1->next = new ListNode(1);
                    }else{
                        l1->next->val++;
                    }
                }
                l1 = l1->next;
            }
            return l1;
        }
        addTwoNumbers(l1->next, l2->next);
        return l1;
    }
};