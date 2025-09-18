//
// Created by user on 2025/9/18.
//
#include <queue>
#include <functional>
using namespace std;

class MedianFinder {
    priority_queue<int, vector<int>, greater<>> min_heap;
    priority_queue<int> max_heap;
public:
    MedianFinder() {

    }

    void swap(){
        int max_heap_top = max_heap.top();
        max_heap.pop();
        int min_heap_top = min_heap.top();
        min_heap.pop();

        min_heap.push(max_heap_top);
        max_heap.push(min_heap_top);
    }

    void addNum(int num) {
        if(min_heap.empty() || min_heap.size() <= max_heap.size()){
            min_heap.push(num);
        }else{
            max_heap.push(num);
        }
        if(max_heap.empty()){
            return;
        }
        while (max_heap.top() > min_heap.top()){
            swap();
        }
    }

    double findMedian() {
        int total = min_heap.size()+max_heap.size();
        if(total%2 == 0){
            return 1.0*(min_heap.top()+max_heap.top())/2;
        }else{
            return 1.0*min_heap.top();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */