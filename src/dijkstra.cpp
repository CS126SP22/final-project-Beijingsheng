//
// Created by clark on 22-4-18.
//
#include "dijkstra.h"
namespace minimetro {
Dijkstra::Dijkstra() {}

/**
 * Helper function for Dijkstra Algorithm
 * @param dist
 * @param sptSet
 * @return
 */
int Dijkstra::MinDist(std::vector<int> dist, std::vector<bool> sptSet) {
    int min = INT_MAX, min_index;
    for (int i = 0; i < num_of_vertices_; i++) {
        if (sptSet[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

/**
 * Get the path
 * @param
 * @return
 */
std::vector<int> Dijkstra::GetPath(int s) {
    std::vector<int> dist;
    std::vector<bool> sptSet;
    std::vector<int> parent;
    for (int i = 0; i < num_of_vertices_; i++) {
        dist.push_back(INT_MAX);
        sptSet.push_back(false);
        parent.push_back(-1);
    }
    dist[s] = 0;
    for (int count = 0; count < num_of_vertices_ - 1; count++) {
        int u = MinDist(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < num_of_vertices_; v++) {
            if (!sptSet[v] && graph_[u][v] && dist[u] + graph_[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph_[u][v];
            }
        }
    }
    return dist;
}

/**
 * Constructor with graph
 * @param graph
 */
Dijkstra::Dijkstra(std::vector<std::vector<int>> graph) {
    this->graph_ = graph;
    this->num_of_vertices_ = graph.size();
}

}