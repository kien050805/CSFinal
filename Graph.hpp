#include <iostream>
#include <list>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <vector>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "customexceptions.hpp"

using namespace std;

class Graph
{
private:
    unordered_map<int, vector<pair<int, double>>> Adj;
    vector<int> V;

public:
    Graph();
    Graph(const Graph &G);
    ~Graph();
    Graph &operator=(const Graph &G);

    void add_edge(int u, int v, double w = 1);
    void remove_edge(int u, int v);
    void delete_vertex(int u);
    void add_vertex(int u);

    bool check_vertex(int u) const;
    bool check_edge(int u, int v) const;
    bool is_empty() const;

    static Graph read_from_STDIN();
};

#endif