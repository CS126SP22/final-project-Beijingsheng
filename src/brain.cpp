//
// Created by clark on 2022/4/12.
//
#include "brain.h"

namespace minimetro {

using glm::vec2;

Brain::Brain() {}

Brain::Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
             std::vector<Metro> metros, int station_radius,
             std::vector<Item> items, std::vector<int> d,
             int kWindowSize) {
    this->kWindowSize = kWindowSize;
    this->station_locations_ = locations;
    this->station_connections_ = connections;
    this->station_radius_ = station_radius;
    this->metros_ = metros;
    this->items_ = items;
    this->destinations_ = d;
    this->dijkstra_ = Dijkstra(InitDijkstra());
    InitValues();
    InitMetro();
    InitItems();
}

/**
 * Initialize class variables
 */
void Brain::InitValues() {
    for (size_t i = 0; i < this->station_locations_.size(); i++) {
        std::vector<int> p;
        this->platforms_.push_back(p);
        this->visitor_counts_.push_back(0);
    }
    for (size_t i = 0; i < this->items_.size(); i++) {
        std::vector<int> h = dijkstra_.GetPath(destinations_[i]);
        this->cur_heights_.push_back(h);
        this->total_steps_needed_ += h[this->items_[i].cur_stop_];
        this->init_heights_.push_back(h[this->items_[i].cur_stop_]);
        this->visitor_counts_[this->items_[i].cur_stop_] += 1;
        this->item_locations_.push_back(std::vector<int> {0, 0});
    }
}

/**
 * Initialize graph_ needed for Dijkstra Algorithm
 * @return graph_
 */
Dijkstra Brain::InitDijkstra() {
    std::vector<std::vector<int>> graph;
    for (int i = 0; i < station_locations_.size(); i++) {
        std::vector<int> temp;
        for (int j = 0; j < station_locations_.size(); j++)
            temp.push_back(0);
        graph.push_back(temp);
    }
    for (int i = 0; i < metros_.size(); i++) {
        carry_counts_.push_back(0);
        for (int j = 0; j < metros_[i].route_.size() - 1; j++)
            graph[metros_[i].route_[j + 1]][metros_[i].route_[j]] = 1;
    }
    return graph;
}

/**
 * Initialize starting station for each metro
 */
void Brain::InitMetro() {
    for (size_t i = 0; i < metros_.size(); i++) {
        metros_[i].location_ = station_locations_[metros_[i].GetCurStop()];
    }
}

/**
 * Initialize starting station for each item
 */
void Brain::InitItems() {
    for (size_t i = 0; i < items_.size(); i++) {
        platforms_[items_[i].GetCurStop()].push_back(i);
    }
}

/**
 * Display connections between stations
 */
void Brain::DisplayConnections() {
    for (unsigned int i = 0; i < station_connections_.size(); i++) {
        for (unsigned int j = i + 1; j < station_connections_.size(); j++) {
            if (station_connections_[i][j] == 1) {
                ci::gl::color(ci::Color("black"));
                ci::gl::drawLine(glm::vec2(left_ + station_locations_[i][0] + station_radius_ * 0.5, top_ + station_locations_[i][1] + station_radius_ * 0.5), glm::vec2(left_ + station_locations_[j][0] + station_radius_ * 0.5, top_ + station_locations_[j][1] + station_radius_ * 0.5));
                ci::gl::color(ci::Color("black"));
                ci::gl::drawLine(glm::vec2(left_ + station_locations_[i][0] - station_radius_ * 0.5, top_ + station_locations_[i][1] - station_radius_ * 0.5), glm::vec2(left_ + station_locations_[j][0] - station_radius_ * 0.5, top_ + station_locations_[j][1] - station_radius_ * 0.5));
            }
        }
    }
}

/**
 * Draw shadow for station i
 * @param i
 */
void Brain::DrawStationShadow(int i) {
    ci::Rectf r;
    ci::gl::color(ci::Color("gray"));
    r.set(left_ + station_locations_[i][0] - station_radius_ * 1.5 + 4,
          top_ + station_locations_[i][1] - station_radius_ * 1.5 + 4,
          left_ + station_locations_[i][0] + station_radius_ * 1.5 + 4,
          top_ + station_locations_[i][1] + station_radius_ * 1.5 + 4);
    ci::gl::drawSolidRoundedRect(r, 4, 0,
                                 glm::vec2(left_ + station_locations_[i][0] - station_radius_,
                                           top_ + station_locations_[i][1] - station_radius_),
                                           glm::vec2(left_ + station_locations_[i][0] + station_radius_,
                                                     top_ + station_locations_[i][1] + station_radius_));
}

/**
 * Display each station
 */
