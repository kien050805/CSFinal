//========================================================
// James Bui & Kien Le & Huy Phan
// December 2024 - Final Project
// Class.cpp
// This file contains the implementation for the Graph class 
// methods.
//========================================================

#include "Graph.hpp"
#include "algorithm"
#include "cmath"
using namespace std;

/**
 * @brief Construct a new Graph:: Graph object.
 * 
 */
Graph::Graph() {};

/**
 * @brief Construct a new Graph:: Graph object.
 * 
 * @param G: Graph object to be copied.
 */
Graph::Graph(const Graph &G)
{
    Adj = G.Adj;
    V = G.V;
};

/**
 * @brief Destroy the Graph:: Graph object.
 * 
 */
Graph::~Graph() {};

/**
 * @brief Operator= operator overloading using deep copy.
 * 
 * @param G: Graph object to be copied.
 * @return Graph& 
 */
Graph &Graph::operator=(const Graph &G)
{
    Adj = G.Adj;
    V = G.V;
    return *this;
};

/**
 * @brief Adds an edge between two vertices in the Graph with a specified weight.
 * 
 * @param u: The source vertex.
 * @param v: The destination vertex.
 * @param w: The weight of the edge between vertices u and v.
 */
void Graph::add_edge(size_t u, size_t v, double w)
{

    if (check_vertex(u) && check_vertex(v) && !check_edge(u, v))
    {
        Adj[u].push_back(make_pair(v, w));
    }
    return;
};

/**
 * @brief Removes the edge between two vertices in the Graph.
 * 
 * @param u: The source vertex.
 * @param v: The destination vertex.
 */
void Graph::remove_edge(size_t u, size_t v)
{
    if (!check_vertex(u))
    {
        throw edge_exception();
    }

    for (size_t i = 0; i < Adj[u].size(); i++)
    {
        if (Adj[u][i].first == v)
        {
            Adj[u].erase(Adj[u].begin() + i);
            return;
        };
    };

    throw edge_exception();
}

/**
 * @brief Updates the weight of an existing edge between two vertices in the Graph.
 * 
 * @param u: The source vertex.
 * @param v: The destination vertex.
 * @param w: The new weight for the edge between u and v.
 */
void Graph::update_weight(size_t u, size_t v, double w)
{
    if (check_vertex(u) && check_vertex(v))
    {
        for (pair<size_t, double> &edge : Adj.at(u))
        {
            if (edge.first == v)
            {
                edge.second = w;
                return;
            }
        }
        throw vertex_exception();
    }
    else
    {
        throw edge_exception();
    };
}

/**
 * @brief Adds a new vertex to the Graph.
 * 
 * @param u: Vertex to be added.
 */
void Graph::add_vertex(size_t u)
{
    if (check_vertex(u))
    {
        throw vertex_exception();
    }

    V.push_back(u);

    Adj.insert({u, vector<pair<size_t, double>>()});
}

/**
 * @brief Delete a vertex from the Graph.
 * 
 * @param u: Vertex to be deleted.
 */
void Graph::delete_vertex(size_t u)
{
    if (!check_vertex(u))
    {
        throw vertex_exception();
    }

    for (size_t i = 0; i < V.size(); i++)
    {
        if (check_edge(V[i], u))
        {
            remove_edge(V[i], u);
        };
    }
    Adj.erase(u);
    V.erase(find(V.begin(), V.end(), u));
}

/**
 * @brief Checks if a vertex exists in the Graph.
 * 
 * @param u: Vertex to check.
 * @return true: Vertex is in the Graph.
 * @return false: Vertex is not in the Graph.
 */
bool Graph::check_vertex(size_t u) const
{
    return Adj.find(u) != Adj.end();
}

/**
 * @brief Checks if an edge exists in the Graph.
 * 
 * @param u: The source vertex.
 * @param v: The destination vertex.
 * @return true: The edge (u,v) is in the Graph.
 * @return false: The edge (u,v) is not in the Graph.
 */
bool Graph::check_edge(size_t u, size_t v) const
{
    if (!check_vertex(u))
    {
        return false;
    }
    for (const pair<size_t, double> &edge : Adj.at(u))
    {
        if (edge.first == v)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if the Graph is empty
 * 
 * @return true: The Graph is empty
 * @return false: The Graph is not empty
 */
bool Graph::is_empty() const
{
    return V.empty();
}


/**
 * @brief Performs Dijkstra's algorithm to find the shortest path from a start vertex.
 * 
 * @param start: The index of the starting vertex for Dijkstra's algorithm.
 * @return unordered_map<size_t, pair<double, size_t>>
 *      An unordered map where the key is the vertex and the value is a pair:
 *         - The first element of the pair is the shortest distance from the `start` vertex to the current vertex.
 *         - The second element of the pair is the preceding vertex on the shortest path.
 */
unordered_map<size_t, pair<double, size_t>> Graph::dijkstra(size_t start)
{
    unordered_map<size_t, pair<double, size_t>> map;

    if (is_empty())
    {
        return map;
    }

    for (size_t i = 0; i < V.size(); ++i)
    {
        map[V[i]] = {INFINITY, -1};
    }

    map[start].first = 0;

    MinPriorityQueue<double, size_t> pqueue;

    for (size_t i = 0; i < V.size(); ++i)
    {
        pqueue.insert(map[V[i]].first, V[i]);
    }

    while (!pqueue.is_empty())
    {
        size_t u = pqueue.extract_min();
        double dist_u = map[u].first; 

        for (const auto& neighbor : Adj[u])
        {
            size_t v = neighbor.first;
            double weight = neighbor.second;
            if (map[v].first > dist_u + weight)
            {
                map[v].first = dist_u + weight;
                map[v].second = u;
                pqueue.decrease_key(map[v].first, v);
            }
        }
    }

    return map;
}