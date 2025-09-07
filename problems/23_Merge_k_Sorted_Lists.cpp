//
// Created by user on 2025/9/7.
//

#include <vector>
#include <queue>
#include <functional>
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto comp = [](ListNode* a, ListNode* b){
            return a->val>b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);
        for (auto node: lists) {
            if(node != nullptr){
                pq.push(node);
            }
        }

        ListNode* new_head = nullptr;
        ListNode* p = nullptr;

        while (!pq.empty()){
            ListNode* cur = pq.top();

            pq.pop();
            if(cur->next != nullptr){
                pq.push(cur->next);
            }

            if(p == nullptr){
                new_head = new ListNode(cur->val);
                p = new_head;
            }else{
                p->next = new ListNode(cur->val);
                p = p->next;
            }
        }
        return new_head;
    }
};