void Brain::DisplayStations() {
    for (unsigned int i = 0; i < station_locations_.size(); i++) {
        DrawStationShadow(i);
        ci::Rectf r;
        if (platforms_[i].size() == 0) ci::gl::color(ci::Color(0.31, 1, 0.39));
        else if (platforms_[i].size() == 1) ci::gl::color(ci::Color(1, 0.87, 0.58));
        else if (platforms_[i].size() >= 2) ci::gl::color(ci::Color(1, 0.59, 0.59));
        r.set(left_ + station_locations_[i][0] - station_radius_ * 1.5,top_ + station_locations_[i][1] - station_radius_ * 1.5,
              left_ + station_locations_[i][0] + station_radius_ * 1.5,top_ + station_locations_[i][1] + station_radius_ * 1.5);
        ci::gl::drawSolidRoundedRect(r, 4, 0, glm::vec2(left_ + station_locations_[i][0] - station_radius_,
                                                        top_ + station_locations_[i][1] - station_radius_),
                                     glm::vec2(left_ + station_locations_[i][0] + station_radius_,
                                               top_ + station_locations_[i][1] + station_radius_));
    }
}

/**
 * Display each metro's current location_
 */
void Brain::DisplayMetros() {
    for (unsigned int i = 0; i < metros_.size(); i++) {
        ci::gl::color(metros_[i].color_);
        ci::Rectf r;
        r.set(left_ + metros_[i].location_[0] - station_radius_ * 0.9, top_ + metros_[i].location_[1] - station_radius_ * 0.9, left_ + metros_[i].location_[0] + station_radius_ * 0.9, top_ + metros_[i].location_[1] + station_radius_ * 0.9);
        ci::gl::drawSolidRect(r);
    }
}

/**
 * Display each item's current location_
 */
void Brain::DisplayItems() {
    for (size_t i = 0; i < platforms_.size(); i++) {
        for (size_t j = 0; j < platforms_[i].size(); j++) {
            if (items_[platforms_[i][j]].cur_stop_ != destinations_[platforms_[i][j]])
                ci::gl::color(items_[platforms_[i][j]].color_);
            else ci::gl::color(ci::Color("green"));
            if (items_[platforms_[i][j]].on_metro_ == -1) {
                item_locations_[platforms_[i][j]][0] = left_ + station_locations_[items_[platforms_[i][j]].cur_stop_][0] - (j + 1.8) * station_radius_ * 0.9;
                item_locations_[platforms_[i][j]][1] = top_ + station_locations_[items_[platforms_[i][j]].cur_stop_][1] - (j + 1.8) * station_radius_ * 0.9;
                ci::gl::drawSolidCircle(glm::vec2(item_locations_[platforms_[i][j]][0], item_locations_[platforms_[i][j]][1]), station_radius_ * 0.6);
            }
        }
    }
    DisplayItemsOnTravel();
}

/**
 * Display items that are on travelling
 */
void Brain::DisplayItemsOnTravel() {
    for (size_t i = 0; i < items_.size(); i++) {
        if (items_[i].on_metro_ != -1) {
            item_locations_[i][0] = left_ + metros_[items_[i].on_metro_].location_[0];
            item_locations_[i][1] = top_ + metros_[items_[i].on_metro_].location_[1];
            ci::gl::color(items_[i].color_);
            ci::gl::drawSolidCircle(glm::vec2(item_locations_[i][0], item_locations_[i][1]), station_radius_ * 0.6);
        }
    }
}

/**
 * Display information: steps done, total steps, on click information
 */
void Brain::DisplayInformation() {
    int temp = 0;
    for (int i = 0; i < items_.size(); i++)
        temp += cur_heights_[i][items_[i].cur_stop_];
    ci::gl::drawStringCentered(std::to_string(total_steps_needed_ - temp) + "/" + std::to_string(total_steps_needed_),
                               vec2(300, 30), ci::ColorA(0, 0, 0, 1),
                               ci::Font("helvetica", 30));
    ci::gl::drawStringCentered(message_ , vec2(300, 80),
                               ci::ColorA(0, 0, 0, 1),
                               ci::Font("helvetica", 18));
}

/**
 * Call all display functions in order
 */
void Brain::Display() {
    DisplayConnections();
    DisplayStations();
    DisplayMetros();
    DisplayItems();
    DisplayInformation();
    DisplaySpeedControl();
    DisplayScrollBars();
}

/**
 * Display scroll bar, horizontal and vertical
 */
