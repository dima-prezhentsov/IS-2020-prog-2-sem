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
    map<string, map<string, int>> numberOfStopsOnRoute; // map<typeOfVehicle, map<routeNumber, value>>
    map<string, pair<string, int>> result;     // map<typeOfVehicle, pair<resRouteNumber, maxValue>>


    for (auto station : allStations) {
        for (const auto& routeNumber : station.getRoutes()) {
            numberOfStopsOnRoute[station.getTypeOfVehicle()][routeNumber] += 1;
        }
    }

    for (auto [typeOfVehicle, Route] : numberOfStopsOnRoute) {
        for (auto [currentRouteNumber, currentValue] : Route) {
            auto [resRouteNumber, maxValue] = result[typeOfVehicle];
            if (currentValue > maxValue) {
                result[typeOfVehicle] = {currentRouteNumber, currentValue};
            }
        }
    }

    for (auto [typeOfVehicle, resPair] : result) {
        auto [resRouteNumber, resValue] = result[typeOfVehicle];
        cout << "Route with the most " << typeOfVehicle << " stops is " << resRouteNumber << endl;
    }

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

void LongestRoute(vector<TransportStation>& allStations) {


    //fixed copy-paste
    //fixed use unpacking for pairs
    map<string, map<string, vector<TransportStation>>> Routes; // map<typeOfVehicle, map<routeNumber, stations vector>>
    map<string, map<string, double>> distance;                 // map<typeOfVehicle, map<routeNumber, value>>
    map<string, pair<double, string>> result;                  // map<typeOfVehicle, pair<maxValue, resultRouteNumber>>
    string typeOfVehicle;
    for (auto& station : allStations) {
        if (!station.getStreet().empty()) {
            typeOfVehicle = station.getTypeOfVehicle();
            for (const auto& routeNumber : station.getRoutes()) {
                Routes[typeOfVehicle][routeNumber].push_back(station);
            }
        }
    }

    for (auto [typeOfVehicle, stationsInRoute] : Routes) {
        for (auto [routeNumber, stations] : stationsInRoute) {
            for (size_t i = 0; i < stations.size() - 1; ++i) {
                distance[typeOfVehicle][routeNumber] += sqrt(pow(stations[i + 1].getX() - stations[i].getX(), 2.0) + pow(stations[i + 1].getY() - stations[i].getY(), 2.0));
            }
        }
    }

    for (auto [typeOfVehicle, distanceInRoute] : distance) {
        for (auto [currentRouteNumber, currentValue] : distanceInRoute) {
            auto [maxValue, resultRouteNumber] = result[typeOfVehicle];
            if (currentValue > maxValue) {
                result[typeOfVehicle] = {currentValue, currentRouteNumber};
            }
        }
    }

    for (auto [typeOfVehicle, resPair] : result) {
        auto [value, routeNumber] = resPair;
        cout << typeOfVehicle << " route with max distance is " << routeNumber << endl;
    }
}