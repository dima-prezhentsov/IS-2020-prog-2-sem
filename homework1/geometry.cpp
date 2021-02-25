#include <iostream> 
#include <math.h>
#include "geometry.h"
using namespace std;

Point::Point() 
{
    x = 0;
    y = 0;
}

Point::Point(int x, int y) 
{
    this->x = x;
    this->y = y;
}

Point::Point(const Point &pt) 
{
    x = pt.x;
    y = pt.y;
}

int Point::getX() 
{
    return x;
}

int Point::getY()
{
    return y;
}

PolygonalChain::PolygonalChain(int n, Point* arr) 
{
    this->n = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = arr[i];
    }
}

Point PolygonalChain::getPoint(int i) 
{
    return points[i];
}

int PolygonalChain::getN() 
{
    return n;
}

int PolygonalChain::perimeter()
{
    int result = 0;
    for (int i = 0; i < n - 1; ++i) {
        result += sqrt(pow(points[i].getX() - points[i + 1].getX(), 2) + pow(points[i].getY() - points[i + 1].getY(), 2));
    }
    return result;
}

PolygonalChain::~PolygonalChain()
{
    delete points;
}

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point* arr)
{
    this->n = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = arr[i];
    }
}

int ClosedPolygonalChain::perimeter() 
{
    int result = 0;
    for (int i = 0; i < n; ++i) {
        result += sqrt(pow(points[i].getX() - points[(i + 1) % n].getX(), 2) + pow(points[i].getY() - points[(i + 1) % n].getY(), 2));
    }
    return result;
}

ClosedPolygonalChain::~ClosedPolygonalChain()
{
    delete points;
}

Polygon::Polygon(int n, Point* arr)
{
    this->n = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = arr[i];
    }
}

float Polygon::area()
{
    float S = 0;
    for (int i = 0; i < n; ++i) {
        S += points[i].getX() * points[(i + 1) % n].getY() - points[(i + 1) % n].getX() * points[i].getY();
    }
    return abs(0.5 * S);
}

Polygon::~Polygon() 
{
    delete points;
}

float length(Point* first, Point* second) 
{
    return sqrt(pow(first->getX() - second->getX(), 2) + pow(first->getY() - second->getY(), 2));
}

Triangle::Triangle(int n, Point* arr) 
{
    this->n = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = arr[i];
    }
}

bool Triangle::hasRightAngle() 
{
    if (length(&points[2], &points[0]) == sqrt(pow( length(&points[0], &points[1]), 2) + pow(length(&points[1], &points[2]),2))) 
    {
        return true;
    }
    else if (length(&points[0], &points[1]) == sqrt(pow(length(&points[1], &points[2]), 2) + pow(length(&points[2], &points[0]),2))) 
    {
        return true;
    }
    else if (length(&points[1], &points[2]) == sqrt(pow(length(&points[2], &points[0]), 2) + pow(length(&points[0], &points[1]),2))) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

Triangle::~Triangle() {
    delete points;
}

Trapezoid::Trapezoid(int n, Point* arr) 
{
    this->n = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = arr[i];
    }
}

float Trapezoid::height()
{
    return (2 * this->area()) / (length(&points[1], &points[2]) + length(&points[3], &points[0]));
}

Trapezoid::~Trapezoid() 
{
    delete points;
}

RegularPolygon::RegularPolygon(int n, Point* arr) 
{
    this->n = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = arr[i];
    }
}

RegularPolygon::~RegularPolygon() 
{
    delete points;
}
