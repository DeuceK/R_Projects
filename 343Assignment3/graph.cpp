//empty constructor
Graph::Graph()
{
    numVertices = MAX;
    adjLists = new list<int>[MAX];
    visited = new bool[MAX];
    printableList = new vector<string>;
}

//constructor with given size
Graph::Graph(int vertices) 
{
    numVertices = vertices;
    adjLists = new list<int>[vertices];
    visited = new bool[vertices];
    printableList = new vector<string>;
}

//destructor
Graph::~Graph()
{
    numVertices, visited = 0;
    delete adjLists;
    delete printableList;
}

// Add edges to the graph
void Graph::add(string start, string end, int edgeWeight) 
{
    int startInt;
    int endInt;
    for(int i = 0;i < 26;i++)
    {
        if(alphabet[i] == start)
        {
            startInt = i;
        }
        if(alphabet[i] == end)
        {
            endInt = i;
        }
    }
    adjLists[startInt].push_back(endInt);
    adjLists[endInt].push_back(startInt);
    stringstream ss;
    ss << edgeWeight;
    string buffer = ss.str();
    storage.push_back(start + end);
    storage.push_back(buffer);
}

// BFS
string Graph::BreadthFirstTraversal(string start) 
{
    string ans;
    int target;
    for(int i = 0;i < 26;i++)
    {
        if(alphabet[i] == start)
        {
            target = i;
        }
    }
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        visited[i] = false;
    }
    list<int> next;

    visited[target] = true;
    next.push_back(target);
    list<int>::iterator i;

    while (!next.empty()) 
    {
        int currVertex = next.front();
        finalVisit.push_back(currVertex);
        bfsString += alphabet[currVertex] + " ";
        next.pop_front();

        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) 
        {
            int adjVertex = *i;
            if (!visited[adjVertex]) 
            {
                visited[adjVertex] = true;
                next.push_back(adjVertex);
            }
        }
    }
    return bfsString;
}


// DFS
string Graph::DepthFirstTraversal(string start)
{
    string ans = "";
    int target;
    for(int i = 0;i < 26;i++)
    {
        if(alphabet[i] == start)
        {
            target = i;
        }
    }
    DepthFirstTraversalHelper(target);
    return dfsString;
}

void Graph::DepthFirstTraversalHelper(int target)
{
    visited[target] = true;
    list<int> adjList = adjLists[target];
    finalVisit.push_back(target);
    dfsString += alphabet[target] + " ";

    list<int>::iterator i;
    for (i = adjList.begin(); i != adjList.end(); ++i)
    {
        if (!visited[*i])
        {
            DepthFirstTraversalHelper(*i);
        }
    }   
}

//DJIKSTRA 
void Graph::dijkstra(int graph[5][5])
{
    for (int i = 0; i < graphMAX; i++)
    {
        shortestPath[i] = MAX, found[i] = false;
    }
    // the distance of vertex to itself is always going to be 0
    shortestPath[0] = 0;
 
    // Iterate over and find the shortest path for all vertices
    for (int i = 0; i < graphMAX - 1; i++) 
    {
        int currentShortest = findVertex(shortestPath, found);
        // Marks the current as processed
        found[currentShortest] = true;
 
        for (int i = 0; i < graphMAX; i++)
        {
            //update the path if not in found
            if (!found[i] && graph[currentShortest][i] && shortestPath[currentShortest] != INT_MAX && shortestPath[currentShortest] + graph[currentShortest][i] < shortestPath[i])
            {
                shortestPath[i] = shortestPath[currentShortest] + graph[currentShortest][i];
            }
        }
    }
}

// FINDS THE VERTEX WITH THE LOWEST VALUES
int Graph::findVertex(int shortestPath[], bool found[])
{
    int curr = MAX, MIN;
 
    for (int i = 0; i < graphMAX; i++)
    {
        //if not registered as found and its less than or equal to the current distance
        if (found[i] == false && shortestPath[i] <= curr)
        {
            curr = shortestPath[i], MIN = i;
        }
    }
    return MIN;
}

//prints out the distances
void Graph::getDijkstraPath()
{
    cout << "Dijkstra path values : " << endl;
    for (int i = 0; i < graphMAX; i++)
    {
        cout << "[" << i << " , " << shortestPath[i] << "]" << endl;
    }
}

//Grabs the edge weight of a given combo
int Graph::getEdgeWeight(string start, string end)
{
    string goal = start + end;
    for(int i = 0;i < storage.size();i++)
    {
        if(storage[i] == goal)
        {
            return stoi (storage[i+1]);
        }
    }
    return -1;
}

//prints out all the visited values
string Graph::getVisited()
{
    string visited = "";
    for(int i = 0;i < finalVisit.size();i++)
    {
        visited += finalVisit[i];
    }
    return visited;
}

//clears all the visited vertices
void Graph::unvisitVertices()
{
    finalVisit.clear();
}
//grabs the number of edges
int Graph::getNumEdges() const
{
    return numEdges;
}
//grabs the number of vertices
int Graph::getNumVertices() const
{
    return storage.size() / 2;
}
//reads in the data from a provided file
void Graph::readFile(string filename) 
{
    int entryCount = 0;
    //uncomment whichever method works best
    ifstream file(filename);
    //ifstream file("C:\\Users\\caele\\OneDrive\\Documents\\CODECODECODE\\JAN2023\\C++\\CSS 343\\Assignment 3\\graph1.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if(entryCount == 0)
            {
                //initial line, shouldn't be added, this is the amount of edges
                stringstream edges;
                edges << line;
                edges >> numEdges;
            }
            else
            {
                //iterates through the entire line 
                istringstream ss(line);
                string del;
                string first = "";
                string second = ""; 
                string third = "";
                int i = 1;
                int edge = 0;
                while(getline(ss, del, ' ')) 
                { 
                    if(del != "")
                    {
                        if(i == 1)
                        {
                            first = del;
                        }
                        if(i == 2)
                        {
                            second = del;
                        }
                        if(i == 3)
                        {
                            third = del;
                        }
                        i++;
                    }
                }
                edge = stoi(third);
                add(first, second, edge);
            }
            entryCount++;
        }
    file.close();
    }
}
