//
// Created by clark on 22-4-18.
//
#include "dijkstra.h"
namespace minimetro {
    Dijkstra::Dijkstra() {}

    int Dijkstra::minDist(std::vector<int> dist, std::vector<bool> sptSet) {
        int min = INT_MAX, min_index;
        for (int i = 0; i < V; i++) {
            if (sptSet[i] == false && dist[i] <= min) {
                min = dist[i];
                min_index = i;
            }
        }
        return min_index;
    }

    std::vector<int> Dijkstra::GetPath(int s, int t) {
        std::vector<int> dist;
        std::vector<bool> sptSet;
        std::vector<int> parent;
        for (int i = 0; i < V; i++) {
            dist.push_back(INT_MAX);
            sptSet.push_back(false);
            parent.push_back(-1);
        }
        dist[s] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDist(dist, sptSet);
            sptSet[u] = true;
            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                    parent[v] = u;
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
//        GetSolution(s, t, dist, parent);
        return dist;
    }

    Dijkstra::Dijkstra(std::vector<std::vector<int>> graph) {
        this->graph = graph;
        this->V = graph.size();
    }
}