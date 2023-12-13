#include <iostream>
#include <climits>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
using namespace std;

#include "graph.h"

////////////////////////////////////////////////////////////////////////////////
// This is 80 characters - Keep all lines under 80 characters                 //
////////////////////////////////////////////////////////////////////////////////

// global variable - need better method, but works for testing
// used by graphVisitor
ostringstream graphOut;

// global variable for Djikstra
map<string, int> weight;
map<string, string> previous;

// OK or ERR for tests
template <typename T>
string isOK(const T& got, const T& expected) 
{
    if (got == expected) 
    {
        return "OK: ";
    } else 
    {
        cout << "    Got   " << got << "\n expected " << expected << endl;
        return "ERR: ";
    }
}

void testGraph() 
{
    cout << "testGraph" << endl;
    Graph g;
    g.readFile("graph0.txt");
    cout << isOK(g.getNumVertices(), 3) << "3 vertices" << endl;
    cout << isOK(g.getNumEdges(), 3) << "3 edges" << endl;

    graphOut.str("");
    string gotDFS = g.DepthFirstTraversal("A");
    cout << isOK(gotDFS, "A C B "s) << "DFS" << endl;

    graphOut.str("");
    string gotBFS = g.BreadthFirstTraversal("A");
    cout << isOK(gotBFS, "A C B "s) << "BFS" << endl;
}

void testGraph2()
{
    cout << "\ntestGraph2" << endl;
    Graph t;
    t.readFile("test2.txt");
    cout << isOK(t.getEdgeWeight("A", "B"), 1) << "EDGE WEIGHT" << endl;
    //returns -1 cause the values given were not valid
    cout << isOK(t.getEdgeWeight("A", "Q"), -1) << "EDGE WEIGHT" << endl;
    //should be nothing since we have not done any searching
    cout << isOK(t.getVisited(), ""s) << "GET VISITED" << endl;
}

void dijkstraTest(int graph[5][5]) 
{
    cout << "\ndijkstraTest" << endl;
    Graph t2;
    t2.dijkstra(graph);
    t2.getDijkstraPath();
}

int main() 
{
    testGraph();
    testGraph2();
    //GRAPH FOR TESTING
    int graph[5][5] = 
    { 
        { 0, 4, 0, 0, 5},
        { 4, 0, 8, 0, 2},
        { 0, 8, 0, 7, 1},
        { 0, 0, 7, 0, 0},
        { 0, 0, 0, 9, 2},
    };
    dijkstraTest(graph);
    return 0;
}
