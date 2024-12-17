#include <iostream>
#include <cassert>
#include "Graph.hpp"

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

// Test Functions
void test_is_empty() {
    MinPriorityQueue<double, size_t> pq;
    assertTest(pq.is_empty(), "Queue is initially empty");
    cout << "Empty Priority Queue test passed!" << endl;
}

void test_insert_and_minimum() {
    MinPriorityQueue<double, size_t> pq;
    pq.insert(5, 1);
    pq.insert(3, 2);
    pq.insert(4, 3);

    assertTest(!pq.is_empty(), "Queue is not empty after insertions");
    assertTest(pq.minimum() == 2, "Minimum value is correctly identified (3, 2)");
    cout << "Test insert and minimum PQueue passed!" << endl;
}

void test_extract_min() {
    MinPriorityQueue<double, size_t> pq;
    pq.insert(5, 1);
    pq.insert(3, 2);
    pq.insert(4, 3);

    size_t minElement = pq.extract_min();
    assertTest(minElement == 2, "Extracted minimum is correct (3.0, 2)");
    assertTest(pq.minimum() == 3, "New minimum is correct (4.0, 3)");
    cout << "Test extract min PQueue passed!" << endl;
}

void test_decrease_key() {
    MinPriorityQueue<double, size_t> pq;
    pq.insert(5.0, 1);
    pq.insert(3.0, 2);
    pq.insert(4.0, 3);

    pq.decrease_key(2.0, 1); // Decrease key of (5.0, 1) to (2.0, 1)
    assertTest(pq.minimum() == 1, "Decreased key becomes new minimum");
}


// Test Graph Class
void test_single_vertex() {
    Graph g;
    g.add_vertex(0);
    g.add_edge(0, 0, 1.0);
    assertTest(g.check_edge(0, 0), "Edge added successfully to single vertex");
    g.remove_edge(0, 0);
    assertTest(!g.check_edge(0, 0), "Edge removed successfully");
    g.delete_vertex(0);
    assertTest(!g.check_vertex(0), "Vertex deleted successfully");
    assertTest(g.is_empty(), "Graph is empty after deleting vertex");

    try {
        g.add_edge(0, 0, 1.0);
    } catch (const vertex_exception&) {
        assertTest(true, "Adding edge to nonexistent vertex throws exception");
    }

    cout << "Single vertex test passed!" << endl;
}

void test_multiple_self_loops() {
    Graph g;
    g.add_vertex(0);
    g.add_edge(0, 0, 1.0);
    g.add_edge(0, 0, 2.0);

    assertTest(g.check_edge(0, 0), "Multiple self-loops handled correctly");
    g.update_weight(0, 0, 2.0);
    assertTest(g.check_edge(0, 0), "Weight updated on self-loop edge");

    cout << "Multiple self-loops test passed!" << endl;
}

void test_update_non_existent_edge() {
    Graph g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(1, 2, 1.0);

    try {
        g.update_weight(1, 3, 10.0);
        assertTest(false, "Updating non-existent edge should throw exception");
    } catch (const edge_exception&) {
        assertTest(true, "Non-existent edge update throws exception");
    }
}

void test_multiple_vertices_same_value() {
    Graph g;
    g.add_vertex(100);

    try {
        g.add_vertex(100);
        assertTest(false, "Adding duplicate vertex should throw exception");
    } catch (const vertex_exception&) {
        assertTest(true, "Adding duplicate vertex throws exception");
    }

    assertTest(g.check_vertex(100), "Vertex exists after adding successfully");
    g.delete_vertex(100);
    assertTest(!g.check_vertex(100), "Vertex deleted successfully");

    cout << "Multiple vertices with same value test passed!" << endl;
}

void test_multiple_updates_on_edge() {
    Graph g;
    g.add_vertex(1);
    g.add_edge(1, 1, 1.0);

    g.update_weight(1, 1, 5.0);
    g.update_weight(1, 1, 10.0);
    assertTest(g.check_edge(1, 1), "Edge remains valid after multiple updates");

    cout << "Multiple updates on edge test passed!" << endl;
}

void test_dijkstra_basic() {
    Graph g;

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 2);
    g.add_edge(1, 3, 3);

    auto result = g.dijkstra(1);

    assertTest(result[1].first == 0, "Dijkstra: Distance to source is 0");
    assertTest(result[2].first == 1, "Dijkstra: Distance to vertex 2 is correct");
    assertTest(result[3].first == 3, "Dijkstra: Distance to vertex 3 is correct");

    cout << "Dijkstra basic test passed!" << endl;
}

void test_dijkstra_multiple_path() {
    Graph g;

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);

    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 1);
    g.add_edge(1, 3, 5);
    g.add_edge(3, 4, 1);

    auto result = g.dijkstra(1);

    assertTest(result[1].first == 0, "Dijkstra: Distance to source is 0");
    assertTest(result[2].first == 1, "Dijkstra: Distance to vertex 2 is correct");
    assertTest(result[3].first == 2, "Dijkstra: Shortest path to vertex 3 is correct");
    assertTest(result[4].first == 3, "Dijkstra: Shortest path to vertex 4 is correct");

    cout << "Dijkstra multiple paths test passed!" << endl;
}

// Main Test Runner
int main() {
    // Test priority queue
    test_is_empty();
    test_insert_and_minimum();
    test_extract_min();
    test_decrease_key();


    test_single_vertex();
    test_multiple_self_loops();
    test_update_non_existent_edge();
    test_multiple_vertices_same_value();
    test_multiple_updates_on_edge();
    test_dijkstra_basic();
    test_dijkstra_multiple_path();


    printTestSummary();
    return 0;
}
