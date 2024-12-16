#include "MinPriorityQueue.hpp"
#include "cmath"
using namespace std;

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue() {}

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(const MinPriorityQueue<K, V> &q)
{
    heap = q.heap;
}

template <typename K, typename V>
MinPriorityQueue<K, V>::~MinPriorityQueue() {}

template <typename K, typename V>
MinPriorityQueue<K, V> &MinPriorityQueue<K, V>::operator=(const MinPriorityQueue<K, V> &q)
{
    heap = q.heap;
    return *this;
}

template <typename K, typename V>
V MinPriorityQueue<K, V>::minimum() const
{
    return heap[0].second;
}

template <typename K, typename V>
bool MinPriorityQueue<K, V>::is_empty() const
{
    return heap.empty();
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::insert(K key, V value)
{
    heap.push_back(make_pair(INFINITY, value));
    decrease_key(key, value);
}

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

template <typename K, typename V>
void MinPriorityQueue<K, V>::decrease_key(K key, V value)
{
    size_t index = -1;
    for (size_t i = 0; i < heap.size(); i++)
    {
        if (heap[i].second == value )
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

template <typename K, typename V>
void MinPriorityQueue<K, V>::heapify(size_t i)
{
    size_t size = heap.size();
    size_t smallest = i;
    size_t left_child = left(i);
    size_t right_child = right(i);

    if (left_child < size && heap[left_child].first < heap[smallest].first)
        smallest = left_child;

    if (right_child < size && heap[right_child].first < heap[smallest].first)
        smallest = right_child;

    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

template <typename K, typename V>
size_t MinPriorityQueue<K, V>::parent(size_t i) const
{
    return (i - 1) / 2;
}

template <typename K, typename V>
size_t MinPriorityQueue<K, V>::left(size_t i) const
{
    return 2 * i + 1;
}

template <typename K, typename V>
size_t MinPriorityQueue<K, V>::right(size_t i) const
{
    return 2 * i + 2;
}