void Brain::DisplayScrollBars() {
    ci::gl::color(ci::Color("gray"));
    ci::Rectf r;
    r.set(kWindowSize - 20, 80, kWindowSize, kWindowSize - 20);
    ci::gl::drawSolidRect(r);
    r.set(80, kWindowSize - 20, kWindowSize - 20, kWindowSize);
    ci::gl::drawSolidRect(r);
    ci::gl::color(ci::Color("white"));
    r.set(kWindowSize - 20, y_scroll_ - 20, kWindowSize, y_scroll_ + 20);
    ci::gl::drawSolidRoundedRect(r, 5, 0, glm::vec2(kWindowSize-20, 100 - (top_ * (kWindowSize - 125)) - 25), glm::vec2(kWindowSize, 100 - (top_ * (kWindowSize - 125)) + 25));
    r.set(x_scroll_ - 20, kWindowSize - 20, x_scroll_ + 20, kWindowSize);
    ci::gl::drawSolidRoundedRect(r, 5, 0, glm::vec2(kWindowSize-20, 100 - (top_ * (kWindowSize - 125)) - 25), glm::vec2(kWindowSize, 100 - (top_ * (kWindowSize - 125)) + 25));
}

/**
 * Display speed control button
 */
void Brain::DisplaySpeedControl() {
    ci::Rectf r;
    ci::gl::color(ci::Color(0.96, 1, 0.67));
    int temp = ((this->speed_ - 1.2) / 3.8) * 200;
    r.set(600 + temp - 5, 75, 600 + temp + 5, 85);
    ci::gl::drawSolidRoundedRect(r, 5, 0, glm::vec2(600, 75), glm::vec2(800, 85));
}

/**
 * On board function for items first time boarding a metro
 * @param i metro idx
 * @param p item idx
 * @param station station idx
 * @param idx
 */
void Brain::OnBoardFirstTime(int i, int p, int station, int idx) {
    platforms_[station].erase(platforms_[station].begin() + idx);
    metros_[i].passenger_ = p;
    carry_counts_[i] += 1;
    items_[p].on_metro_ = i;
    items_[p].visit_hist_.push_back(station);
}

/**
 * On board function for items already started their route_
 * @param i metro idx
 * @param p item idx
 * @param station station idx
 * @param idx
 */
void Brain::OnBoardToNext(int i, int p, int station, int idx) {
    platforms_[station].erase(platforms_[station].begin() + idx);
    metros_[i].passenger_ = p;
    carry_counts_[i] += 1;
    items_[p].on_metro_ = i;
    items_[p].visit_hist_.push_back(station);
}

/**
 * Called when metro i picks up an item at station
 * @param i metro idx
 * @param station station idx
 */
void Brain::OnBoard(int i, int station) {
    if (metros_[i].passenger_ != -1) return;
    if (platforms_[station].size() > 0) {
        for (size_t idx = 0; idx < platforms_[station].size(); idx++) {
            int p = platforms_[station][idx];
            if (station == destinations_[p]) continue;
            if (items_[p].cur_stop_ != destinations_[p]) {
                if (items_[p].visit_hist_.size() == 0)
                    OnBoardFirstTime(i, p, station, idx);
                else if (items_[p].visit_hist_.size() > 0 && cur_heights_[p][items_[p].visit_hist_[items_[p].visit_hist_.size() - 1]] > cur_heights_[p][metros_[i].GetNextStop()]) {
                    OnBoardToNext(i, p, station, idx);
                }
                break;
            }
        }
    }
}

/**
 * Called when metro i drop off an item at station
 * @param i metro idx
 * @param station station idx
 */
void Brain::OffBoard(int i, int station) {
    int p = metros_[i].passenger_;
    if (station == destinations_[p]) {
        metros_[i].passenger_ = -1;
        items_[p].on_metro_ = -1;
        items_[p].cur_stop_ = station;
        platforms_[station].push_back(p);
        visitor_counts_[station] += 1;
    }
    else if (cur_heights_[p][items_[p].visit_hist_[items_[p].visit_hist_.size() - 1]] >= cur_heights_[p][station]) {
        metros_[i].passenger_ = -1;
        items_[p].on_metro_ = -1;
        items_[p].cur_stop_ = station;
        platforms_[station].push_back(p);
        visitor_counts_[station] += 1;
    }
}

/**
 * Called when metro i arrives at its next stop
 * @param i next stop idx
 */
void Brain::UpdateArriving(int i) {
    metros_[i].location_[0] = station_locations_[metros_[i].GetNextStop()][0];
    metros_[i].location_[1] = station_locations_[metros_[i].GetNextStop()][1];
    metros_[i].OnArrive();
    if (metros_[i].passenger_ == -1) {
        OnBoard(i, metros_[i].GetCurStop());
    } else {
        OffBoard(i, metros_[i].GetCurStop());
        OnBoard(i, metros_[i].GetCurStop());
    }
}

