//
// Created by clark on 2022/4/13.
//
#include "passenger.h"

namespace minimetro {

    Passenger::Passenger(int start_station, ci::Color color) {
        this->color = color;
        this->cur_stop = start_station;
        this->stop_visited = 0;
        on_metro = -1;
        std::vector<int> v;
        this->visited = v;
    }

    int Passenger::GetCurStop() {
        return cur_stop;
    }

}
