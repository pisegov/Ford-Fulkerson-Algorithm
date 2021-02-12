#include <iostream>
#include "Network.h"
#include <list>
#include "Network.cpp"
int main()
{
    srand(time(NULL));

    int vertices = 10;
    Network<int> network = Network<int>::generateNetwork(vertices);

//    std::cout << network << std::endl;
//    network.printForTest();

    std::cout << "Max flow = " << network.FordFulkersonMaxFlow();

    return 0;
}