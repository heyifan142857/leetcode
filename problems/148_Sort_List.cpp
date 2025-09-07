//
// Created by user on 2025/9/7.
//
#include <algorithm>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        vector<int> v;
        ListNode* p = head;
        while (p != nullptr){
            v.push_back(p->val);
            p = p->next;
        }
        sort(v.begin(), v.end());

        ListNode* new_head = nullptr;
        p = nullptr;

        for (int i = 0; i < v.size(); ++i) {
            if(i==0){
                new_head = new ListNode(v[i]);
                p = new_head;
            } else{
                p->next = new ListNode(v[i]);
                p = p->next;
            }
        }
        return new_head;
    }
};