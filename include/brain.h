//
// Created by clark on 2022/4/12.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace minimetro {
class Brain {
public:
    Brain();
    Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
          std::vector<std::vector<int>> routes, int station_radius,
          std::vector<std::vector<int>> destinations, std::vector<ci::Color> colors);
    void Display();
    void AdvanceOneFrame();

private:
    void DisplayConnections();
    void DisplayStations();
    void DisplayMetros();
    void DisplayTourists();

    void InitColors(std::vector<ci::Color> colors);
    void InitPlatform(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> routes);
    void InitDirections(std::vector<std::vector<int>> routes);
    void InitMetroLocs(std::vector<std::vector<int>> routes);
    void InitPassengers(std::vector<std::vector<int>> routes);
    void InitNextStops(std::vector<std::vector<int>> routes);

    void UpdateArriving(int i);
    void UpdateDriving(int i);
    void UpdateDirection(int i);
    void UpdateNextStop(int i);

    int HasPassengerToBoard(int i);
    int HasPassengerToLeave(int i);

    int GetMetroNextStop(int i);

    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    std::vector<std::vector<float>> metro_locs;
    std::vector<int> next_stop;
    int station_radius_;
    std::vector<int> directions;
    std::vector<std::vector<int>> destinations;
    std::vector<int> tourists_locs;
    std::vector<bool> on_metro;
    std::vector<ci::Color> colors;
    std::vector<int> passengers;
    std::vector<std::vector<int>> platform;
    std::vector<std::vector<int>> routes;
};
}
