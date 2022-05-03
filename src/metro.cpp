//
// Created by clark on 2022/4/13.
//
#include "metro.h"

namespace minimetro {

Metro::Metro() {}

/**
 * Constructor with metro route and color
 * @param route
 * @param color
 */
Metro::Metro(std::vector<int> route, ci::Color color) {
    this->location_.push_back(0);
    this->location_.push_back(0);
    this->passenger_ = -1;
    this->cur_stop_idx_ = 0;
    this->next_stop_idx_ = 1;
    this->color_ = color;
    this->route_ = route;
}

/**
 * Getter for current stop idx
 * @return current stop idx
 */
int Metro::GetCurStop() {
    return route_[cur_stop_idx_];
}

/**
 * Getter for next stop idx
 * @return next stop idx
 */
int Metro::GetNextStop() {
    return route_[next_stop_idx_];
}

/**
 * Update stop indexes upon arrival
 */
void Metro::OnArrive() {
    cur_stop_idx_ = next_stop_idx_;
    int temp = (next_stop_idx_ + 1) % route_.size();
    if (temp == route_.size() - 1)
        temp = 0;
    next_stop_idx_ = temp;
}

}
