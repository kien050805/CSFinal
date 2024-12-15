#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>
#include <vector>

#ifndef MINPRIORITYQUEUE_HPP
#define MINPRIORITYQUEUE_HPP

#include "customexceptions.hpp"

using namespace std;

template<typename T>
class MinPriorityQueue
{
private:
    vector<T> heap;

public:
    MinPriorityQueue();
    MinPriorityQueue(const MinPriorityQueue<T> &q);
    ~MinPriorityQueue();
    MinPriorityQueue<T> &operator=(const MinPriorityQueue<T> &q);

    void insert(T x);
    void minimum();
    T extractMin();
    void decreaseKey(T x);
    void remove(T x);
    void heapify(int i);
    int parent(int i) ;


};

#endif
