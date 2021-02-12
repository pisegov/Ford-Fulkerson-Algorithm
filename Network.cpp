#include "Network.h"

template<typename T>
Network<T>::Network(int _vertices): vertices(_vertices), target(_vertices - 1)
{
    T initAll = 0;
    adjMatrix.resize(vertices);
    for (int i = 0; i < vertices; ++i)
    {
        adjMatrix[i].resize(vertices, initAll);
    }
}

template <typename T>
Network<T> Network<T>::generateNetwork(int vertices)
{
    // Init an adjacency matrix
    Network<T> network(vertices);

    // Generate arcs coming from the source
    const int minimalSourceArcs = 2;
    int arcsCounter = 0;
    int iterationsCounter = 0;
    while (arcsCounter < minimalSourceArcs && iterationsCounter < 1000)
    {
        arcsCounter = 0;
        iterationsCounter = 0;
        for (int i = 1; i < vertices; ++i)
        {
            network[0][i] = rand() % 2;
            if (network[0][i])
            {
                ++arcsCounter;
            }
        }
        ++iterationsCounter;
    }

    // Generate the rest of the network
    for(int i = network.source + 1; i < network.target; i++)
    {
        arcsCounter = 0;
        iterationsCounter = 0;
        while (arcsCounter < 1 && iterationsCounter < 1000)
        {
            for (int j = network.source + 1; j < vertices; j++)
            {
                if((network[i][j] == network[j][i]) && (i != j))
                {
                    network[i][j] = rand() % 2;
                    if (network[i][j])
                    {
                        ++arcsCounter;
                    }
                }
            }
            ++iterationsCounter;
        }
    }

    for (int i = 0; i < network.target; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            if (network[i][j])
            {
                network[i][j] = rand() % 20 + 1;
            }
        }
    }

    return network;
}

template<typename T>
std::vector<int> Network<T>::depthFirstSearch() {
    int cur = source;
    std::vector<int> path;

    bool visited[vertices];

    while (cur != target)
    {
        bool notFound = true;
        visited[cur] = true;
        for (int i = 0; i < vertices; ++i)
        {
            if (adjMatrix[cur][i] > 0 && !visited[i])
            {
                path.push_back(cur);
                cur = i;
                notFound = false;
                break;
            }
        }
        if (notFound)
        {
            if (cur == source)
            {
                path.resize(0);
                return path;
            }
            cur = path.back();
            path.pop_back();
        }
    }

    path.push_back(target);

    return path;
}

template<typename T>
T Network<T>::FordFulkersonMaxFlow()
{
    std::vector<int> path = depthFirstSearch();

    T maxFlow = 0;
    while (!path.empty())
    {
        T minCapacity = 1000;
        for (int i = 0; i < path.size() - 1; ++i)
        {
            if(adjMatrix[path[i]][path[i + 1]] < minCapacity)
            {
                minCapacity = adjMatrix[path[i]][path[i + 1]];
            }
        }

        for (int i = 0; i < path.size() - 1; ++i)
        {
            adjMatrix[path[i]][path[i + 1]] -= minCapacity;
            adjMatrix[path[i + 1]][path[i]] += minCapacity;
        }

        maxFlow += minCapacity;

        path = depthFirstSearch();
    }

    return maxFlow;
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, Network<T> network)
{
    int vertices = network.Vertices();
    int target = vertices - 1;
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < target; ++j)
        {
            stream << network[i][j] << ' ';
        }
        stream << network[i][target] << ' ';

        stream << std::endl;
    }
    return stream;
}

template<typename T>
void Network<T>::printForTest() {
    int edges = 0;

    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            if(adjMatrix[i][j])
            {
                edges++;
            }
        }
    }

    std::cout << vertices << " " << edges << std::endl;
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            if(adjMatrix[i][j])  std::cout << i << " " << j << " " << adjMatrix[i][j] << std::endl;
        }
    }
}
