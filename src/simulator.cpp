//
// Created by clark on 2022/4/12.
//
#include "../include/simulator.h"
// CITE: https://github.com/nlohmann/json/
#include "json.hpp"

namespace minimetro {

MiniMetroApp::MiniMetroApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);

    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    std::vector<Metro> metros;
    std::vector<Passenger> passengers;
    std::vector<int> destination;

    std::ifstream stations_file("/home/clark/Cinder/my-projects/final-project-Beijingsheng/resources/stations.json");

    nlohmann::json stations_json;
    stations_file >> stations_json;
    int num_station = stations_json.begin()->size();
    for (nlohmann::json::iterator it = stations_json.begin()->begin(); it != stations_json.begin()->end(); ++it) {
        std::vector<int> temp{};
        for (int j = 0; j < num_station; j++) temp.push_back(0);
        for (int i = 0; i < it->begin().value().size(); i++) {
            temp[int(it->begin().value()[i]) - 1] = 1;
        }
        connections.push_back(temp);
        nlohmann::json::iterator it_temp = it->begin();
        it_temp ++;
        std::vector<float> temp2;
        temp2.push_back(it_temp.value());
        it_temp ++;
        temp2.push_back(it_temp.value());
        locations.push_back(temp2);
    }

    std::ifstream metros_file("/home/clark/Cinder/my-projects/final-project-Beijingsheng/resources/metros.json");

    nlohmann::json metros_json;
    metros_file >> metros_json;

    for (nlohmann::json::iterator it = metros_json.begin()->begin(); it != metros_json.begin()->end(); ++it) {
        nlohmann::json::iterator temp = it->begin();
        temp ++;
        std::vector<int> temp_route{};
        for (int i = 0; i < temp.value().size(); i++) {
            temp_route.push_back(temp.value()[i]);
        }
        std::string c = it->begin().value();
        char* co = const_cast<char*>(c.c_str());
        metros.push_back(Metro(temp_route, ci::Color(co)));
    }

    std::ifstream items_file("/home/clark/Cinder/my-projects/final-project-Beijingsheng/resources/items.json");

    nlohmann::json items_json;
    items_file >> items_json;

    for (nlohmann::json::iterator it = items_json.begin()->begin(); it != items_json.begin()->end(); ++it) {
        std::string c = it->begin().value();
        char* co = const_cast<char*>(c.c_str());
        nlohmann::json::iterator temp = it->begin();
        temp ++;
        int d = temp.value();
        temp ++;
        int start = temp.value();
        passengers.push_back(Passenger(start, ci::Color(co)));
        destination.push_back(d);
    }

    brain_ = Brain(locations, connections, metros, 12, passengers, destination);
}

void MiniMetroApp::mouseDown(ci::app::MouseEvent event) {
    brain_.HandleBrush(event.getPos());
}

void MiniMetroApp::mouseDrag(ci::app::MouseEvent event) {
    brain_.HandleBrush(event.getPos());
}

void MiniMetroApp::draw() {
    ci::Color background_color(0.92, 0.92, 0.92);
    ci::gl::clear(background_color);
    brain_.Display();
}

void MiniMetroApp::update() {
    brain_.AdvanceOneFrame();
}

}
