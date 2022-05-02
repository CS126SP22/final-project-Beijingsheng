//
// Created by clark on 2022/4/12.
//
#include "../include/simulator.h"
// CITE: https://github.com/nlohmann/json/
#include "json.hpp"

namespace minimetro {

MiniMetroApp::MiniMetroApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
    readDataStations();
    readDataMetros();
    readDataItems();
    brain_ = Brain(station_locations_, station_connections_, metros_, 12, items_, destinations_, kWindowSize);
}

/**
 * Read data of stations, including each station's location_ and their station_connections_,
 * from kFileStationsLocation
 */
void MiniMetroApp::readDataStations() {
    std::ifstream stations_file(kFileStationsLocation);
    nlohmann::json stations_json;
    stations_file >> stations_json;
    int num_station = stations_json.begin()->size();
    for (nlohmann::json::iterator it = stations_json.begin()->begin(); it != stations_json.begin()->end(); ++it) {
        std::vector<int> temp{};
        for (int j = 0; j < num_station; j++) temp.push_back(0);
        for (int i = 0; i < it->begin().value().size(); i++) temp[int(it->begin().value()[i])] = 1;
        station_connections_.push_back(temp);
        nlohmann::json::iterator it_temp = it->begin();
        it_temp ++;
        std::vector<float> temp2;
        temp2.push_back(it_temp.value());
        it_temp ++;
        temp2.push_back(it_temp.value());
        station_locations_.push_back(temp2);
    }
}

/**
 * Read data of Metros,
 * from kFileMetrosLocation
 */
void MiniMetroApp::readDataMetros() {
    std::ifstream metros_file(kFileMetrosLocation);
    nlohmann::json metros_json;
    metros_file >> metros_json;
    for (nlohmann::json::iterator it = metros_json.begin()->begin(); it != metros_json.begin()->end(); ++it) {
        nlohmann::json::iterator temp = it->begin();
        temp ++;
        std::vector<int> temp_route{};
        for (int i = 0; i < temp.value().size(); i++) temp_route.push_back(temp.value()[i]);
        std::string c = it->begin().value();
        char* co = const_cast<char*>(c.c_str());
        metros_.push_back(Metro(temp_route, ci::Color(co)));
    }
}

/**
 * Read data of items, including item detail and each item's destinations,
 * from kFileItemsLocation
 */
void MiniMetroApp::readDataItems() {
    std::ifstream items_file(kFileItemsLocation);
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
        items_.push_back(Item(start, ci::Color(co)));
        destinations_.push_back(d);
    }
}

/**
 * Override of mouseDown
 * @param event mouse down event
 */
void MiniMetroApp::mouseDown(ci::app::MouseEvent event) {
    brain_.HandleBrush(event.getPos());
}

/**
 * Override of mouseDrag
 * @param event mouse drag event
 */
void MiniMetroApp::mouseDrag(ci::app::MouseEvent event) {
    brain_.HandleBrush(event.getPos());
}

/**
 * Draw background, speed_ control panel, and visualize brain data
 */
void MiniMetroApp::draw() {
    ci::Color background_color(0.92, 0.92, 0.92);
    ci::gl::clear(background_color);
    drawSpeedControlPanel();
    brain_.Display();
}

/**
 * Draw speed_ control panel, including title, slider, and pause button
 */
void MiniMetroApp::drawSpeedControlPanel() {
    ci::gl::drawStringCentered("speed_", vec2(630, 50), ci::ColorA(0, 0, 0, 1), ci::Font("helvetica", 20));
    ci::Rectf r, r2;
    ci::gl::color(ci::Color("gray"));
    r.set(592, 72, 808, 88);
    ci::gl::drawSolidRoundedRect(r, 5, 0, glm::vec2(600, 75), glm::vec2(800, 85));
    ci::gl::color(ci::Color(0.78, 0.86, 1));
    r2.set(592, 112, 682, 145);
    ci::gl::drawSolidRoundedRect(r2, 5, 0, glm::vec2(600, 75), glm::vec2(800, 85));
    ci::gl::drawStringCentered("|►", vec2(637, 127), ci::ColorA(0, 0, 0, 1), ci::Font("helvetica", 20));
}

void MiniMetroApp::update() {
    brain_.AdvanceOneFrame();
}

}
