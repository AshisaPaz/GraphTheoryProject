#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * @brief Prim's algorithm for finding the minimum spanning tree of a graph
 * 
 * @param graph The graph to find the minimum spanning tree
 * @param source The source node
 * @param prev The array of previous nodes
 * @param cost The array of costs
 * @param node_amount The number of nodes in the graph
 * @param mstEdges The vector of edges in the minimum spanning tree
 * @return void
*/

void Prim(vector<vector<int>> &graph, int source, vector<int> &prev, vector<int> &cost, int node_amount, vector<pair<int, int>> &mstEdges)
{
    cost[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push(make_pair(0, source));
    vector<bool> visited(node_amount, false);

    // While the heap is not empty

    while (!minHeap.empty())
    {
        // Get the node with the minimum cost

        int currentNode = minHeap.top().second;
        minHeap.pop();

        // If the node has already been visited, continue

        visited[currentNode] = true;

        // For each neighbor of the current node

        for (int i = 0; i < node_amount; i++)
        {

            // If the neighbor is not visited and the weight of the edge
            // is less than the cost of the neighbor

            if (graph[currentNode][i] != -1)
            {

                // Get the neighbor and the weight of the edge

                int neighbor = i;
                int weight = graph[currentNode][i];

                // Update the cost of the neighbor and add it to the heap

                if (!visited[neighbor] && weight < cost[neighbor])
                {

                    // Update the cost and previous node

                    cost[neighbor] = weight;
                    prev[neighbor] = currentNode;

                    minHeap.push(make_pair(cost[neighbor], neighbor));

                    // Add the edge to the vector of edges

                    mstEdges.push_back(make_pair(currentNode, neighbor));
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
    bool solution = false;

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
        else if (arg == "-s")
        {
            solution = true;
        }
    }

    int node_amount, edge_amount, u, v, cost;

    ifstream input_file(input_filename);

    if (!input_file.is_open())
    {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    // Read the number of nodes and edges.

    input_file >> node_amount >> edge_amount;

    vector<vector<int>> graph(node_amount, vector<int>(node_amount, -1));

    for (int i = 0; i < edge_amount; ++i)
    {
        input_file >> u >> v >> cost;
        graph[u - 1][v - 1] = cost;
        graph[v - 1][u - 1] = cost;
    }
    input_file.close();

    vector<int> prev(node_amount, -1);
    vector<int> cost_array(node_amount, INT_MAX);

    vector<pair<int, int>> mstEdges;

    Prim(graph, initialVertex - 1, prev, cost_array, node_amount, mstEdges);

    int finalcost = 0;

    for (int i = 0; i < node_amount; i++)
    {
        finalcost += cost_array[i];
    }

    sort(mstEdges.begin(), mstEdges.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.first < b.first; });

    if (!output_filename.empty())
    {
        ofstream output_file(output_filename);

        if (output_file.is_open())
        {
            streambuf *originalCoutBuffer = std::cout.rdbuf(); // Store the original cout buffer
            cout.rdbuf(output_file.rdbuf());

            if (solution)
            {
                for (int i = 0; i < node_amount; i++)
                {
                    if (prev[i] == -1)
                        continue;
                    cout << "(" << prev[i] + 1 << "," << i + 1 << ")";

                    if (i != node_amount - 1)
                        cout << " ";
                    else
                        cout << endl;
                }
            }
            else
                cout << finalcost << endl;

            std::cout.rdbuf(originalCoutBuffer); // Restore the original cout buffer
            output_file.close();
        }
    }
    else
    {
        if (solution)
        {
            for (int i = 0; i < node_amount; i++)
            {
                if (prev[i] == -1)
                    continue;
                cout << "(" << prev[i] + 1 << "," << i + 1 << ")";

                if (i != node_amount - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }
        else
            cout << finalcost << endl;
    }

    return 0;
}