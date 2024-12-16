// #include <iostream>
// #include "Graph.cpp"

// using namespace std;

// int main()
// {
//     Graph g;

//     g.add_vertex(1);
//     g.delete_vertex(1);
//     g.add_vertex(1);
//     g.add_vertex(2);
//     g.add_edge(1,2);
//     g.add_edge(2,1,0.1);
//     g.remove_edge(1,2);
//     g.remove_edge(1,2);
//     return 0;
// };

#include <iostream>
#include <cassert>
#include <string>
#include "MinPriorityQueue.hpp"

using namespace std;

// Test case definitions
void test_insert_and_minimum() {
    MinPriorityQueue<int, string> pq;

    pair<int, string> p1(10, "A");
    pair<int, string> p2(5, "B");
    pair<int, string> p3(20, "C");

    pq.insert(p1);
    assert(pq.minimum() == "A");

    pq.insert(p2);
    assert(pq.minimum() == "B"); // B has the smallest key (5)

    pq.insert(p3);
    assert(pq.minimum() == "B"); // Still B
}

void test_extract_min() {
    MinPriorityQueue<int, string> pq;

    pair<int, string> p1(10, "A");
    pair<int, string> p2(5, "B");
    pair<int, string> p3(20, "C");

    pq.insert(p1);
    pq.insert(p2);
    pq.insert(p3);

    assert(pq.extractMin() == "B"); // Smallest value
    assert(pq.minimum() == "A");   // Next smallest is A

    assert(pq.extractMin() == "A");
    assert(pq.minimum() == "C");

    assert(pq.extractMin() == "C");
    assert(pq.is_empty());
}

void test_decrease_key() {
    MinPriorityQueue<int, string> pq;

    pair<int, string> p1(10, "A");
    pair<int, string> p2(20, "B");

    pq.insert(p1);
    pq.insert(p2);

    pair<int, string> p2_new(5, "B");
    pq.decreaseKey(p2, 5); // Update B's key to 5

    assert(pq.minimum() == "B");
    assert(pq.extractMin() == "B");
    assert(pq.minimum() == "A");
}

void test_remove() {
    MinPriorityQueue<int, string> pq;

    pair<int, string> p1(10, "A");
    pair<int, string> p2(5, "B");
    pair<int, string> p3(20, "C");

    pq.insert(p1);
    pq.insert(p2);
    pq.insert(p3);

    pq.remove(p2); // Remove element B
    assert(pq.minimum() == "A"); // A is now the smallest

    pq.remove(p1); // Remove element A
    assert(pq.minimum() == "C");

    pq.remove(p3); // Remove element C
    assert(pq.is_empty());
}

void test_is_empty() {
    MinPriorityQueue<int, string> pq;
    assert(pq.is_empty());

    pair<int, string> p1(10, "A");
    pq.insert(p1);
    assert(!pq.is_empty());

    pq.extractMin();
    assert(pq.is_empty());
}

void test_copy_constructor_and_assignment() {
    MinPriorityQueue<int, string> pq1;

    pair<int, string> p1(10, "A");
    pair<int, string> p2(5, "B");

    pq1.insert(p1);
    pq1.insert(p2);

    MinPriorityQueue<int, string> pq2 = pq1; // Test copy constructor
    assert(pq2.minimum() == pq1.minimum());

    MinPriorityQueue<int, string> pq3;
    pq3 = pq1; // Test assignment operator
    assert(pq3.minimum() == pq1.minimum());
}

// Main function to run all test cases
int main() {
    test_insert_and_minimum();
    cout << "test_insert_and_minimum passed!" << endl;

    test_extract_min();
    cout << "test_extract_min passed!" << endl;

    test_decrease_key();
    cout << "test_decrease_key passed!" << endl;

    test_remove();
    cout << "test_remove passed!" << endl;

    test_is_empty();
    cout << "test_is_empty passed!" << endl;

    test_copy_constructor_and_assignment();
    cout << "test_copy_constructor_and_assignment passed!" << endl;

    cout << "All tests passed!" << endl;
    return 0;
}
