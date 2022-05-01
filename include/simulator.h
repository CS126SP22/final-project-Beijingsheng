//
// Created by clark on 2022/4/12.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "brain.h"

namespace minimetro {

class MiniMetroApp : public ci::app::App {
public:
    MiniMetroApp();
    void draw() override;
    void update() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
private:
    const int kWindowSize = 875;
    const std::string kFileStationsLocation = "/home/clark/Cinder/my-projects/final-project-Beijingsheng/resources/stations.json";
    const std::string kFileMetrosLocation = "/home/clark/Cinder/my-projects/final-project-Beijingsheng/resources/metros.json";
    const std::string kFileItemsLocation = "/home/clark/Cinder/my-projects/final-project-Beijingsheng/resources/items.json";

    void readDataItems();
    void readDataMetros();
    void readDataStations();
    void drawSpeedControlPanel();

    std::vector<std::vector<float>> station_locations_;
    std::vector<std::vector<int>> station_connections_;
    std::vector<Metro> metros_;
    std::vector<Passenger> items_;
    std::vector<int> destinations_;
    Brain brain_;
};

}