/**
 * Called when metro i leaves its current stop
 * @param i current stop idx
 */
void Brain::UpdateDriving(int i) {
    float x1 = station_locations_[metros_[i].route_[metros_[i].next_stop_idx_]][1] - metros_[i].location_[1];
    float x2 = station_locations_[metros_[i].route_[metros_[i].next_stop_idx_]][0] - metros_[i].location_[0];
    float x3 = sqrt(x1 * x1 + x2 * x2);
    metros_[i].location_[0] += speed_ * x2 / x3;
    metros_[i].location_[1] += speed_ * x1 / x3;
}

void Brain::AdvanceOneFrame() {
    if (!on_pause_) {
        int count = 0;
        for (size_t i = 0; i < items_.size(); i++)
            if (items_[i].cur_stop_ == destinations_[i]) count ++;
        if (count == items_.size()) return;
        for (size_t i = 0; i < metros_.size(); i++) {
            if (glm::length(glm::vec2(metros_[i].location_[0], metros_[i].location_[1])
                            - glm::vec2(station_locations_[metros_[i].GetNextStop()][0], station_locations_[metros_[i].GetNextStop()][1]))
                < station_radius_ * 0.2) {
                UpdateArriving(i);
            } else
                UpdateDriving(i);
        }
    }
}

void Brain::HandleVerticalScrollBar(const vec2 &vec) {
    top_ = 100 - 800 * (vec[1] - 100)/(kWindowSize - 145);
    y_scroll_ = vec[1];
}

void Brain::HandleHorizontalScrollBar(const vec2 &vec) {
    left_ = 100 - 800 * (vec[0] - 100)/(kWindowSize - 145);
    x_scroll_ = vec[0];
}

void Brain::HandleSpeedControl(const vec2 &vec) {
    this->speed_ = 1.2 + 3.8 * (vec[0] - 600) / 200;
}

bool Brain::HandleClickItem(const vec2 &vec) {
    for (int i = 0; i < items_.size(); i++) {
        if ((vec[0] - item_locations_[i][0]) * (vec[0] - item_locations_[i][0])
            + (vec[1] - item_locations_[i][1]) * (vec[1] - item_locations_[i][1])
            <= station_radius_ * 0.7 * station_radius_ * 0.7) {
            if (!cur_heights_[i][items_[i].cur_stop_]) {
                message_ = "Item " + std::to_string(i + 1) + " moved " + std::to_string(init_heights_[i]) + " times.";
            } else {
                message_ = "Item " + std::to_string(i + 1) + " needs " + std::to_string(cur_heights_[i][items_[i].cur_stop_]) + " more moves.";
            }
            return true;
        }
    }
    return false;
}

bool Brain::HandleClickMetro(const vec2 &vec) {
    for (int i = 0; i < metros_.size(); i++) {
        if (abs(vec[0] - left_ - metros_[i].location_[0]) <= station_radius_ * 0.9) {
            if (abs(vec[1] - top_ - metros_[i].location_[1]) <= station_radius_ * 0.9) {
                message_ = "Metro " + std::to_string(i) + " has carried items " + std::to_string(carry_counts_[i]) + " times.";
                return true;
            }
        }
    }
    return false;
}

bool Brain::HandleClickStation(const vec2 &vec) {
    for (int i = 0; i < station_locations_.size(); i++) {
        if (abs(vec[0] - left_ - station_locations_[i][0]) <= station_radius_) {
            if (abs(vec[1] - top_ - station_locations_[i][1]) <= station_radius_) {
                message_ = "Station " + std::to_string(i) + " has been visited " + std::to_string(visitor_counts_[i]) + " times.";
                return true;
            }
        }
    }
    return false;
}

void Brain::HandleBrush(const vec2 &vec) {
    if (vec[0] > kWindowSize - 20 && vec[1] > 100 && vec[0] < kWindowSize && vec[1] < kWindowSize - 40) {
        HandleVerticalScrollBar(vec);
    } else if (vec[0] > 100 && vec[1] > kWindowSize - 20 && vec[0] < kWindowSize - 40 && vec[1] < kWindowSize) {
        HandleHorizontalScrollBar(vec);
    } else if (vec[0] >= 600 && vec[0] <= 800 && vec[1] >= 75 && vec[1] <= 85) {
        HandleSpeedControl(vec);
    } else if (vec[0] >= 592 && vec[0] <= 682 && vec[1] >= 112 && vec[1] <= 145) {
        on_pause_ = !on_pause_;
    }
    if (HandleClickItem(vec)) return;
    if (HandleClickStation(vec)) return;
    if (HandleClickMetro(vec)) return;
}

}