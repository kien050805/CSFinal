#include "MinPriorityQueue.hpp"
#include <bits/stdc++.h>

template <typename T>
MinPriorityQueue<T>::MinPriorityQueue() 
{}

template <typename T>
MinPriorityQueue<T>::MinPriorityQueue(const MinPriorityQueue &q) 
{
    heap = q.heap;
}

template <typename T>
MinPriorityQueue<T>::~MinPriorityQueue() 
{}

template <typename T>
MinPriorityQueue<T> &MinPriorityQueue<T>::operator=(const MinPriorityQueue<T> &q) 
{
    heap = q.heap;
    return *this;
}

template <typename T>
void MinPriorityQueue<T>::insert(T x) 
{
    
    heap.push_back(x);
    decreaseKey(x, x);
}

template <typename T>
void MinPriorityQueue<T>::minimum() 
{
    return heap[0];
}

template <typename T>
T MinPriorityQueue<T>::extractMin() 
{
    int size = heap.size();
     if (size <= 0)
        return -1;  // Indicates that the heap is empty
    if (size == 1) {
        return heap[0];
    }

    // Store the minimum value, and remove it
    T root = heap[0];
    heap[0] = heap[size - 1];
    heap.pop_back();

    // Heapify the root node after deletion
    heapify(0);  
    return root;
}

template <typename T>
int MinPriorityQueue<T>::parent(int i) 
{
    return int(i / 2);
}


template <typename T>
void MinPriorityQueue<T>::decreaseKey(T x) 
{
    auto i = find(heap.start(), heap.end(), x);
    while (i > 1 && heap[parent(i)] > heap[i])
    {
        swap(heap[parent(i)], heap[i]);
        i = parent(i);
    }
    
}

template <typename T>
void MinPriorityQueue<T>::remove(T x) 
{
    auto i = find(heap.start(), heap.end(), x);
    swap(heap[i], heap[heap.size() - 1]);
    heap.pop_back();
    heapify(i);
}

template <typename T>
void MinPriorityQueue<T>::heapify(int i)
{
    int size = heap.size();
    int smallest = i;    
    //  Find the Left child index
    int left = 2 * i + 1;    
        // Find the Right child index
    int right = 2 * i + 2;   
    
    // If left child is smaller than root
    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    // If right child is smaller than the smallest so far
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        swap(heap[i], heap[smallest]);  
        heapify(smallest);                
    }
}
