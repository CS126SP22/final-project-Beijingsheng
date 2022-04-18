//
// Created by clark on 22-4-18.
//
#include <bits/stdc++.h>
using namespace std;

namespace minimetro {

    class Dijkstra {
    public:
        Dijkstra();
        Dijkstra(std::vector<std::vector<int>> graph);
        int minDist(std::vector<int> dist, std::vector<bool> sptSet);
        std::vector<int> GetPath(int s, int t);
        std::vector<int> GetSolution(int s, int t, std::vector<int> dist, std::vector<int> parent);

        int V;
        std::vector<std::vector<int>> graph;
    };
}