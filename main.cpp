/*
Name: Basma Elhoseny
Sec:1
BN:16
Code:9202381
*/

#define el "\n";

#include <iostream>
#include <vector>
#include <algorithm> // for std::sort
#include <queue>

using namespace std;

bool isElementInVector(const std::vector<int> &vec, const int x)
{
    // Iterate through the vector
    for (int num : vec)
    {
        // Check if the current element equals x
        if (num == x)
        {
            return true; // x found in the vector
        }
    }
    return false; // x not found in the vector
}

void printForwardPath(vector<std::vector<int>> &forwardPaths)
{
    // Ignore node 0 while printing
    for (int i = 1; i < forwardPaths.size(); i++)
    {
        int j;
        for (j = 0; j < forwardPaths[i].size(); j++)
        {
            cout << forwardPaths[i][j] << " ";
        }
        // has no forward messages :D
        if (j == 0)
            cout << "-1";
        cout << el;
    }
}
void print_queue(queue<std::pair<int, std::vector<int>>> q)
{
    while (!q.empty())
    {
        cout << q.front().first << " ";
        q.pop();
    }
    cout << '\n';
}

void DRS(const int &src, const int &dst, const vector<vector<int>> &adjList, vector<vector<int>> &forwardPath)
{
    // init Frontier [Queue BFS :D]
    std::queue<std::pair<int, std::vector<int>>> frontier;

    // Add src to the frontier Empty Vector
    frontier.push(make_pair(src, vector<int>()));

    // Keep looping over the Frontier
    while (!frontier.empty())
    {
        // printForwardPath(forwardPath);
        // print_queue(frontier);
        // cout << "....................\n";
        // Pick Node to Send
        int node = frontier.front().first;
        vector<int> path = frontier.front().second;

        frontier.pop();

        // if node is dst -->  don't send
        if (node == dst)
            continue;

        // if node in this message --> don't send
        if (isElementInVector(path, node))
            continue;

        if (forwardPath[node].size() != 0)
        {
            // then this node has sent sth before

            // check if the new path is longer than the one before (so this path is longer don't take)
            if (path.size() + 1 > forwardPath[node].size())
                continue; // old path is shorter :D

            // then they are of the same len --> check lexicographically
            if (forwardPath[node].size() - 2 < 0 || forwardPath[node][forwardPath[node].size() - 2] < path[path.size() - 1])
                continue; // old path is lexicographically smaller :D
            {
                // cout<<"node"<<node<<" ";
                // cout << "Herrr\n";
                continue;
            }

            // cout<<"node"<<node<<" ";
            // // Print the old path
            // cout<<"Old Path\n";
            // for (int i = 0; i < forwardPath[node].size(); i++)
            // {
            //     cout << forwardPath[node][i] << " ";
            // }
            // cout<<"New Path\n";
            // // print new path
            // for (int i = 0; i < path.size(); i++)
            // {
            //     cout << path[i] << " ";
            // }
            // cout << "******\n";
        }

        // Add this path :D
        forwardPath[node] = path;
        // Add node
        forwardPath[node].push_back(node);

        // cout<<"Path:\n";
        // for (int i=0;i<path.size();i++){
        //     cout<<path[i]<<" ";
        // }

        // cout<<"\nNew Path\n";
        // for (int i=0;i<forwardPath[node].size();i++){
        //     cout<<forwardPath[node][i]<<" ";
        // }

        // Add neighbors to the frontier
        for (int i = 0; i < adjList[node].size(); i++)
        {
            frontier.push(make_pair(adjList[node][i], forwardPath[node]));
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // Read input
    // Read no of nodes and edges
    int no_nodes, no_edges;
    cin >> no_nodes >> no_edges;

    // Read Graph
    vector<vector<int>> adjList(no_nodes + 1);
    int x, y;
    for (int i = 0; i < no_edges; i++)
    {
        cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
        // sort the adjList descending
        // std::sort(adjList[x].begin(), adjList[x].end());
        // std::sort(adjList[y].begin(), adjList[y].end());
    }
    // Sort the adjList
    for (int i = 1; i < adjList.size(); i++)
    {
        std::sort(adjList[i].begin(), adjList[i].end());
    }

    // // Print Graph
    // for (int i = 1; i < adjList.size(); i++)
    // {
    //     cout << i << " : ";
    //     for (int j = 0; j < adjList[i].size(); j++)
    //     {
    //         cout << adjList[i][j] << " ";
    //     }
    //     cout << el;
    // }

    // return 0;

    // Read Src & Dst
    int src, dst;
    cin >> src >> dst;

    // Running DRS Algo
    vector<std::vector<int>> forwardPaths(no_nodes + 1, std::vector<int>());

    DRS(src, dst, adjList, forwardPaths);

    // // Print Forward Path
    // printForwardPath(forwardPaths);
    // Ignore node 0 while printing
    for (int i = 1; i < forwardPaths.size(); i++)
    {
        int j;
        for (j = 0; j < forwardPaths[i].size(); j++)
        {
            cout << forwardPaths[i][j] << " ";
        }
        // has no forward messages :D
        if (j == 0)
            cout << "-1";
        cout << el;
    }
}