#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

void Dijkstra(vector<vector<int>> &graph, int source, int dist[], int prev[], int numNodes)
{
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    minHeap.push(make_pair(0, source));

    while (!minHeap.empty())
    {
        int currentNode = minHeap.top().second;
        minHeap.pop();

        for (int i = 0; i < numNodes; i++)
        {

            if (graph[currentNode][i] != -1)
            {

                int neighbor = i;
                int weight = graph[currentNode][i];

                if (dist[currentNode] + weight < dist[neighbor])
                {
                    dist[neighbor] = dist[currentNode] + weight;
                    minHeap.push(make_pair(dist[neighbor], neighbor));
                    prev[neighbor] = currentNode + 1;
                }
            }
        }
    }
}

void printHelp()
{
    cout << "Help:" << endl;
    cout << "-h: shows help dialog" << endl;
    cout << "-o <file>: redirects output to 'file'" << endl;
    cout << "-f <file>: indicates the 'file' containing the input graph" << endl;
    cout << "-s: shows the solution" << endl;
    cout << "-i: initial vertex" << endl;
}

int main(int argc, char *argv[])
{
    string output_filename;
    string input_filename;
    int initialVertex = 1;

    // Process command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "-h")
        {
            printHelp();
            return 0;
        }
        else if (arg == "-o")
        {
            if (i + 1 < argc)
            {
                output_filename = argv[i + 1];
                ++i;
            }
            else
            {
                cerr << "Missing '-o' argument." << endl;
                return 1;
            }
        }
        else if (arg == "-f")
        {
            if (i + 1 < argc)
            {
                input_filename = argv[i + 1];
                ++i;
            }
            else
            {
                cerr << "Missing'-f' argument" << endl;
                return 1;
            }
        }
        else if (arg == "-i")
        {
            initialVertex = stoi(argv[i + 1]);
        }
    }

    int numNodes, numEdges, u, v, weight;

    ifstream input_file(input_filename);

    input_file >> numNodes >> numEdges;

    vector<vector<int>> graph(numNodes, vector<int>(numNodes, -1));

    for (int i = 0; i < numEdges; ++i)
    {
        input_file >> u >> v >> weight;
        graph[u - 1][v - 1] = weight;
        graph[v - 1][u - 1] = weight;
    }
    input_file.close();

    int prev[numNodes];
    int dist[numNodes];

    for (int i = 0; i < numNodes; i++)
    {
        prev[i] = -1;
        dist[i] = numeric_limits<int>::max();
    }

    Dijkstra(graph, initialVertex - 1, dist, prev, numNodes);

    string result;

    if (!output_filename.empty())
    {
        ofstream output_file(output_filename);
        if (output_file.is_open())
        {
            streambuf *originalCoutBuffer = std::cout.rdbuf(); // Store the original cout buffer
            cout.rdbuf(output_file.rdbuf());

            for (int i = 0; i < numNodes; i++)
            {
                if (dist[i] == numeric_limits<int>::max())
                    result = "-1";
                else
                    result = to_string(dist[i]);
                cout << i + 1 << ":" << result;
                if (i < numNodes - 1)
                    cout << " ";
                else
                    cout << endl;
            }

            std::cout.rdbuf(originalCoutBuffer); // Restore the original cout buffer
            output_file.close();
        }
    }
    else
    {

        for (int i = 0; i < numNodes; i++)
        {
            if (dist[i] == numeric_limits<int>::max())
                result = "-1";
            else
                result = to_string(dist[i]);
            cout << i + 1 << ":" << result;
            if (i < numNodes - 1)
                cout << " ";
            else
                cout << endl;
        }
    }

    return 0;
}