#ifndef LABA2_POLYNOMIAL_H
#define LABA2_POLYNOMIAL_H
#include <iostream>

using namespace std;
class Polynomial {
private:
    int minDegree;
    int maxDegree;
    int* coefficents;
    string result;
    //fixed private method
    friend Polynomial &additition(Polynomial &a, const Polynomial &b, int sign);
public:
    Polynomial();

    Polynomial(int minDegree_, int maxDegree_, int* coefficents_);

    Polynomial(const Polynomial &other);

    double get(int value) const;

    Polynomial &operator=(const Polynomial &other);

    friend Polynomial operator+(const Polynomial &a, const Polynomial &other);

    friend Polynomial operator-(const Polynomial &a, const Polynomial &other);

    friend Polynomial operator*(const Polynomial &a, const Polynomial &b);

    friend Polynomial operator/(const Polynomial &a, int value);

    Polynomial &operator+=(const Polynomial &other);

    Polynomial &operator-=(const Polynomial &other);

    Polynomial &operator/=(int value);

    bool operator==(const Polynomial &second);

    bool operator!=(const Polynomial &second);

    int &operator[](int index);

    int operator[](int index) const;

    Polynomial operator-() const;

    friend stringstream &operator<<(stringstream &stream, const Polynomial& p);

    friend Polynomial &operator*(const Polynomial &other, int value);

    friend Polynomial &operator*(int value, const Polynomial &other);

    ~Polynomial();


};


#endif