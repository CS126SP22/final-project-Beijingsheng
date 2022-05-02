//
// Created by clark on 2022/4/13.
//
#include "item.h"

namespace minimetro {

/**
 * Constructor with start station and item color_
 * @param start_station
 * @param color
 */
Item::Item(int start_station, ci::Color color) {
    this->color_ = color;
    this->cur_stop_ = start_station;
    this->stop_visited_ = 0;
    on_metro_ = -1;
    std::vector<int> v;
    this->visit_hist_ = v;
}

/**
 * Getter for current stop
 * @return current stop
 */
int Item::GetCurStop() {
    return cur_stop_;
}

}
