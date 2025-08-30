//
// Created by user on 2025/8/30.
//
#include <map>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::map<ListNode *, int> myMap;
        ListNode* p = head;
        while (p != NULL)
        {
            if (myMap.find(p) != myMap.end()) {
                return p;
            }
            myMap[p] = 1;
            p = p->next;
        }
        return NULL;
    }
};