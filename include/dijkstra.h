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
    std::vector<int> GetPath(int s);
private:
    int num_of_vertices_;
    std::vector<std::vector<int>> graph_;
    int MinDist(std::vector<int> dist, std::vector<bool> sptSet);
};

}