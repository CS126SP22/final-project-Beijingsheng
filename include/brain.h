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
          std::vector<Passenger> passengers, std::vector<int> d,
          int kWindowSize);
    void Display();
    void AdvanceOneFrame();
    void HandleBrush(const vec2& vec);


private:
    void DisplayConnections();
    void DisplayStations();
    void DisplayMetros();
    void DisplayTourists();
    void DisplayInformation();
    void DisplaySpeedControl();
    void DisplayScrollBars();
    void InitMetro();
    void InitPassengers();
    Dijkstra InitDijkstra();

    void UpdateArriving(int i);
    void UpdateDriving(int i);

    void OnBoard(int metro, int station);
    void OffBoard(int metro, int station);
    std::vector<int> destination;
    std::vector<std::vector<int>> passenger_locations;
    std::vector<std::vector<int>> platform;
    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    int station_radius_;
    int steps_needed;
    int kWindowSize;
    float top_;
    float y_scroll_;
    float x_scroll_;
    float left_;
    bool onPause;
    float speed;
    std::string message;
    std::vector<Metro> metros;
    std::vector<Passenger> passengers;
    Dijkstra dijkstra;
    std::vector<std::vector<int>> heights;
    std::vector<int> init_heights;
    std::vector<int> visitor_counts;
    std::vector<int> carry_counts;
};

}
