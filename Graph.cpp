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

    if (check_vertex(u) && check_vertex(v) && !check_edge(u, v))
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