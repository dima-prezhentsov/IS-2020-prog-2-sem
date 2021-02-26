#ifndef GEOMETRY_H
#define GEOMETRY_H

class Point {
private:
    int x;
    int y;

public:
    Point();
    
    Point(int x, int y);

    Point(const Point &pt);

    int getX() const;
    int getY() const;
};

float length(Point* first, Point* second);

class PolygonalChain: public Point {
protected:
    int n;
    Point* points;
public:
    PolygonalChain(int n = 0, Point* arr = nullptr);

    Point getPoint(int i) const;
    
    int getN() const;

    virtual double perimeter() const;

    ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain(int n = 0, Point* arr = nullptr);

    double perimeter() const;

    ~ClosedPolygonalChain();
};


class Polygon : public ClosedPolygonalChain {
public:
    Polygon(int n = 0, Point* arr = nullptr);

    float area() const;

    ~Polygon();
};

class Triangle : public Polygon {

friend float length(Point* first, Point* second);
public:
    Triangle(int n = 0, Point* arr = nullptr);

    bool hasRightAngle() const;

    ~Triangle();
};


class Trapezoid : public Polygon {

friend float length(Point* first, Point* second);

public:
    Trapezoid(int n = 0, Point* arr = nullptr);

    float height() const;

    ~Trapezoid();

};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(int n = 0, Point* arr = nullptr);

    ~RegularPolygon();
};


#endif