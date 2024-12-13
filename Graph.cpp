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

void Graph::add_edge(int u, int v, double w)
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
        Adj[u].push_back({v, w});
    }
    return;
};

void Graph::remove_edge(int u, int v)
{
    if (!check_vertex(u))
    {
        throw edge_exception();
    }

    for (int i = 0; i < Adj[u].size(); i++)
    {
        if (Adj[u][i].first == v)
        {
            Adj[u].erase(Adj[u].begin() + i);
            return;
        };
    };

    throw edge_exception();
}

void Graph::add_vertex(int u)
{
    if (check_vertex(u))
    {
        throw vertex_exception();
    };
    V.push_back(u);
    Adj.insert({u, vector<pair<int, double>>()});
};

void Graph::delete_vertex(int u)
{
    if (!check_vertex(u))
    {
        throw vertex_exception();
    }

    for (int i = 0; i < V.size(); i++)
    {
        if (check_edge(V[i], u))
        {
            remove_edge(V[i], u);
        };
    }
    Adj.erase(u);
    V.erase(remove(V.begin(), V.end(), u), V.end());
}

bool Graph::check_vertex(int u) const
{
    return Adj.find(u) != Adj.end();
}

bool Graph::check_edge(int u, int v) const
{
    if (!check_vertex(u))
    {
        return false;
    }

    for (const pair<int, double> &edge : Adj.at(u))
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