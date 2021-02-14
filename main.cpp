#include <iostream>
#include <chrono>
#include "Network.h"
#include "Network.cpp"
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>

bool sort_function (std::vector<double> first, std::vector<double> second)
{
    return (first[0]<second[0]);
}

int main()
{
//    srand(time(NULL));

    Network<int> network;

    int k = 0;
    std::vector<std::vector<double>> results;
    results.resize(k+1);
    for (int i = 20; i <= 200; i += 20)
    {
        for (int j = 20; j <= 2000; j += 200)
        {
            network = Network<int>::generateNetwork(i, j);

            int edges = network.Edges();
            int maxFlow = 0;
            auto start = std::chrono::high_resolution_clock::now();
            for (int l = 0; l < 10; ++l)
            {
                maxFlow = network.FordFulkersonMaxFlow();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;

            results.resize(k+1);
            results[k].push_back(maxFlow * edges);
            results[k].push_back(maxFlow);
            results[k].push_back(edges);
            results[k].push_back(i);
            results[k].push_back(j);
            results[k].push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 10);

            std::cout << "X " << k << " " << results[k][0] << " " << results[k][5] << std::endl;

            ++k;
        }
    }

    std::sort(results.begin(), results.end(),sort_function);

    std::ofstream graphTable("graphTable.csv");
    std::ofstream table("table.csv");

    graphTable << std::fixed;
    table << std::fixed;

    for (int i = 0; i < results.size(); ++i)
    {
        graphTable << results[i][0] << " " << results[i][5] << std::endl;
        for (int j = 0; j < results[0].size(); ++j)
        {
            std::cout << results[i][j] << " ";
            table << results[i][j] << " ";
        }
        std::cout << std::endl;
        table << std::endl;
    }
    graphTable.close();
    table.close();

    int vertices = 10;
    int capacity = 20;

//    network = Network<int>::generateNetwork(vertices, capacity);
//    std::cout << network << std::endl;
//    network.printForTest();

//    std::cout << "Max flow = " << network.FordFulkersonMaxFlow();

    return 0;
}