#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Graph.cpp"
using namespace std;

class GraphMap
{
private:
    Graph G;
    size_t n;
    size_t m;
    unordered_map<double, unordered_map<double, size_t> > Coor;
    unordered_map<size_t, unordered_map<size_t, string> > Name;

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

        cout << start_x << " " << start_y << " " << end_x << " " << end_y << endl;
    }

};

void intro()
{
    cout << "Welcome to my CLI route planner! You may enter the letter q at any time to exit." << endl;
}

string get_file()
{
    cout << "Enter a file name to load: ";
    string file;
    cin >> file;
    return file;
}

int main()
{
    intro();
    // string file_name = get_file();
    GraphMap graph_map;

    graph_map.load_file("denison.out");

    while (1)
    {
        double start_x, start_y, end_x, end_y;
        graph_map.get_coordinates(start_x, start_y, end_x, end_y);


    };

    return 0;
}
