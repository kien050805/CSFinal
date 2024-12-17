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

int testsPassed = 0;
int testsFailed = 0;

void assertTest(bool condition, const string& testName) {
    if (condition) {
        testsPassed++;
        cout << "[PASS] " << testName << endl;
    } else {
        testsFailed++;
        cout << "[FAIL] " << testName << endl;
    }
}

void printTestSummary() {
    cout << "\n--- Test Summary ---" << endl;
    cout << "Tests Passed: " << testsPassed << endl;
    cout << "Tests Failed: " << testsFailed << endl;
    if (testsFailed == 0) {
        cout << "All tests passed!" << endl;
    } else {
        cout << "Some tests failed. Please review the failed cases." << endl;
    }
}

/**
 * @brief Test Graph with single vertex.
 *
 */
void test_single_vertex()
{
    Graph G;

    G.add_vertex(0);
    assertTest(G.check_vertex(0), "Vertex 0 added successfully");
    G.add_edge(0, 0, 1.0);
    assertTest(G.check_edge(0, 0), "Self-loop (0 -> 0) added successfully");
    G.remove_edge(0, 0);
    assertTest(!G.check_edge(0, 0), "Self-loop (0 -> 0) removed successfully");
    G.delete_vertex(0);
    assertTest(!G.check_vertex(0), "Vertex 0 deleted successfully");
    assertTest(G.is_empty(), "Graph is empty after deleting vertex 0");
    G.add_edge(0, 0, 1.0);
    assertTest(G.is_empty(), "Edge addition fails on deleted vertex");
    G.add_vertex(0);
    G.add_edge(0, 0, -1.0);
    assertTest(!G.is_empty(), "Graph is not empty after re-adding vertex 0");

    cout << "Test single vertex graph completed!" << endl;
}


/**
 * @brief Test Graph with self loops
 *
 */
void test_multiple_self_loops()
{
    Graph G;

    G.add_vertex(0);
    G.add_edge(0, 0, 1.0);
    assertTest(G.check_edge(0, 0), "Self-loop (0 -> 0) with weight 1.0 added successfully");

    G.add_edge(0, 0, 2.0);
    assertTest(G.check_edge(0, 0), "Self-loop (0 -> 0) with weight 2.0 added successfully");

    G.update_weight(0, 0, 2.0);
    assertTest(G.check_edge(0, 0), "Self-loop (0 -> 0) weight updated to 2.0 successfully");

    cout << "Test multiple self-loops completed!" << endl;
}


/**
 * @brief Test Graph by updating non existence edge.
 *
 */
void test_update_non_existent_edge()
{
    Graph G;

    G.add_vertex(1);
    G.add_vertex(2);
    G.add_edge(1, 2, 1.0);

    bool exceptionCaught = false;

    try
    {
        G.update_weight(1, 3, 10.0);
    }
    catch (const edge_exception &)
    {
        exceptionCaught = true;
    }

    assertTest(exceptionCaught, "Update weight on non-existent edge throws exception");
}

/**
 * @brief Test Graph with multiple vertices with same value.
 *
 */
void test_multiple_vertices_same_value()
{
    Graph G;

    G.add_vertex(100);
    assertTest(G.check_vertex(100), "Vertex 100 added successfully");

    bool exceptionCaught = false;

    try
    {
        G.add_vertex(100);
    }
    catch (const vertex_exception &)
    {
        exceptionCaught = true;
    }

    assertTest(exceptionCaught, "Exception thrown when adding duplicate vertex 100");

    G.delete_vertex(100);
    assertTest(!G.check_vertex(100), "Vertex 100 deleted successfully");

    cout << "Test multiple vertices with same value completed!" << endl;
}


/**
 * @brief Test Graph by updating edge multiple times.
 *
 */
void test_multiple_updates_on_edge()
{
    Graph G;

    G.add_vertex(1);
    G.add_edge(1, 1, 1.0);
    assertTest(G.check_edge(1, 1), "Edge (1 -> 1) with weight 1.0 added successfully");

    G.update_weight(1, 1, 5.0);
    assertTest(G.check_edge(1, 1), "Edge (1 -> 1) updated to weight 5.0 successfully");

    G.update_weight(1, 1, 10.0);
    assertTest(G.check_edge(1, 1), "Edge (1 -> 1) updated to weight 10.0 successfully");

    cout << "Test multiple updates on same edge completed!" << endl;
}


