#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

/**
 * @brief Kruskal's algorithm for finding the minimum spanning tree of a graph
 * 
 * @param edges The vector of edges of the graph
 * @param node_amount The number of nodes in the graph
 * @param init_vertex The initial vertex
 * @return vector<Edge> The vector of edges in the minimum spanning tree
*/

// Struct for storing the edges of the graph

struct Edge
{
    int src, dest, weight;
};

// Struct for storing the union-find data structure

struct findUnion
{
    vector<int> parent, rank;


    findUnion(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Find operation

    int Find(int v)
    {
        if (parent[v] != v)
            parent[v] = Find(parent[v]);
        return parent[v];
    }

    // Union by rank

    void Union(int v, int u)
    {
        if (rank[v] > rank[u])
        {
            parent[u] = v;
        }
        else if (rank[v] < rank[u])
        {
            parent[v] = u;
        }
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
};

// Comparator for sorting the edges

bool compareEdges(const Edge &e1, const Edge &e2)
{
    return e1.weight < e2.weight;
}

// Kruskal's algorithm

vector<Edge> Kruskal(vector<Edge> &edges, int node_amount, int init_vertex)
{
    vector<Edge> mst;
    sort(edges.begin(), edges.end(), compareEdges);

    // Create the union-find data structure

    findUnion union1(node_amount);
    union1.Union(init_vertex, init_vertex); // Connect the initial vertex to itself

    for (int i = 0; i < edges.size(); i++)
    {
        int srcParent = union1.Find(edges[i].src);
        int destParent = union1.Find(edges[i].dest);

        // If the parents are different, then the edge is part of the MST

        if (srcParent != destParent)
        {
            mst.push_back(edges[i]);
            union1.Union(srcParent, destParent);
        }
    }

    return mst;
}

void printHelp()
{
    cout << "Help:" << endl;
    cout << "-h: shows help dialog" << endl;
    cout << "-o <file>: redirects output to 'file'" << endl;
    cout << "-f <file>: indicates the 'file' containing the input graph" << endl;
    cout << "-s: shows the solution (ascending order)" << endl;
    cout << "-i: initial vertex" << endl;
}

int main(int argc, char *argv[])
{
    string output_filename;
    string input_filename;
    int init_vertex = 1;
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
                input_f = argv[i + 1];
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
            init_vertex = stoi(argv[i + 1]);
        }
        else if (arg == "-s")
        {
            solution = true;
        }
    }

    int node_amount, edge_amount, u, v, weight;

    ifstream input_file(input_f);

    input_file >> node_amount >> edge_amount;

    vector<Edge> edges(edge_amount);

    for (int i = 0; i < edge_amount; ++i)
    {
        input_file >> u >> v >> weight;
        edges[i] = {u - 1, v - 1, weight};
    }
    input_file.close();

    vector<Edge> mst = Kruskal(edges, node_amount, init_vertex - 1);

    sort(mst.begin(), mst.end(), [](const Edge &edge1, const Edge &edge2)
         { return edge1.src < edge2.src; });

    int finalcost = 0;

    for (const auto &edge : mst)
    {
        finalcost += edge.weight;
    }

    if (!output_filename.empty())
    {
        ofstream output_file(output_filename);
        if (output_file.is_open())
        {
            streambuf *originalCoutBuffer = std::cout.rdbuf();
            cout.rdbuf(output_file.rdbuf());

            if (solution)
            {
                for (size_t i = 0; i < mst.size(); i++)
                {
                    const auto &edge = mst[i];
                    cout << "(" << edge.src + 1 << "," << edge.dest + 1 << ")";

                    if (i != mst.size() - 1)
                        cout << " ";
                    else
                        cout << endl;
                }
            }
            else
                cout << finalcost << endl;

            std::cout.rdbuf(originalCoutBuffer);
            output_file.close();
        }
    }
    else
    {
        if (solution)
        {
            for (size_t i = 0; i < mst.size(); i++)
            {
                const auto &edge = mst[i];
                cout << "(" << edge.src + 1 << "," << edge.dest + 1 << ")";

                if (i != mst.size() - 1)
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