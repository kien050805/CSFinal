#include <iostream>
#include "Graph.cpp"

using namespace std;

int main()
{
    Graph g;

    g.add_vertex(1);
    g.delete_vertex(1);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(1,2);
    g.add_edge(2,1,0.1);
    return 0;
};