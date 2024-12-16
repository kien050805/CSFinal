#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Graph.hpp"
using namespace std;

class GraphMap
{
private:
    Graph G;
    size_t n;
    size_t m;
    unordered_map<double, unordered_map<double, size_t>> Coor;
    unordered_map<size_t, unordered_map<size_t, string>> Name;

public:
    void load_file(const string &file_name)
    {
        ifstream file(file_name);
        if (!file.is_open())
        {
            cerr << "Error opening file!" << endl;
            return;
        }

        file >> n >> m;

        for (size_t i = 0; i < n; i++)
        {
            size_t id;
            double x, y;
            string s;
            file >> id >> x >> y;
            Coor[x][y] = id;
            G.add_vertex(id);
        }

        for (size_t i = 0; i < m; ++i)
        {
            size_t u, v;
            double w;
            string s;
            file >> u >> v >> w;
            file.ignore();
            getline(file, s);
            G.add_edge(u, v, w);
            Name[u][v] = s;
        }

        file.close();
        cout << "Graph successfully loaded!" << endl;
    }

    void get_coordinates(double &start_x, double &start_y, double &end_x, double &end_y)
    {
        cout << "Enter a start coordinate: ";

        string input;
        getline(cin, input);
        if (input == "q")
        {
            exit(0);
        }
        else
        {
            stringstream ss(input);
            ss >> start_x >> start_y;
        }

        cout << "Enter an end coordinate: ";
        getline(cin, input);
        if (input == "q")
        {
            exit(0);
        }
        else
        {
            stringstream ss(input);
            ss >> end_x >> end_y;
        }
    }
    void find_path()
    {
        double start_x, start_y, end_x, end_y;
        get_coordinates(start_x, start_y, end_x, end_y);

        auto path = G.dijkstra(Coor[start_x][start_y]);

        cout << "The shortest path from (" << start_x << ", " << start_y << ") to ("
             << end_x << ", " << end_y << ") is: ";

        if (path.find(Coor[end_x][end_y]) == path.end())
        {
            cout << "No path found!" << endl;
            return;
        }

        vector<size_t> result_path;
        size_t current_vertex = Coor[end_x][end_y];

        while (current_vertex != -1)
        {
            result_path.push_back(current_vertex);
            current_vertex = path[current_vertex].second;
        }

        reverse(result_path.begin(), result_path.end());

        for (const auto &vertex : result_path)
        {
            cout << vertex << " -> ";
        }
        cout << endl;
    }
};


string get_file()
{
    cout << "Welcome to my CLI route planner! You may enter the letter q at any time to exit." << endl;
    cout << "Enter a file name to load: ";
    string file;
    cin >> file;
    return file;
}

int main()
{  
    string file = get_file();

    GraphMap graph_map;

    graph_map.load_file(file);

    while (1)
    {
        graph_map.find_path();
    };

    return 0;
}
