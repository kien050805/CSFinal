#include "MinPriorityQueue.hpp"
#include <algorithm> 
#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue() 
{}

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(const MinPriorityQueue<K, V> &q) 
{
    heap = q.heap;
}

template <typename K, typename V>
MinPriorityQueue<K, V>::~MinPriorityQueue() 
{}

template <typename K, typename V>
MinPriorityQueue<K, V> &MinPriorityQueue<K, V>::operator=(const MinPriorityQueue<K, V> &q) 
{
    heap = q.heap;
    return *this;
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::insert(pair<K, V> &x) 
{
    heap.push_back(x);
    decreaseKey(x, x.first);
}

template <typename K, typename V>
V MinPriorityQueue<K, V>::minimum() 
{
    return heap[0].second;
}

template <typename K, typename V>
V MinPriorityQueue<K, V>::extractMin() 
{
    int size = heap.size();
    if (size <= 0)
        throw heap_underflow_exception();  // Indicates that the heap is empty

    // Store the minimum value, and remove it
    pair<K, V> root = heap[0];
    heap[0] = heap[size - 1];
    heap.pop_back();

    // Heapify the root node after deletion
    heapify(0);  
    return root.second;
}

template <typename K, typename V>
int MinPriorityQueue<K, V>::parent(int i) 
{
    return int((i - 1)/ 2);
}


template <typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(pair<K, V> &x, K key) 
{
    if (key > x.first)
        throw Key_exception();
    
    auto it = find(heap.begin(), heap.end(), x);
    int index = std::distance(heap.begin(), it);
    heap[index].first = key;
    while (index > 0 && heap[parent(index)].first > heap[index].first)
    {
        swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
    
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::remove(pair<K, V> &x) 
{
    auto it = find(heap.begin(), heap.end(), x);
    int index = std::distance(heap.begin(), it);
    swap(heap[index], heap[heap.size() - 1]);
    heap.pop_back();
    heapify(index);
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::heapify(int i)
{
    int size = heap.size();
    int smallest = i;    
    //  Find the Left child index
    int left = 2 * i + 1;    
        // Find the Right child index
    int right = 2 * i + 2;   
    
    // If left child is smaller than root
    if (left < size && heap[left].first < heap[smallest].first)
        smallest = left;

    // If right child is smaller than the smallest so far
    if (right < size && heap[right].first < heap[smallest].first)
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        swap(heap[i], heap[smallest]);  
        heapify(smallest);                
    }
}
template <typename K, typename V>
bool MinPriorityQueue<K, V>::is_empty()
{
    return heap.empty();
}

