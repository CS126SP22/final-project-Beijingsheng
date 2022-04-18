//
// Created by clark on 2022/4/13.
//
#include "metro.h"

namespace minimetro {

Metro::Metro() {}

Metro::Metro(std::vector<int> route, ci::Color color) {
    this->location.push_back(0);
    this->location.push_back(0);
    this->passenger = -1;
    this->stop_idx = 0;
    this->next_stop_idx = 1;
    this->color = color;
    this->route = route;
}

int Metro::GetCurStop() {
    return route[stop_idx];
}

int Metro::GetNextStop() {
    return route[next_stop_idx];
}

void Metro::OnArrive() {
    stop_idx = next_stop_idx;
    int temp = (next_stop_idx + 1) % route.size();
    if (temp == route.size() - 1)
        temp = 0;
    next_stop_idx = temp;
}

}
