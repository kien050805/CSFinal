#ifndef MINPRIORITYQUEUE_HPP
#define MINPRIORITYQUEUE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include "customexceptions.hpp"

using namespace std;

template <typename K, typename V>
class MinPriorityQueue
{
private:
    vector<pair<K, V>> heap;

    void heapify(size_t i);
    size_t parent(size_t i) const;
    size_t left(size_t i) const;
    size_t right(size_t i) const;

public:
    MinPriorityQueue();
    MinPriorityQueue(const MinPriorityQueue<K, V> &q);
    ~MinPriorityQueue();
    MinPriorityQueue<K, V> &operator=(const MinPriorityQueue<K, V> &q);

    V minimum() const;
    bool is_empty() const;

    void insert(K key, V value);
    V extract_min();
    void decrease_key(K key, V value);
};

#include "MinPriorityQueue.cpp"

#endif
