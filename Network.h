#ifndef FORD_FULKERSON_MAX_FLOW_NETWORK_H
#define FORD_FULKERSON_MAX_FLOW_NETWORK_H

#include <iostream>
#include <vector>

template <typename T>
class Network
{
    int source = 0;
    int target = 0;
    int vertices = 0;
    std::vector<std::vector<T>> adjMatrix;

public:
    Network()= default;;
    explicit Network(int _vertices);

    int Vertices() const { return vertices; }

    int Source() const {return source;}

    int Target() const { return target; }

    std::vector<T>& operator[](int number) {return adjMatrix[number];}

    static Network<T> generateNetwork(int vertices, int maxCapacity = 20);

    void generateDigraphForNetwork();

    std::vector<int> depthFirstSearch();

    T FordFulkersonMaxFlow();

    void printForTest();
};

#endif //FORD_FULKERSON_MAX_FLOW_NETWORK_H
