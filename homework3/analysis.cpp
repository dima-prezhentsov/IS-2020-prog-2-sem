#include "analysis.h"
#include <sstream>
#include <map>
#include <cmath>

using namespace std;

TransportStation::TransportStation(string name, string tov, const string& r, const string& coord, const string& strt_name) {
    name_station = name;
    type_of_vehicle = tov;
    const char delim = ',';

    string sn;
    stringstream ss0(strt_name);
    getline(ss0, street_name, delim);

    string route;
    stringstream ss1(r);
    while (getline(ss1, route, delim)) {
        routes.push_back(route);
    }

    string x, y;
    stringstream ss2(coord);
    getline(ss2, x, delim);
    getline(ss2, y, delim);
    coordinates.first = stod(x);
    coordinates.second = stod(y);

}

void TransportStation::getInfo() {
    cout << name_station
         << " "
         << type_of_vehicle
         << " "
         << street_name
         << " ";
    for (auto & route : routes) {
        cout << route << " ";
    }
    cout << " " << "("
         << coordinates.first << ";"
         << coordinates.second << ")\n";
}

vector<string> & TransportStation::getRoutes() {
    return routes;
}

string TransportStation::getTypeOfVehicle() {
    return type_of_vehicle;
}

string TransportStation::getStreet() {
    return street_name;
}

double TransportStation::getX() const {
    return coordinates.first;
}

double TransportStation::getY() const {
    return coordinates.second;
}

void MaxStopsRoute(vector<TransportStation>& allStations) {
    map<string, int> maxStationInRoute_BUS;
    map<string, int> maxStationInRoute_TRAM;
    map<string, int> maxStationInRoute_TROLLEYBUS;
    for (auto station : allStations) {
        if (station.getTypeOfVehicle() == "Трамвай") {
            for (const auto& route : station.getRoutes()) {
                maxStationInRoute_TRAM[route] += 1;
            }
        }
        if (station.getTypeOfVehicle() == "Троллейбус") {
            for (const auto& route : station.getRoutes()) {
                maxStationInRoute_TROLLEYBUS[route] += 1;
            }
        }
        if (station.getTypeOfVehicle() == "Автобус") {
            for (const auto& route : station.getRoutes()) {
                maxStationInRoute_BUS[route] += 1;
            }
        }
    }

    int maxRoute_TRAM = 0;
    int maxRoute_BUS = 0;
    int maxRoute_TROLLEYBUS = 0;
    string Route_TRAM;
    string Route_BUS;
    string Route_TROLLEYBUS;

    for (auto& el : maxStationInRoute_TRAM) {
        if (el.second > maxRoute_TRAM) {
            maxRoute_TRAM = el.second;
            Route_TRAM = el.first;
        }
    }
    for (auto& el : maxStationInRoute_BUS) {
        if (el.second > maxRoute_BUS) {
            maxRoute_BUS = el.second;
            Route_BUS = el.first;
        }
    }
    for (auto& el : maxStationInRoute_TROLLEYBUS) {
        if (el.second > maxRoute_TROLLEYBUS) {
            maxRoute_TROLLEYBUS = el.second;
            Route_TROLLEYBUS = el.first;
        }
    }

    cout << "Route with the most tram stops is " << Route_TRAM << endl;
    cout << "Route with the most trolleybus stops is " << Route_TROLLEYBUS << endl;
    cout << "Route with the most bus stops is " << Route_BUS << endl;

}

void MaxStopsStreet(vector<TransportStation>& allStation) {
    map<string, int> Streets;
    for (auto station : allStation) {
        if (!station.getStreet().empty())
            Streets[station.getStreet()] += 1;
    }
    int maxStops = 0;
    string result;
    for (const auto& el : Streets) {
        if (el.second > maxStops) {
            maxStops = el.second;
            result = el.first;
        }
    }
    cout << "Street with the most stops is " << result << endl;
}
//todo all type of vehicle
void LongestRoute(vector<TransportStation>& allStations) {
    map<string, vector<TransportStation>> Routes_BUS;
    map<string, vector<TransportStation>> Routes_TRAM;
    map<string, vector<TransportStation>> Routes_TROLLEYBUS;
    map<string, double> distance_BUS;
    map<string, double> distance_TRAM;
    map<string, double> distance_TROLLEYBUS;
    double max_dist_BUS = 0;
    double max_dist_TRAM = 0;
    double max_dist_TROLLEYBUS = 0;
    string result_BUS;
    string result_TRAM;
    string result_TROLLEYBUS;
    //todo copy-paste
    for (auto& station : allStations) {
        if (!station.getStreet().empty()) {
            if (station.getTypeOfVehicle() == "Автобус") {
                for (const auto& rt : station.getRoutes()) {
                    Routes_BUS[rt].push_back(station);
                }
            }
            if (station.getTypeOfVehicle() == "Трамвай") {
                for (const auto& rt : station.getRoutes()) {
                    Routes_TRAM[rt].push_back(station);
                }
            }
            if (station.getTypeOfVehicle() == "Троллейбус") {
                for (const auto& rt : station.getRoutes()) {
                    Routes_TROLLEYBUS[rt].push_back(station);
                }
            }

        }
    }
    //todo use unpacking for pairs
    for (const auto& rt : Routes_BUS) {
        for (size_t i = 0; i < rt.second.size() - 1; ++i) {
            distance_BUS[rt.first] += sqrt(pow(rt.second[i + 1].getX() - rt.second[i].getX(), 2.0) + pow(rt.second[i + 1].getY() - rt.second[i].getY(), 2.0));
        }
    }
    for (const auto& rt : Routes_TRAM) {
        for (size_t i = 0; i < rt.second.size() - 1; ++i) {
            distance_TRAM[rt.first] += sqrt(pow(rt.second[i + 1].getX() - rt.second[i].getX(), 2.0) + pow(rt.second[i + 1].getY() - rt.second[i].getY(), 2.0));
        }
    }
    for (const auto& rt : Routes_TROLLEYBUS) {
        for (size_t i = 0; i < rt.second.size() - 1; ++i) {
            distance_TROLLEYBUS[rt.first] += sqrt(pow(rt.second[i + 1].getX() - rt.second[i].getX(), 2.0) + pow(rt.second[i + 1].getY() - rt.second[i].getY(), 2.0));
        }
    }

    for (const auto& el : distance_BUS) {
        if (el.second > max_dist_BUS) {
            result_BUS = el.first;
            max_dist_BUS = el.second;
        }
    }
    for (const auto& el : distance_TRAM) {
        if (el.second > max_dist_TRAM) {
            result_TRAM = el.first;
            max_dist_TRAM = el.second;
        }
    }
    for (const auto& el : distance_TROLLEYBUS) {
        if (el.second > max_dist_TROLLEYBUS) {
            result_TROLLEYBUS = el.first;
            max_dist_TROLLEYBUS = el.second;
        }
    }

    cout << "Bus route with max distance is " << result_BUS << endl;
    cout << "Tram route with max distance is " << result_TRAM << endl;
    cout << "Trolleybus route with max distance is " << result_TROLLEYBUS << endl;
}