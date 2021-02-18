#include <iostream> 
#include <math.h>
using namespace std;


class Point {
private:
    int x;
    int y;

public:
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point(const Point &pt) {
        x = pt.x;
        y = pt.y;
    }

};

class Polyline {

};

class Closed_Polyline {

};

class Polygon {

};

class Triangle {

};

class Trapezoid {

};

class Regular_Polygon {

};

int main() {

    return 0;
}
