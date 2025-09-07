//
// Created by user on 2025/9/7.
//

#include <cstddef>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp;

        Node* p = head;
        Node* np = nullptr;
        Node* new_head = nullptr;

        while (p != nullptr){
            if(np == nullptr){
                new_head = new Node(p->val);
                new_head->random = p->random;
                np = new_head;
            } else{
                np->next = new Node(p->val);
                np->next->random = p->random;
                np = np->next;
            }
            mp[p] = np;

            p = p->next;
        }

        mp[nullptr] = nullptr;
        p = new_head;
        while (p != nullptr){
            p->random = mp[p->random];
            p = p->next;
        }

        return new_head;
    }
};