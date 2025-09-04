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
    ListNode* reverseList(ListNode* head) {
        ListNode* p = head;
        ListNode* ans = nullptr;
        while (p!= nullptr){
            ListNode* newNode = new ListNode(p->val, ans);
            ans = newNode;
            p = p->next;
        }
        return ans;
    }
};