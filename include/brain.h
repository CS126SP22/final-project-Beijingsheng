//
// Created by clark on 2022/4/12.
//
#pragma once

#include "cinder/gl/gl.h"
#include "metro.h"
#include "item.h"
#include "dijkstra.h"

using glm::vec2;

namespace minimetro {
class Brain {
public:
    Brain();
    Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
          std::vector<Metro> metros, int station_radius,
          std::vector<Item> items, std::vector<int> d,
          int kWindowSize);
    void Display();
    void AdvanceOneFrame();
    void HandleBrush(const vec2& vec);
private:
    void DisplayConnections();
    void DisplayStations();
    void DisplayMetros();
    void DisplayItems();
    void DisplayItemsOnTravel();
    void DrawStationShadow(int i);
    void DisplayInformation();
    void DisplaySpeedControl();
    void DisplayScrollBars();
    void InitValues();
    void InitMetro();
    void InitPassengers();
    Dijkstra InitDijkstra();
    void UpdateArriving(int i);
    void UpdateDriving(int i);
    void OnBoard(int metro, int station);
    void OnBoardFirstTime(int metro, int p, int station, int idx);
    void OnBoardToNext(int metro, int p, int station, int idx);
    void OffBoard(int metro, int station);
    int kWindowSize;
    std::vector<int> destinations_;
    std::vector<std::vector<int>> item_locations_;
    std::vector<std::vector<int>> platforms_;
    std::vector<std::vector<float>> station_locations_;
    std::vector<std::vector<int>> station_connections_;
    int station_radius_;
    int total_steps_needed_ = 0;
    float top_ = 100;
    float left_ = 100;
    float y_scroll_ = 100;
    float x_scroll_ = 100;
    bool on_pause_ = true;
    float speed_ = 1.2;
    std::string message_ = "_______________";
    std::vector<Metro> metros_;
    std::vector<Item> items_;
    Dijkstra dijkstra_;
    std::vector<std::vector<int>> cur_heights_;
    std::vector<int> init_heights_;
    std::vector<int> visitor_counts_;
    std::vector<int> carry_counts_;

    void HandleVerticalScrollBar(const vec2 &vec);
    void HandleHorizontalScrollBar(const vec2 &vec);
    void HandleSpeedControl(const vec2 &vec);
    bool HandleClickItem(const vec2 &vec);
    bool HandleClickStation(const vec2 &vec);
    bool HandleClickMetro(const vec2 &vec);
};

}
