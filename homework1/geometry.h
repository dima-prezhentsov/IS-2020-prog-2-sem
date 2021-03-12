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
    //fixed operator=
    int getN() const;

    PolygonalChain &operator=(const PolygonalChain &other);

    virtual double perimeter() const;
    //fixed virtual destructor
    virtual ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    explicit ClosedPolygonalChain(int n = 0, Point* arr = nullptr) : PolygonalChain(n, arr) {};

    double perimeter() const;
    //fixed copy constructor
    ClosedPolygonalChain(const ClosedPolygonalChain &other) : PolygonalChain(other.n, other.points) {};
    //fixed operator= default
    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &other) = default;

    ~ClosedPolygonalChain() = default;;
};


class Polygon : public ClosedPolygonalChain {
public:
    explicit Polygon(int n = 0, Point* arr = nullptr) : ClosedPolygonalChain(n, arr) {};

    Polygon(const Polygon &other) : ClosedPolygonalChain(other.n, other.points) {};

    virtual double area() const;

    Polygon &operator=(const Polygon &other) = default;

    ~Polygon() = default;;
};

class Triangle : public Polygon {

public:
    explicit Triangle(int n = 0, Point* arr = nullptr) : Polygon(n, arr) {};

    Triangle(const Triangle &other) : Polygon(other.n, other.points) {};

    bool hasRightAngle() const;

    Triangle &operator=(const Triangle &other) = default;

    ~Triangle() = default;;
};


class Trapezoid : public Polygon {
public:
    explicit Trapezoid(int n = 0, Point* arr = nullptr) : Polygon(n, arr) {};

    Trapezoid(const Trapezoid &tr) : Polygon(tr.n, tr.points) {};

    float length(const Point &first, const Point &second) const;

    float height() const;

    Trapezoid &operator=(const Trapezoid &other) = default;

    ~Trapezoid() = default;;

};

class RegularPolygon : public Polygon {
public:
    explicit RegularPolygon(int n = 0, Point* arr = nullptr) : Polygon(n, arr) {};

    RegularPolygon(const RegularPolygon &other) : Polygon(other.n, other.points) {};

    double perimeter() const;

    double area() const;

    RegularPolygon &operator=(const RegularPolygon &other) = default;

    ~RegularPolygon() = default;;
};


#endif