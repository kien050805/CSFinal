#include <iostream>
#include <cassert>
#include "Graph.hpp"

using namespace std;

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

    cout << "Single vertex graph passed!" << endl;
}

void test_multiple_self_loops()
{
    Graph g;

    g.add_vertex(0);
    g.add_edge(0, 0, 1.0);
    g.add_edge(0, 0, 2.0);
    assert(g.check_edge(0, 0));
    g.update_weight(0, 0, 2.0);
    assert(g.check_edge(0, 0));

    cout << "Multiple self-loops test passed!" << endl;
}

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
        cout << "Non-existent edge update test passed!" << endl;
    }
}

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

    cout << "Multiple vertices with same value test passed!" << endl;
}

void test_multiple_updates_on_edge()
{
    Graph g;

    g.add_vertex(1);
    g.add_edge(1, 1, 1.0);
    g.update_weight(1, 1, 5.0);
    g.update_weight(1, 1, 10.0);
    assert(g.check_edge(1, 1));

    cout << "Multiple updates on same edge test passed!" << endl;
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

    assert(result[1].first == 0);
    assert(result[2].first == 1);
    assert(result[3].first == 3);
    assert(result[2].second == 1);
    assert(result[3].second == 1);
    cout << "Dijkstra basic passed!" << endl;
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

    assert(result[1].first == 0);
    assert(result[2].first == 1);
    assert(result[3].first == 2);
    assert(result[4].first == 3);
    assert(result[2].second == 1);
    assert(result[3].second == 2);
    assert(result[4].second == 3);
    cout << "Dijkstra multiple path passed passed!" << endl;
}



int main()
{
    test_single_vertex();
    test_multiple_self_loops();
    test_update_non_existent_edge();
    test_multiple_vertices_same_value();
    test_multiple_updates_on_edge();
    test_dijkstra_basic();
    test_dijkstra_multiple_path();
    cout << "Pass all tests!" << endl;
    return 0;
};