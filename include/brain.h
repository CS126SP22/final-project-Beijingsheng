//
// Created by clark on 2022/4/12.
//
#pragma once

#include "cinder/gl/gl.h"
#include "metro.h"
#include "passenger.h"
#include "dijkstra.h"

using glm::vec2;

namespace minimetro {
class Brain {
public:
    Brain();
    Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
          std::vector<Metro> metros, int station_radius,
          std::vector<Passenger> passengers, std::vector<int> d);
    void Display();
    void AdvanceOneFrame();

private:
    void DisplayConnections();
    void DisplayStations();
    void DisplayMetros();
    void DisplayTourists();
    void InitMetro();
    void InitPassengers();
    Dijkstra InitDijkstra();

    void UpdateArriving(int i);
    void UpdateDriving(int i);

    void OnBoard(int metro, int station);
    void OffBoard(int metro, int station);

    std::vector<int> destination;

    std::vector<std::vector<int>> platform;
    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    int station_radius_;
    std::vector<Metro> metros;
    std::vector<Passenger> passengers;
    Dijkstra dijkstra;
    std::vector<std::vector<int>> heights;
};

}
