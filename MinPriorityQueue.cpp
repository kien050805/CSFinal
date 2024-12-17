//========================================================
// James Bui & Kien Le & Huy Phan
// December 2024 - Final Project
// MinPriorityQueue.cpp
// This file contains the implementation for the MinPriorityQueue
// class methods.
//========================================================

#include "MinPriorityQueue.hpp"
#include "cmath"
using namespace std;

/**
 * @brief Construct a new Min Priority Queue< K,  V>:: Min Priority Queue object.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 */
template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue() {}

/**
 * @brief Construct a new Min Priority Queue< K,  V>:: Min Priority Queue object.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 * @param q: MinPriorityQueue< K, V> object to be copied.
 */
template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(const MinPriorityQueue<K, V> &q)
{
    heap = q.heap;
}

/**
 * @brief Destroy the Min Priority Queue< K,  V>:: Min Priority Queue object.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 */
template <typename K, typename V>
MinPriorityQueue<K, V>::~MinPriorityQueue() {}

/**
 * @brief Operator= operator overloading using deep copy.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 * @param q: MinPriorityQueue< K, V> object to be copied.
 * @return MinPriorityQueue<K, V>&
 */
template <typename K, typename V>
MinPriorityQueue<K, V> &MinPriorityQueue<K, V>::operator=(const MinPriorityQueue<K, V> &q)
{
    heap = q.heap;
    return *this;
}

/**
 * @brief Look up the value with minimum key of the MinPriorityQueue
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 * @return V: Value of the minimum.
 */
template <typename K, typename V>
V MinPriorityQueue<K, V>::minimum() const
{
    if (is_empty())
    {
        throw heap_underflow_exception();
    }
    return heap[0].second;
}

/**
 * @brief Checks if the MinPriorityQueue is empty.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 * @return true: The MinPriorityQueue is empty.
 * @return false: The MinPriorityQueue is not empty.
 */
template <typename K, typename V>
bool MinPriorityQueue<K, V>::is_empty() const
{
    return heap.empty();
}

/**
 * @brief Inserts a new element <key, value> into the MinPriorityQueue.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for value.
 * @param key: The priority key for the new element. Smaller keys indicate higher priority.
 * @param value: The value associated with the given key.
 */
template <typename K, typename V>
void MinPriorityQueue<K, V>::insert(K key, V value)
{
    heap.push_back(make_pair(INFINITY, value));
    decrease_key(key, value);
}

/**
 * @brief Extracts the minimum element from the MinPriorityQueue.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for key.
 * @return V: The value associated with the minimum key in the queue.
 */
template <typename K, typename V>
V MinPriorityQueue<K, V>::extract_min()
{
    size_t size = heap.size();
    if (size == 0)
        throw heap_underflow_exception();

    pair<K, V> root = heap[0];
    heap[0] = heap[size - 1];
    heap.pop_back();

    if (!heap.empty())
        heapify(0);

    return root.second;
}

/**
 * @brief Decreases the key of a specific element in the MinPriorityQueue.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for key.
 * @param key: The new, decreased key for the element. Must be smaller than or equal to the current key.
 * @param value: The value identifying the element whose key should be decreased.
 */
template <typename K, typename V>
void MinPriorityQueue<K, V>::decrease_key(K key, V value)
{
    size_t index = -1;
    for (size_t i = 0; i < heap.size(); i++)
    {
        if (heap[i].second == value)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        throw key_exception();
    }

    if (key != INFINITY && key >= heap[index].first)
    {
        throw key_exception();
    };
    heap[index].first = key;

    while (index > 0 && heap[parent(index)].first > heap[index].first)
    {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

/**
 * @brief Maintains the heap property by recursively ensuring the element at index i satisfies the min-heap condition.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for key.
 * @param i: The index of the element in the heap that may violate the heap property.
 */
template <typename K, typename V>
void MinPriorityQueue<K, V>::heapify(size_t i)
{
    size_t size = heap.size();
    size_t smallest = i;
    size_t left_child = left(i);
    size_t right_child = right(i);

    if (right_child < size && heap[right_child].first < heap[smallest].first)
        smallest = right_child;

    if (left_child < size && heap[left_child].first < heap[smallest].first)
        smallest = left_child;

    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

/**
 * @brief Compute the parent index of i.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for key.
 * @param i: The index of i.
 * @return size_t: the index of parent of i.
 */
template <typename K, typename V>
size_t MinPriorityQueue<K, V>::parent(size_t i) const
{
    return (i - 1) / 2;
}

/**
 * @brief Compute the left child index of i.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for key.
 * @param i: The index of i.
 * @return size_t: the index of the left child of i.
 */
template <typename K, typename V>
size_t MinPriorityQueue<K, V>::left(size_t i) const
{
    return 2 * i + 1;
}

/**
 * @brief Compute the right child index of i.
 *
 * @tparam K: Templated class for key.
 * @tparam V: Templated class for key.
 * @param i: The index of i.
 * @return size_t: the index of the right child of i.
 */
template <typename K, typename V>
size_t MinPriorityQueue<K, V>::right(size_t i) const
{
    return 2 * i + 2;
}