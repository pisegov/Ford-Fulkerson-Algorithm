#include "Network.h"

#define INF 1e9

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
Network<T> Network<T>::generateNetwork(int vertices, int maxCapacity)
{
    Network<T> network(vertices);
    network.generateDigraphForNetwork();
    network.countEdges();

    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> uid(1, maxCapacity);

    //Filling the network with capacities
    for (int i = 0; i < network.target; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            if (network[i][j])
            {
                network[i][j] = uid(gen);
            }
        }
    }

    return network;
}

template <typename T>
void Network<T>::generateDigraphForNetwork()
{
    int arcsCounter = 0;
    int iterationsCounter = 0;
    int const minimalArcs = 1;

    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> uid(0, 1);

    // Generation at least one arc from the source
    while (arcsCounter < minimalArcs && iterationsCounter < 1000)
    {
        arcsCounter = 0;
        iterationsCounter = 0;
        for (int i = 1; i < vertices; ++i)
        {
            adjMatrix[0][i] = uid(gen);
            if (adjMatrix[0][i])
            {
                ++arcsCounter;
            }
        }
        ++iterationsCounter;
    }

    // Generation of the rest of the network
    for(int i = source + 1; i < target; i++)
    {
        for (int j = source + 1; j < vertices; j++)
        {
            if((adjMatrix[i][j] == adjMatrix[j][i]) && (i != j))
            {
                adjMatrix[i][j] = uid(gen);
            }
        }
    }

    //Checking if there are arcs to the target
    bool noArcsToTarget = true;
    for (int i = source; i < target; ++i)
    {
        if (adjMatrix[i][target])
        {
            noArcsToTarget = false;
        }
    }

    //If there are no arcs to the target, generation
    iterationsCounter = 0;
    while ( noArcsToTarget && iterationsCounter < 1000)
    {
        for (int i = source; i < target; i++)
        {
            adjMatrix[i][target] = uid(gen);
            if (adjMatrix[i][target])
            {
                noArcsToTarget = false;
            }
        }
        ++iterationsCounter;
    }
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
    Network<T> network = *this;
    std::vector<int> path = network.depthFirstSearch();

    T maxFlow = 0;
    while (!path.empty())
    {
        T minCapacity = INF;
        for (int i = 0; i < path.size() - 1; ++i)
        {
            if(network[path[i]][path[i + 1]] < minCapacity)
            {
                minCapacity = network[path[i]][path[i + 1]];
            }
        }

        for (int i = 0; i < path.size() - 1; ++i)
        {
            network[path[i]][path[i + 1]] -= minCapacity;
            network[path[i + 1]][path[i]] += minCapacity;
        }

        maxFlow += minCapacity;

        path = network.depthFirstSearch();
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
void Network<T>::countEdges()
{
    int edgesCounter = 0;

    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            if(adjMatrix[i][j])
            {
                edgesCounter++;
            }
        }
    }

    edges = edgesCounter;
}

template<typename T>
void Network<T>::printForTest() {

    std::cout << vertices << " " << edges << std::endl;
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            if(adjMatrix[i][j])  std::cout << i << " " << j << " " << adjMatrix[i][j] << std::endl;
        }
    }
}

template<typename T>
void Network<T>::doubleCapacities() {
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            adjMatrix[i][j] *= 2;
        }
    }
}