/**
 * @brief Test Graph Dijkstra's algorithm. Simple version with 3 vertices.
 *
 */
void test_dijkstra_1()
{
    Graph G;

    G.add_vertex(1);
    G.add_vertex(2);
    G.add_vertex(3);
    G.add_edge(1, 2, 1);
    G.add_edge(2, 3, 2);
    G.add_edge(1, 3, 3);

    auto result = G.dijkstra(1);

    assertTest(result[1].first == 0, "Vertex 1 distance is 0 (start vertex)");
    assertTest(result[2].first == 1, "Vertex 2 distance is 1 via vertex 1");
    assertTest(result[3].first == 3, "Vertex 3 distance is 3 via vertex 1");
    assertTest(result[2].second == 1, "Vertex 2 predecessor is 1");
    assertTest(result[3].second == 1, "Vertex 3 predecessor is 1");

    cout << "Test Dijkstra 1 completed!" << endl;
}


/**
 * @brief Test Graph Dijkstra's algorithm. Harder versions with back and fourth edges
 *
 */
void test_dijkstra_2()
{
    Graph G;

    G.add_vertex(0);
    G.add_vertex(1);
    G.add_vertex(3);
    G.add_vertex(5);
    G.add_vertex(7);
    G.add_vertex(2);
    G.add_vertex(4);
    G.add_vertex(6);

    G.add_edge(2, 0, 5);
    G.add_edge(4, 2, 10);
    G.update_weight(4, 2, 6);
    G.add_edge(3, 1, 3);
    G.add_edge(2, 1, 1);
    G.add_edge(2, 6, 5);
    G.add_edge(2, 5, 5);
    G.add_edge(1, 6, 3);
    G.add_edge(5, 1, 2);
    G.add_edge(5, 7, 5);
    G.add_edge(6, 2, 8);
    G.add_edge(7, 5, 6);
    G.add_edge(7, 6, 1);

    auto result = G.dijkstra(3);

    assertTest(result[0].first == 19, "Vertex 0 distance is 19");
    assertTest(result[0].second == 2, "Vertex 0 predecessor is 2");

    assertTest(result[1].first == 3, "Vertex 1 distance is 3");
    assertTest(result[1].second == 3, "Vertex 1 predecessor is 3");

    assertTest(result[2].first == 14, "Vertex 2 distance is 14");
    assertTest(result[2].second == 6, "Vertex 2 predecessor is 6");

    assertTest(result[3].first == 0, "Vertex 3 distance is 0");
    assertTest(result[3].second == -1, "Vertex 3 predecessor is -1");

    assertTest(result[4].first == numeric_limits<double>::max(), "Vertex 4 distance is INFINITY");
    assertTest(result[4].second == -1, "Vertex 4 predecessor is -1");

    assertTest(result[5].first == 19, "Vertex 5 distance is 19");
    assertTest(result[5].second == 2, "Vertex 5 predecessor is 2");

    assertTest(result[6].first == 6, "Vertex 6 distance is 6");
    assertTest(result[6].second == 1, "Vertex 6 predecessor is 1");

    assertTest(result[7].first == 24, "Vertex 7 distance is 24");
    assertTest(result[7].second == 5, "Vertex 7 predecessor is 5");

    cout << "Test Dijkstra 2 completed!" << endl;
}


/**
 * @brief Test Graph Dijkstra's algorithm. Harder version with multiple vertices and edges.
 *
 */
