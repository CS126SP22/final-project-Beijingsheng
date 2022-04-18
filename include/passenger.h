//
// Created by clark on 2022/4/13.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace minimetro {

    class Passenger {
    public:
        Passenger(int start_station, ci::Color color);
        int stop_visited;
        int cur_stop;
        ci::Color color;
        int on_metro;
        std::vector<int> visited;
        int GetCurStop();
    private:

    };

}