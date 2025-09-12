//
// Created by user on 2025/9/11.
//
#include <string>
#include <vector>
using namespace std;

struct Node{
    char var;
    vector<Node*> son;
    Node():var('0'), son({}){}
    Node(char c):var(c), son({}){}
};

class Trie {
    Node* head;
public:
    Trie() {
        head = new Node;
    }

    void insert(string word) {
        Node* p = head;
        for (auto c: word) {
            bool exist = false;
            for (auto son: p->son) {
                if(son != nullptr && c == son->var){
                    p = son;
                    exist = true;
                    break;
                }
            }
            if(!exist){
                Node* newNode = new Node(c);
                p->son.push_back(newNode);
                p = newNode;
            }
        }
        p->son.push_back(nullptr);
    }

    bool search(string word) {
        Node* p = head;
        for (auto c: word) {
            bool exist = false;
            for (auto son: p->son) {
                if(son != nullptr && c == son->var){
                    p = son;
                    exist = true;
                    break;
                }
            }
            if(!exist){
                return false;
            }
        }
        for (auto son: p->son) {
            if(son == nullptr){
                return true;
            }
        }
        return false;
    }

    bool startsWith(string prefix) {
        Node* p = head;
        for (auto c: prefix) {
            bool exist = false;
            for (auto son: p->son) {
                if(son != nullptr && c == son->var){
                    p = son;
                    exist = true;
                    break;
                }
            }
            if(!exist){
                return false;
            }
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */