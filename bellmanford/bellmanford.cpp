#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

struct Edge
{
    int source, destination, weight;
};

bool bellmanFord(vector<Edge> &edges, int numVertices, int numEdges, int source, vector<int> &distances, bool directedgraph)
{

    distances[source] = 0;

    for (int i = 0; i < numVertices - 1; ++i)
    {
        for (int j = 0; j < numEdges; ++j)
        {
            int u = edges[j].source;
            int v = edges[j].destination;
            int weight = edges[j].weight;

            if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v])
            {

                distances[v] = distances[u] + weight;
            }

            // For undirected graphs only
            if (distances[v] != std::numeric_limits<int>::max() &&
                distances[v] + weight < distances[u] && !directedgraph)
            {
                distances[u] = distances[v] + weight;
            }
        }
    }

    for (const auto &edge : edges)
    {
        int u = edge.source;
        int v = edge.destination;
        int weight = edge.weight;

        if (distances[u] != numeric_limits<int>::max() &&
            distances[u] + weight < distances[v])
        {
            return false;
        }
    }
    return true;
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
    bool directedgraph = false;

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
                cerr << "Erro: Faltando o argumento para '-o'" << endl;
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
                cerr << "Erro: Faltando o argumento para '-f'" << endl;
                return 1;
            }
        }
        else if (arg == "-i")
        {
            initialVertex = stoi(argv[i + 1]);
        }
        else if (arg == "-d")
        {
            directedgraph = true;
        }
    }

    int numNodes, numEdges, u, v, weight;

    ifstream input_file(input_filename);

    input_file >> numNodes >> numEdges;

    vector<Edge> edges(numEdges);

    for (int i = 0; i < numEdges; ++i)
    {
        input_file >> u >> v >> weight;
        edges[i].source = u - 1;
        edges[i].destination = v - 1;
        edges[i].weight = weight;
    }

    input_file.close();

    vector<int> distances(numNodes, numeric_limits<int>::max());

    bool SemCicloNeg = bellmanFord(edges, numNodes, numEdges, initialVertex - 1, distances, directedgraph);
    string result;

    if (!output_filename.empty())
    {
        ofstream output_file(output_filename);
        if (output_file.is_open())
        {
            streambuf *originalCoutBuffer = std::cout.rdbuf();
            cout.rdbuf(output_file.rdbuf());

            if (SemCicloNeg)
            {
                for (int i = 0; i < numNodes; i++)
                {
                    if (distances[i] == numeric_limits<int>::max())
                        result = "Unreachable";
                    else
                        result = to_string(distances[i]);
                    cout << i + 1 << ":" << result;
                    if (i < numNodes - 1)
                        cout << " ";
                    else
                        cout << endl;
                }
            }
            else
            {
                cout << "Graph contains a negativa cycles" << endl;
            }

            std::cout.rdbuf(originalCoutBuffer);
            output_file.close();
        }
    }
    else
    {
        if (SemCicloNeg)
        {
            for (int i = 0; i < numNodes; i++)
            {
                if (distances[i] == numeric_limits<int>::max())
                    result = "Unreachable";
                else
                    result = to_string(distances[i]);
                cout << i + 1 << ":" << result;
                if (i < numNodes - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }
        else
        {
            cout << "Graph contains a negative cycle" << endl;
        }
    }

    return 0;
}