#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <functional>
#include <stdexcept>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
private:
    std::vector<T> heap;
    Compare comp;

    void heapifyUp(int index) {
        while (index > 0 && comp(heap[parent(index)], heap[index])) {
            std::swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int maxIndex = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        if (left < heap.size() && comp(heap[maxIndex], heap[left])) {
            maxIndex = left;
        }
        if (right < heap.size() && comp(heap[maxIndex], heap[right])) {
            maxIndex = right;
        }
        
        if (index != maxIndex) {
            std::swap(heap[index], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }
    
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    PriorityQueue() {}
    
    void push(const T& item) {
        heap.push_back(item);
        heapifyUp(heap.size() - 1);
    }
    
    void pop() {
        if (heap.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
    
    T top() const {
        if (heap.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap[0];
    }
    
    bool isEmpty() const {
        return heap.empty();
    }
    
    int size() const {
        return heap.size();
    }
};

#endif
