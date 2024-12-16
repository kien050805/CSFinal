#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>
#include <vector>

#ifndef MINPRIORITYQUEUE_HPP
#define MINPRIORITYQUEUE_HPP

#include "customexceptions.hpp"

using namespace std;

template<typename K, typename V>
class MinPriorityQueue
{
private:
    vector<pair<K, V>> heap;

public:
    MinPriorityQueue();
    MinPriorityQueue(const MinPriorityQueue<K, V> &q);
    ~MinPriorityQueue();
    MinPriorityQueue<K, V> &operator=(const MinPriorityQueue<K, V> &q);

    void insert(pair<K, V> &x);
    V minimum();
    V extractMin();
    void decreaseKey(pair<K, V> &x, K key);
    void remove(pair<K, V> &x);
    void heapify(int i);
    int parent(int i) ;
    bool is_empty();

};

#include "MinPriorityQueue.cpp"

#endif
