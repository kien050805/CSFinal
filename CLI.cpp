//========================================================
// James Bui & Kien Le & Huy Phan
// December 2024 - Final Project
// CLI.cpp
// This file contains the main program to run CLI
// Find path for every two startpoint and endpoint
//========================================================
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <sstream>
#include "Graph.hpp"
using namespace std;

class GraphMap
{
private:
    Graph G;
    size_t n;
    size_t m;
    unordered_map<double, unordered_map<double, size_t>> ID;
    unordered_map<size_t, pair<double, double>> Coor;
    unordered_map<size_t, unordered_map<size_t, string>> Name;

public:
    /**
     * @brief This function is used to load a file for data 
     * 
     * @return: If the file is loaded correctly return true,
     * else return false
     */
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
            ID[x][y] = id;
            Coor[id] = make_pair(x,y);
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
                while (file.peek() == ' ')
                {
                    file.ignore();
                }
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


    /**
    * @brief This function is used to get the coordinates from user  
    * @param start_x: x - coordinate of start point 
    * @param start_y: y - coordinate of start point 
    * @param end_x: x - coordinate of end point 
    * @param end_y: y - coordinate of end point 
    * @return: not return anything but get input from user
     */
    void get_coordinates(double &start_x, double &start_y, double &end_x, double &end_y)
    {
        string input;
        stringstream ss;

        while (true)
        {
            cout << "Enter start coordinates: ";
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
            cout << "Enter end coordinates: ";
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

    /**
    * @brief This function is used to validate the input is correct
    * @param start_x: x - coordinate of start point 
    * @param start_y: y - coordinate of start point 
    * @param end_x: x - coordinate of end point 
    * @param end_y: y - coordinate of end point 
    * @return: true if the user enter correct coordinates
     */
    bool validate_input(double start_x, double start_y, double end_x, double end_y)
    {
        if (ID.find(start_x) == ID.end() || ID[start_x].find(start_y) == ID[start_x].end())
        {
            cerr << "Error: Start coordinates (" << start_x << ", " << start_y << ") are not valid!" << endl;
            return false;
        }

        if (ID.find(end_x) == ID.end() || ID[end_x].find(end_y) == ID[end_x].end())
        {
            cerr << "Error: End coordinates (" << end_x << ", " << end_y << ") are not valid!" << endl;
            return false;
        }

        return true;
    }

    /**
    * @brief This function is used to find paths betwen start point and endpoint
    * @return: the paths connecting startpoint and endpoint
     */
    void find_path()
    {
        double start_x, start_y, end_x, end_y;
        while (true) 
        {
            get_coordinates(start_x, start_y, end_x, end_y);

            if (validate_input(start_x, start_y, end_x, end_y))
            {
                break; 
            }

            cout << "Invalid input! Please try again." << endl;
        }

        size_t start_vertex = ID[start_x][start_y];
        size_t end_vertex = ID[end_x][end_y];

        auto path = G.dijkstra(start_vertex);

        cout << "The shortest path from (" << start_x << ", " << start_y << ") to ("
             << end_x << ", " << end_y << ") is: ";

        if (path.find(end_vertex) == path.end() || path[end_vertex].first == numeric_limits<double>::max())
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
            cout << "(" << Coor[result_path[i]].first << ", " << Coor[result_path[i]].second << ")";
            if (i != result_path.size() - 1)
            {
                cout << " -> ";
            }

            if (Name[result_path[i]][result_path[i+1]] != "")
            {
                cout << "(" << Name[result_path[i]][result_path[i+1]] << ")" << " -> ";
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
