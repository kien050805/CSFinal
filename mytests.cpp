//========================================================
// James Bui & Kien Le & Huy Phan
// December 2024 - Final Project
// mytests.cpp
// This file contains the tests cases for the Graph and
// MinPriorityQueue class.
//========================================================

#include <iostream>
#include <cassert>
#include "Graph.hpp"
#include "MinPriorityQueue.hpp"

using namespace std;

/**
 * @brief Test Graph with single vertex.
 *
 */
void test_single_vertex()
{
    Graph g;

    g.add_vertex(0);
    g.add_edge(0, 0, 1.0);
    assert(g.check_edge(0, 0));
    g.remove_edge(0, 0);
    assert(!g.check_edge(0, 0));
    g.delete_vertex(0);
    assert(!g.check_vertex(0));
    g.add_edge(0, 0, 1.0);
    assert(g.is_empty());
    g.add_vertex(0);
    g.add_edge(0, 0, -1.0);
    assert(!g.is_empty());
    g.delete_vertex(0);

    cout << "Test single vertex graph passed!" << endl;
}

/**
 * @brief Test Graph with self loops
 *
 */
void test_multiple_self_loops()
{
    Graph g;

    g.add_vertex(0);
    g.add_edge(0, 0, 1.0);
    g.add_edge(0, 0, 2.0);
    assert(g.check_edge(0, 0));
    g.update_weight(0, 0, 2.0);
    assert(g.check_edge(0, 0));

    cout << "Test multiple self-loops test passed!" << endl;
}

/**
 * @brief Test Graph by updating non existence edge.
 *
 */
void test_update_non_existent_edge()
{
    Graph g;

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(1, 2, 1.0);

    try
    {
        g.update_weight(1, 3, 10.0);
    }
    catch (const edge_exception &)
    {
        cout << "Test non-existent edge update test passed!" << endl;
    }
}

/**
 * @brief Test Graph with multiple vertices with same value.
 *
 */
void test_multiple_vertices_same_value()
{
    Graph g;

    g.add_vertex(100);

    try
    {
        g.add_vertex(100);
    }
    catch (const vertex_exception &)
    {
    }

    assert(g.check_vertex(100));
    g.delete_vertex(100);
    assert(!g.check_vertex(100));

    cout << "Test multiple vertices with same value test passed!" << endl;
}

/**
 * @brief Test Graph by updating edge multiple times.
 *
 */
void test_multiple_updates_on_edge()
{
    Graph g;

    g.add_vertex(1);
    g.add_edge(1, 1, 1.0);
    g.update_weight(1, 1, 5.0);
    g.update_weight(1, 1, 10.0);
    assert(g.check_edge(1, 1));

    cout << "Test multiple updates on same edge test passed!" << endl;
}

/**
 * @brief Test Graph Dijkstra's algorithm. Simple version with 3 vertices.
 *
 */
void test_dijkstra_1()
{
    Graph g;

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 2);
    g.add_edge(1, 3, 3);

    auto result = g.dijkstra(1);

    assert(result[1].first == 0);
    assert(result[2].first == 1);
    assert(result[3].first == 3);
    assert(result[2].second == 1);
    assert(result[3].second == 1);
    cout << "Test Dijkstra 1 passed!" << endl;
}

/**
 * @brief Test Graph Dijkstra's algorithm. Harder versions with back and fourth edges
 *
 */
void test_dijkstra_2()
{
    Graph g;

    g.add_vertex(0);
    g.add_vertex(1);
    g.add_vertex(3);
    g.add_vertex(5);
    g.add_vertex(7);
    g.add_vertex(2);
    g.add_vertex(4);
    g.add_vertex(6);

    g.add_edge(2, 0, 5);
    g.add_edge(4, 2, 10);
    g.update_weight(4, 2, 6);
    g.add_edge(3, 1, 3);
    g.add_edge(2, 1, 1);
    g.add_edge(2, 6, 5);
    g.add_edge(2, 5, 5);
    g.add_edge(1, 6, 3);
    g.add_edge(5, 1, 2);
    g.add_edge(5, 7, 5);
    g.add_edge(6, 2, 8);
    g.add_edge(7, 5, 6);
    g.add_edge(7, 6, 1);

    auto result = g.dijkstra(3);

    assert(result[0].first == 19);
    assert(result[0].second == 2);
    assert(result[1].first == 3);
    assert(result[1].second == 3);
    assert(result[2].first == 14);
    assert(result[2].second == 6);
    assert(result[3].first == 0);
    assert(result[3].second == -1);
    assert(result[4].first == INFINITY);
    assert(result[4].second == -1);
    assert(result[5].first == 19);
    assert(result[5].second == 2);
    assert(result[6].first == 6);
    assert(result[6].second == 1);
    assert(result[7].first == 24);
    assert(result[7].second == 5);

    cout << "Test Dijkstra 2 passed!" << endl;
}

