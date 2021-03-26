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
public:
    Polynomial();

    Polynomial(int minDegree_, int maxDegree_, int* coefficents_);

    Polynomial(const Polynomial &other);

    string getResult() const;

    int getCoeff(int i) const;

    double get(int value);

    Polynomial &operator=(const Polynomial &other);

    Polynomial &operator+(const Polynomial &other) const;

    Polynomial &operator-(const Polynomial &other) const;

    Polynomial &operator+=(const Polynomial &other);

    Polynomial &operator-=(const Polynomial &other);

    Polynomial &operator*(const Polynomial &b) const;

    Polynomial &operator/(int value) const;

    bool operator==(const Polynomial &second);

    bool operator!=(const Polynomial &second);

    int &operator[](int index);

    int operator[](int index) const;

    Polynomial operator-() const;

    friend stringstream &operator<<(stringstream &stream, const Polynomial& p);

    friend Polynomial &operator*(const Polynomial &other, int value);

    friend Polynomial &operator*(int value, const Polynomial &other);

    friend Polynomial &additition(Polynomial &a, const Polynomial &b, int sign);

    ~Polynomial();


};


#endif
