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

int Point::getX() const
{
    return x;
}

int Point::getY() const
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

Point PolygonalChain::getPoint(int i) const
{
    return points[i];
}

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &other) {
    if (&other == this) {
        return *this;
    }

    n = other.n;
    delete[] points;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}


int PolygonalChain::getN() const
{
    return n;
}

double PolygonalChain::perimeter() const
{
    double result = 0;
    for (int i = 0; i < n - 1; ++i) {
        result += sqrt(pow(points[i].getX() - points[i + 1].getX(), 2.0) + pow(points[i].getY() - points[i + 1].getY(), 2.0));
    }
    return result;
}

PolygonalChain::~PolygonalChain()
{
    delete[] points;
}



double ClosedPolygonalChain::perimeter() const
{
    //fixed perimeter from base class
    double result = PolygonalChain::perimeter();

    result += sqrt(pow(points[n - 1].getX() - points[0].getX(), 2) + pow(points[n - 1].getY() - points[0].getY(), 2));

    return result;
}

double Polygon::area() const
{

    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += points[i].getX() * points[(i + 1) % n].getY() - points[(i + 1) % n].getX() * points[i].getY();
    }
    return abs(0.5 * s);
}

float Trapezoid::length(const Point &first, const Point &second) const
{
    return sqrt(pow(first.getX() - second.getX(), 2) + pow(first.getY() - second.getY(), 2));
}

bool Triangle::hasRightAngle() const
{
    if ((points[1].getX() - points[0].getX()) * (points[2].getX() - points[0].getX()) + (points[1].getY() - points[0].getY()) * (points[2].getY() - points[0].getY()) == 0)
    {
        return true;
    }
    if ((points[2].getX() - points[1].getX()) * (points[0].getX() - points[1].getX()) + (points[2].getY() - points[1].getY()) * (points[0].getY() - points[1].getY()) == 0)
    {
        return true;
    }
    if ((points[1].getX() - points[2].getX()) * (points[0].getX() - points[2].getX()) + (points[1].getY() - points[2].getY()) * (points[0].getY() - points[2].getY()) == 0)
    {
        return true;
    }
    return false;


}

float Trapezoid::height() const
{
    return (2 * this->area()) / (length(points[1], points[2]) + length(points[3], points[0]));
}

Trapezoid::Trapezoid(const Trapezoid &tr)  : Polygon(tr) {
    this->n = tr.n;
    points = new Point[n];
    for (int i = 0; i < n; ++i) {
        points[i] = tr.getPoint(i);
    }
}

double RegularPolygon::perimeter() const
{
    double a = sqrt(pow(points[0].getX() - points[1].getX(), 2.0) + pow( points[0].getY() - points[1].getY(), 2.0));
    return this->n * a;
}

double RegularPolygon::area() const
{
    double a = sqrt(pow(points[0].getX() - points[1].getX(), 2.0) + pow( points[0].getY() - points[1].getY(), 2.0));
    return (a * a * this->n) / (4.0 * tan(M_PI / this->n));
}