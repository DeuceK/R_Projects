#ifndef GRAPH_H
#define GRAPH_H

class Graph 
{
public:
    //constructors
    Graph();
    Graph(int vertices);
    //destructor
    ~Graph();
    //Reads in the data from a file
    void readFile(string filename);
    //gets the number of different requested data points
    int getNumEdges() const;
    int getNumVertices() const;
    int getEdgeWeight(string start, string end);
    string getVisited();
    //adds to the data
    void add(string start, string end, int edgeWeight);
    //Breadth first search functions
    string BreadthFirstTraversal(string start);
    //void BreadthFirstTraversalHelper(int startVertex);
    //Depth first search functions
    string DepthFirstTraversal(string start);
    void DepthFirstTraversalHelper(int target);
    //Dijkstra search functions  
    void dijkstra(int graph[5][5]);
    int findVertex(int dist[], bool sptSet[]);
    void getDijkstraPath();

private:
    //Private variables
    string alphabet [27] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",};
    int numberOfVertices;
    int numberOfEdges;
    vector<int> finalVisit;
    vector<string> storage;
    int numVertices, numEdges;
    list<int>* adjLists;
    bool* visited;
    vector<string>* printableList;
    int MAX = 50;
    int graphMAX = 5;
    string dfsString = "";
    string bfsString = "";
    //output array (holds shortest distance from src to i)
    int shortestPath[5];
    //returns true if vertex i is included in shortest (finds path and then checks it as true if in the list)
    bool found[5];
    //unvisits all the vertices
    void unvisitVertices();
};
#endif //GRAPH_H
#include "graph.cpp"