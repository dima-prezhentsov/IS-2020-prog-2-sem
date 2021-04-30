#include <iostream>
#include "pugixml.hpp"
#include "analysis.h"
#include <vector>
#include <map>


using namespace std;

int main() {
//    setlocale(LC_ALL,"Russian");
    system("chcp 65001");
    const char source[] = "data.xml";
    vector<TransportStation> allStations;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(source);
    pugi::xml_node tools = doc.child("dataset");
    string stop = "Остановка";

    if (result)
    {
        cout << "XML [" << source << "] parsed without errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n\n";

        for (pugi::xml_node tool = tools.child("transport_station"); tool; tool = tool.next_sibling("transport_station")) {
            if (tool.child("object_type").child_value() == stop) {
                allStations.emplace_back(tool.child("name_stopping").child_value(),
                                         tool.child("type_of_vehicle").child_value(),
                                         tool.child("routes").child_value(),
                                         tool.child("coordinates").child_value(),
                                         tool.child("location").child_value());
            }
        }

        MaxStopsRoute(allStations);
        cout << "\n";
        MaxStopsStreet(allStations);
        cout << "\n";
        LongestRoute(allStations);
    }
    else
    {
        cout << "XML [" << source << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        cout << "Error description: " << result.description() << "\n";
        cout << "Error offset: " << result.offset << " (error at [..." << (source + result.offset) << "]\n\n";
    }

    return 0;
}
