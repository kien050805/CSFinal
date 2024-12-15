#include "Graph.hpp"
using namespace std;

Graph::Graph() {};

Graph::Graph(const Graph &G)
{
    Adj = G.Adj;
    V = G.V;
};

Graph::~Graph() {};

Graph &Graph::operator=(const Graph &G)
{
    Adj = G.Adj;
    V = G.V;
    return *this;
};

void Graph::add_edge(size_t u, size_t v, double w)
{
    if (!check_vertex(u))
    {
        return;
    }
    if (!check_vertex(v))
    {
        return;
    }
    if (!check_edge(u, v))
    {
        Adj[u].push_back(make_pair(v, w));
    }
    return;
};

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

void Graph::add_vertex(size_t u)
{
    if (check_vertex(u))
    {
        throw vertex_exception();
    }

    V.push_back(u);

    Adj[u];
}

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

bool Graph::check_vertex(size_t u) const
{
    return Adj.find(u) != Adj.end();
}

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

bool Graph::is_empty() const
{
    return V.empty();
}


unordered_map<size_t, pair<size_t, double>> Graph::dijsktra(size_t v)
{
    unordered_map<size_t, pair<size_t, double>> map;
    if (is_empty())
    {
        return map;
    };

    for (int i = 1; i < V.size() + 1; i++)
    {
        map.insert({V[i], pair<int, int>(-1, 0)}); // -1 as unreachable, 0 as NIL
    }

    map[v].first = 0;
    map[v].second = -1;

    

}