/**
 * @brief Test Graph Dijkstra's algorithm. Harder version with multiple vertices and edges.
 *
 */
void test_dijkstra_3()
{
    Graph g;

    for (size_t i = 0; i < 6; ++i)
    {
        g.add_vertex(i);
    }

    g.add_edge(0, 1, 4);
    g.add_edge(0, 2);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 3, 8);
    g.add_edge(2, 4, 10);
    g.add_edge(3, 4, 2);
    g.add_edge(3, 5, 3);
    g.add_edge(4, 5, 4);
    g.remove_edge(4, 5);
    g.add_edge(4, 5, 4);

    auto result = g.dijkstra(0);

    assert(result[0].first == 0);
    assert(result[1].first == 4);
    assert(result[2].first == 1);
    assert(result[3].first == 9);
    assert(result[4].first == 11);
    assert(result[5].first == 12);
    assert(result[1].second == 0);
    assert(result[2].second == 0);
    assert(result[3].second == 2);
    assert(result[4].second == 2);
    assert(result[5].second == 3);

    cout << "Test Dijkstra 3 passed!" << endl;
}

/**
 * @brief Test Graph Operator=. Expected a deep copy.
 *
 */
void test_graph_copy()
{
    Graph g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(1, 2);
    g.add_edge(2, 1);

    Graph h = g;
    h.delete_vertex(2);

    assert(g.check_edge(1, 2));
    assert(g.check_edge(2, 1));
    assert(!h.check_edge(1, 2));
    assert(!h.check_edge(2, 1));

    cout << "Test Graph copy passed!" << endl;
}

/**
 * @brief Test MinPriorityQueue empty.
 *
 */
void test_empty_priority_queue()
{
    MinPriorityQueue<int, string> pq;
    try
    {
        pq.extract_min();
    }
    catch (const heap_underflow_exception &e)
    {
    }

    try
    {
        pq.minimum();
    }
    catch (const heap_underflow_exception &e)
    {
    }

    cout << "Test empty priority queue passed!" << endl;
}

/**
 * @brief Test MinPriorityQueue but increasing key and expect an error.
 *
 */
void test_increase_key()
{
    MinPriorityQueue<int, string> pq;
    pq.insert(10, "A");
    pq.insert(20, "B");

    try
    {
        pq.decrease_key(25, "A");
    }
    catch (const key_exception &e)
    {
    }

    cout << "Test increase key passed!" << endl;
}

/**
 * @brief Test MinPriorityQueue by extract after decrease key.
 *
 */
void test_extract_after_decrease_key()
{
    MinPriorityQueue<int, string> pq;
    pq.insert(10, "A");
    pq.insert(20, "B");
    pq.insert(15, "C");
    pq.decrease_key(5, "B");

    assert(pq.extract_min() == "B");
    assert(pq.extract_min() == "A");
    assert(pq.extract_min() == "C");

    cout << "Test extract after decrease key passed!" << endl;
}

/**
 * @brief Test MinPriorityQueue by decrease non-existence key.
 *
 */
void test_non_existence()
{
    MinPriorityQueue<int, string> pq;
    pq.insert(10, "A");

    try
    {
        pq.decrease_key(5, "B");
    }
    catch (const key_exception &e)
    {
    }

    cout << "Test non existence passed!" << endl;
}

/**
 * @brief @brief Test MinPriorityQueue Operator=. Expected a deep copy.
 * 
 */
void test_queue_copy ()
{
    MinPriorityQueue<int, double> pq;
    pq.insert(10, 10.1);
    pq.insert(11, 11.1);
    pq.insert(12, 9.9);

    MinPriorityQueue<int, double> pq_copy = pq;

    pq_copy.decrease_key(1, 10.1);
    assert(pq_copy.extract_min() == 10.1);
    assert(pq.extract_min() == 10.1);
    assert(pq.extract_min() == 11.1);

    cout << "Test MinPriorityQueue copy passed!" << endl;
}

int main()
{
    test_single_vertex();
    test_multiple_self_loops();
    test_update_non_existent_edge();
    test_multiple_vertices_same_value();
    test_multiple_updates_on_edge();
    test_dijkstra_1();
    test_dijkstra_2();
    test_dijkstra_3();
    test_graph_copy();

    test_empty_priority_queue();
    test_increase_key();
    test_extract_after_decrease_key();
    test_non_existence();
    test_queue_copy();

    cout << "Pass all tests!" << endl;
    return 0;
};