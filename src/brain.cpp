//
// Created by clark on 2022/4/12.
//
#include "brain.h"

namespace minimetro {

using glm::vec2;

Brain::Brain() {}

Brain::Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
             std::vector<Metro> metros, int station_radius,
             std::vector<Passenger> passengers, std::vector<int> d) {
    //locations for all station
    this->locations = locations;
    //connections between stations
    this->connections = connections;
    //station radius on graph
    this->station_radius_ = station_radius;
    //all metro routes
    this->metros = metros;
    //all passengers, color and start station
    this->passengers = passengers;
    //all passengers' destination
    this->destination = d;
    //height of each station
    this->dijkstra = Dijkstra(InitDijkstra());

    for (size_t i = 0; i < locations.size(); i++) {
        std::vector<int> p;
        this->platform.push_back(p);
    }
    for (size_t i = 0; i < passengers.size(); i++) {
        std::vector<int> h = dijkstra.GetPath(destination[i], 0);
        this->heights.push_back(h);
    }

    InitMetro();
    InitPassengers();

    for (int i = 0; i < heights.size(); i++) {
        for (int j = 0; j < heights[i].size(); j++) {
            std::cout << heights[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Dijkstra Brain::InitDijkstra() {
    std::vector<std::vector<int>> graph;
    for (int i = 0; i < locations.size(); i++) {
        std::vector<int> temp;
        for (int j = 0; j < locations.size(); j++) {
            temp.push_back(0);
        }
        graph.push_back(temp);
    }

    for (int i = 0; i < metros.size(); i++) {
        for (int j = 0; j < metros[i].route.size() - 1; j++) {
            graph[metros[i].route[j+1]][metros[i].route[j]] = 1;
        }
    }

    return graph;
}

void Brain::InitMetro() {
    for (size_t i = 0; i < metros.size(); i++) {
        metros[i].location = locations[metros[i].GetCurStop()];
    }
}

void Brain::InitPassengers() {
    for (size_t i = 0; i < passengers.size(); i++) {
        platform[passengers[i].GetCurStop()].push_back(i);
    }
}

void Brain::DisplayConnections() {
    for (unsigned int i = 0; i < connections.size(); i++) {
        for (unsigned int j = i + 1; j < connections.size(); j++) {
            if (connections[i][j] == 1) {
                ci::gl::color(ci::Color("blue"));
                ci::gl::drawLine(glm::vec2(locations[i][0], locations[i][1]), glm::vec2(locations[j][0], locations[j][1]));
            }
        }
    }
}

void Brain::DisplayStations() {
    for (unsigned int i = 0; i < locations.size(); i++) {
        if (platform[i].size() == 0)
            ci::gl::color(ci::Color("green"));
        else if (platform[i].size() == 1)
            ci::gl::color(ci::Color("orange"));
        else if (platform[i].size() >= 2)
            ci::gl::color(ci::Color("red"));
        ci::gl::drawSolidCircle(glm::vec2(locations[i][0], locations[i][1]), station_radius_);
    }
}

void Brain::DisplayMetros() {
    for (unsigned int i = 0; i < metros.size(); i++) {
        ci::gl::color(metros[i].color);
        ci::gl::drawSolidCircle(glm::vec2(metros[i].location[0], metros[i].location[1]), station_radius_ * 0.9);
    }
}

void Brain::DisplayTourists() {
    for (size_t i = 0; i < platform.size(); i++) {
        for (size_t j = 0; j < platform[i].size(); j++) {
            ci::gl::color(passengers[platform[i][j]].color);
            if (passengers[platform[i][j]].on_metro == -1) {
                ci::gl::drawSolidCircle(glm::vec2(locations[passengers[platform[i][j]].cur_stop][0] - (j + 1) * station_radius_ * 1.2, locations[passengers[platform[i][j]].cur_stop][1] - (j + 1) * station_radius_ * 1.2), station_radius_ * 0.7);
            }
        }
    }

    for (size_t i = 0; i < passengers.size(); i++) {
        if (passengers[i].on_metro != -1) {
            ci::gl::color(passengers[i].color);
            ci::gl::drawSolidCircle(glm::vec2(metros[passengers[i].on_metro].location[0] - station_radius_ * 1.2, metros[passengers[i].on_metro].location[1] - station_radius_ * 1.2), station_radius_ * 0.7);
        }
    }
}

void Brain::Display() {
    DisplayConnections();
    DisplayStations();
    DisplayMetros();
    DisplayTourists();
}

//logic to decide if pick up a passenger when metro i enters station station
void Brain::OnBoard(int i, int station) {
    //don't pick up passenger if this is the destination
    if (metros[i].passenger != -1)
        return;
    //if the station has at least one passenger on the platform
    if (platform[station].size() > 0) {
        //get this passenger's id
        for (size_t idx = 0; idx < platform[station].size(); idx++) {
            int p = platform[station][idx];
            std::cout << p << " " << destination[p] << " " << station << endl;
            if (station == destination[p])
                continue;
            if (passengers[p].cur_stop != destination[p]) {
                //if this passenger hasn't boarded any metro
                if (passengers[p].visited.size() == 0) {
                    //passenger leave platform
                    std::cout << p << " get on metro " << i << " at station " << station << std::endl;
                    platform[station].erase(platform[station].begin() + idx);
                    //passenger board metro
                    metros[i].passenger = p;
                    passengers[p].on_metro = i;
                    //passenger leave that station
                    passengers[p].visited.push_back(station);
                }
                else if (passengers[p].visited.size() > 0 && heights[p][passengers[p].visited[passengers[p].visited.size() - 1]] > heights[p][metros[i].GetNextStop()]) {
                    std::cout << p << " get on metro " << i << " at station " << station << std::endl;
                    platform[station].erase(platform[station].begin() + idx);
                    metros[i].passenger = p;
                    passengers[p].on_metro = i;
                    passengers[p].visited.push_back(station);
                }
                break;
            }
        }
    }
}

void Brain::OffBoard(int i, int station) {
    int p = metros[i].passenger;
    if (station == destination[p]) {
        metros[i].passenger = -1;
        passengers[p].on_metro = -1;
        passengers[p].cur_stop = station;
        std::cout << p << " get off metro " << i << " at station " << station << std::endl;
        platform[station].push_back(p);
    }
    else if (heights[p][passengers[p].visited[passengers[p].visited.size() - 1]] >= heights[p][station]) {
        metros[i].passenger = -1;
        passengers[p].on_metro = -1;
        passengers[p].cur_stop = station;
        std::cout << p << " get off metro " << i << " at station " << station << std::endl;
        platform[station].push_back(p);
    }
}

void Brain::UpdateArriving(int i) {
    metros[i].location[0] = locations[metros[i].GetNextStop()][0];
    metros[i].location[1] = locations[metros[i].GetNextStop()][1];
    metros[i].OnArrive();
    if (metros[i].passenger == -1) {
        OnBoard(i, metros[i].GetCurStop());
    } else {
        OffBoard(i, metros[i].GetCurStop());
        OnBoard(i, metros[i].GetCurStop());
    }
}

void Brain::UpdateDriving(int i) {
    float x1 = locations[metros[i].route[metros[i].next_stop_idx]][1] - metros[i].location[1];
    float x2 = locations[metros[i].route[metros[i].next_stop_idx]][0] - metros[i].location[0];
    float x3 = sqrt(x1 * x1 + x2 * x2);
    metros[i].location[0] += 5 * x2 / x3;
    metros[i].location[1] += 5 * x1 / x3;
}

void Brain::AdvanceOneFrame() {
    for (size_t i = 0; i < metros.size(); i++) {
        if (glm::length(glm::vec2(metros[i].location[0], metros[i].location[1])
                            - glm::vec2(locations[metros[i].GetNextStop()][0], locations[metros[i].GetNextStop()][1]))
                            < station_radius_) {
            UpdateArriving(i);
        } else {
            UpdateDriving(i);
        }
    }
}

}