void test_dijkstra_3()
{
    Graph G;

    for (size_t i = 0; i < 6; ++i)
    {
        G.add_vertex(i);
    }

    G.add_edge(0, 1, 4);
    G.add_edge(0, 2, 1);
    G.add_edge(1, 2, 2);
    G.add_edge(1, 3, 5);
    G.add_edge(2, 3, 8);
    G.add_edge(2, 4, 10);
    G.add_edge(3, 4, 2);
    G.add_edge(3, 5, 3);
    G.add_edge(4, 5, 4);
    G.remove_edge(4, 5);
    G.add_edge(4, 5, 4);

    auto result = G.dijkstra(0);

    assertTest(result[0].first == 0, "Vertex 0 distance is 0 (start vertex)");
    assertTest(result[1].first == 4, "Vertex 1 distance is 4");
    assertTest(result[2].first == 1, "Vertex 2 distance is 1");
    assertTest(result[3].first == 9, "Vertex 3 distance is 9");
    assertTest(result[4].first == 11, "Vertex 4 distance is 11");
    assertTest(result[5].first == 12, "Vertex 5 distance is 12");

    assertTest(result[1].second == 0, "Vertex 1 predecessor is 0");
    assertTest(result[2].second == 0, "Vertex 2 predecessor is 0");
    assertTest(result[3].second == 2, "Vertex 3 predecessor is 2");
    assertTest(result[4].second == 2, "Vertex 4 predecessor is 2");
    assertTest(result[5].second == 3, "Vertex 5 predecessor is 3");

    cout << "Test Dijkstra 3 completed!" << endl;
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

    assertTest(g.check_edge(1, 2), "Original graph retains edge (1 -> 2)");
    assertTest(g.check_edge(2, 1), "Original graph retains edge (2 -> 1)");
    assertTest(!h.check_edge(1, 2), "Copied graph no longer has edge (1 -> 2)");
    assertTest(!h.check_edge(2, 1), "Copied graph no longer has edge (2 -> 1)");

    cout << "Test Graph copy passed!" << endl;
}


/**
 * @brief Test MinPriorityQueue empty.
 *
 */
void test_empty_priority_queue()
{
    MinPriorityQueue<int, string> pq;

    bool exceptionCaught1 = false, exceptionCaught2 = false;

    try { pq.extract_min(); }
    catch (const heap_underflow_exception &e) { exceptionCaught1 = true; }

    try { pq.minimum(); }
    catch (const heap_underflow_exception &e) { exceptionCaught2 = true; }

    assertTest(exceptionCaught1, "Extract_min throws heap_underflow_exception on empty queue");
    assertTest(exceptionCaught2, "Minimum throws heap_underflow_exception on empty queue");

    cout << "Test empty priority queue passed!" << endl;
}


/**
 * @brief Test MinPriorityQueue but increasing key and expect an error.
 *
 */
void test_decrease_key()
{
    MinPriorityQueue<int, string> pq;
    pq.insert(10, "A");
    pq.insert(20, "B");

    bool exceptionCaught = false;

    try { pq.decrease_key(50, "A"); }
    catch (const key_exception &e) { exceptionCaught = true; }

    assertTest(exceptionCaught, "Decrease key throws exception when key increases");

    cout << "Test decrease key passed!" << endl;
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

    assertTest(pq.extract_min() == "B", "Extract_min returns B after decrease_key");
    assertTest(pq.extract_min() == "A", "Extract_min returns A after B");
    assertTest(pq.extract_min() == "C", "Extract_min returns C last");

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

    bool exceptionCaught = false;

    try { pq.decrease_key(5, "B"); }
    catch (const key_exception &e) { exceptionCaught = true; }

    assertTest(exceptionCaught, "Decrease key throws exception for non-existent key");

    cout << "Test non existence passed!" << endl;
}

/**
 * @brief @brief Test MinPriorityQueue Operator=. Expected a deep copy.
 * 
 */
void test_queue_copy()
{
    MinPriorityQueue<int, double> pq;
    pq.insert(10, 10.1);
    pq.insert(11, 11.1);
    pq.insert(12, 9.9);

    MinPriorityQueue<int, double> pq_copy = pq;

    pq_copy.decrease_key(1, 10.1);
    assertTest(pq_copy.extract_min() == 10.1, "Copied queue extracts 10.1 after decrease_key");
    assertTest(pq.extract_min() == 10.1, "Original queue extracts 10.1 (unaltered)");
    assertTest(pq.extract_min() == 11.1, "Original queue extracts 11.1 next");

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
    test_decrease_key();
    test_extract_after_decrease_key();
    test_non_existence();
    test_queue_copy();

    printTestSummary();
    cout << "Pass all tests!" << endl;
    return 0;
};