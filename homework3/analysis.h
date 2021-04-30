#ifndef LABA3_ANALYSIS_H
#define LABA3_ANALYSIS_H
#include <iostream>
#include <vector>

using namespace std;

class TransportStation {
private:
    string name_station;
    string street_name;
    string type_of_vehicle;
    vector<string> routes;
    pair<double, double> coordinates;
public:
    TransportStation(string name, string tov, const string& r, const string& coord, const string& strt_name);

    void getInfo();

    vector<string>& getRoutes();

    string getTypeOfVehicle();

    string getStreet();

    [[nodiscard]] double getX() const;

    [[nodiscard]] double getY() const;

    ~TransportStation() = default;
};

void MaxStopsRoute(vector<TransportStation>& allStations);

void MaxStopsStreet(vector<TransportStation>& allStations);

void LongestRoute(vector<TransportStation>& allStations);


#endif //LABA3_ANALYSIS_H
