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

class PolygonalChain: public Point {
protected:
    int n;
    Point* points;
public:
    explicit PolygonalChain(int n = 0, Point* arr = nullptr);

    Point getPoint(int i) const;
    
    int getN() const;

    virtual double perimeter() const;

    ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    explicit ClosedPolygonalChain(int n = 0, Point* arr = nullptr) : PolygonalChain(n, arr) {};

    double perimeter() const;

    ~ClosedPolygonalChain() = default;;
};


class Polygon : public ClosedPolygonalChain {
public:
    explicit Polygon(int n = 0, Point* arr = nullptr) : ClosedPolygonalChain(n, arr) {};

    virtual double area() const;

    ~Polygon() = default;;
};

class Triangle : public Polygon {

public:
    explicit Triangle(int n = 0, Point* arr = nullptr) : Polygon(n, arr) {};

    bool hasRightAngle() const;

    ~Triangle() = default;;
};


class Trapezoid : public Polygon {
public:
    explicit Trapezoid(int n = 0, Point* arr = nullptr) : Polygon(n, arr) {};

    explicit Trapezoid(const Trapezoid &tr);

    float length(const Point &first, const Point &second) const;

    float height() const;

    ~Trapezoid() = default;;

};

class RegularPolygon : public Polygon {
public:
    explicit RegularPolygon(int n = 0, Point* arr = nullptr) : Polygon(n, arr) {};

    double perimeter() const;

    double area() const;

    ~RegularPolygon() = default;;
};


#endif