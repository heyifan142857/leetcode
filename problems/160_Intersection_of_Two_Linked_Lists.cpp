//
// Created by user on 2025/9/4.
//

#include <cstddef>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> set;
        ListNode* pA = headA;
        ListNode* pB = headB;

        while (pA != nullptr || pB != nullptr){
            if(pA != nullptr){
                if(set.contains(pA)){
                    return pA;
                }
                set.insert(pA);
                pA = pA->next;
            }
            if(pB != nullptr){
                if(set.contains(pB)){
                    return pB;
                }
                set.insert(pB);
                pB = pB->next;
            }
        }
        return NULL;
    }
};