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
    bool load_file()
    {
        string file_name;
        cout << "Enter a file name to load: ";
        cin >> file_name;
        ifstream file(file_name);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return false;
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
            if (file.peek() == ' ')
            {
                file.ignore();
                getline(file, s);
            }
            G.add_edge(u, v, w);
            Name[u][v] = s;
        }

        file.close();
        cout << "Graph successfully loaded!" << endl;
        cin.ignore();

        return true;
    }

    void get_coordinates(double &start_x, double &start_y, double &end_x, double &end_y)
    {
        string input;
        stringstream ss;

        while (true)
        {
            cout << "Enter start coordinates (format: x y): ";
            getline(cin, input);

            if (input == "q")
            {
                quit();
            }

            ss.clear();
            ss.str(input);
            
            if (ss >> start_x >> start_y && ss.eof())
            {
                break;
            }

            cerr << "Invalid input. Please try again." << endl;
        }

        while (true)
        {
            cout << "Enter end coordinates (format: x y): ";
            getline(cin, input);

            if (input == "q")
            {
                quit();
            }

            ss.clear();
            ss.str(input);
            if (ss >> end_x >> end_y && ss.eof())
            {
                break;
            }

            cerr << "Invalid input. Please try again." << endl;
        }
    }

    void find_path()
    {
        double start_x, start_y, end_x, end_y;
        get_coordinates(start_x, start_y, end_x, end_y);
            if (Coor.find(start_x) == Coor.end() || Coor[start_x].find(start_y) == Coor[start_x].end())
    {
        cerr << "Error: Start coordinates (" << start_x << ", " << start_y << ") are not valid!" << endl;
        return;
    }

    if (Coor.find(end_x) == Coor.end() || Coor[end_x].find(end_y) == Coor[end_x].end())
    {
        cerr << "Error: End coordinates (" << end_x << ", " << end_y << ") are not valid!" << endl;
        return;
    }


        size_t start_vertex = Coor[start_x][start_y];
        size_t end_vertex = Coor[end_x][end_y];

        auto path = G.dijkstra(start_vertex);

        cout << "The shortest path from (" << start_x << ", " << start_y << ") to ("
             << end_x << ", " << end_y << ") is: ";

        if (path.find(end_vertex) == path.end() || path[end_vertex].first == INFINITY)
        {
            cout << "No path found!" << endl;
            return;
        }

        vector<size_t> result_path;
        size_t current_vertex = end_vertex;

        while (current_vertex != -1)
        {
            result_path.push_back(current_vertex);
            current_vertex = path[current_vertex].second;
        }

        reverse(result_path.begin(), result_path.end());

        for (size_t i = 0; i < result_path.size(); ++i)
        {
            cout << result_path[i];
            if (i != result_path.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << " and it has weight " << path[end_vertex].first << "." << endl;
    }

    void quit()
    {
        cout << "Exiting... Thank you for using me instead of Google Maps!" << endl;
        exit(0);
    }
};

int main()
{
    cout << "Welcome to my CLI route planner! You may enter the letter q at any time to exit." << endl;

    GraphMap graph_map;

    while (true)
    {
        if (graph_map.load_file())
        {
            break;
        };
    };

    while (1)
    {
        graph_map.find_path();
    };
    return 0;
}
