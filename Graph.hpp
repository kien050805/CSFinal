#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>
#include <vector>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "customexceptions.hpp"

using namespace std;

class Graph
{
private:
    unordered_map<size_t, vector<pair<size_t, double> > > Adj;
    vector<size_t> V;

public:
    Graph();
    Graph(const Graph &G);
    ~Graph();
    Graph &operator=(const Graph &G);

    void add_edge(size_t u, size_t v, double w = 1);
    void remove_edge(size_t u, size_t v);
    void delete_vertex(size_t u);
    void add_vertex(size_t u);

    bool check_vertex(size_t u) const;
    bool check_edge(size_t u, size_t v) const;
    bool is_empty() const;

    static Graph read_from_STDIN();
};

#endif