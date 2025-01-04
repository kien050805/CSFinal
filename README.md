# Routeplanner

Here’s a detailed README for your Route Planner program:

Route Planner: Shortest Path Finder
Overview
The Route Planner is a C++ program designed to calculate the shortest path between two geographical coordinates input by the user. It leverages graph data structures to store the locations and their connections and implements Dijkstra’s Algorithm to determine the shortest path efficiently.

Features
Allows users to input geographical coordinates (nodes) and distances (edges).
Builds a graph to represent the connectivity between locations.
Calculates the shortest path between a specified starting point and destination.
Outputs the shortest path and its total distance.
How It Works
Graph Representation:

Each geographical location is a node in the graph.
The connections between locations (with distances) are edges.
User Input:

The user provides the number of locations, their coordinates, and the connections between them, including distances.
Dijkstra’s Algorithm:

The program uses Dijkstra’s Algorithm to compute the shortest path from the starting point to the destination.
Output:

Displays the shortest path as a sequence of locations.
Shows the total distance of the shortest path.

