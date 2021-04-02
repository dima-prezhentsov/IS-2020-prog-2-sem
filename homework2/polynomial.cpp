#include "polynomial.h"
#include <sstream>
#include <cmath>

using namespace std;

Polynomial::Polynomial() {
    minDegree = 0;
    maxDegree = 0;
    coefficents = nullptr;
    result = "0";
}

Polynomial::Polynomial(int minDegree_, int maxDegree_, int *coefficents_) {
    minDegree = minDegree_;
    maxDegree = maxDegree_;
    coefficents = new int[maxDegree - minDegree + 1];
    for (int i = 0; i < maxDegree - minDegree + 1; ++i) {
        coefficents[i] = coefficents_[i];
    }
}

Polynomial::Polynomial(const Polynomial &other) {
    if (other.coefficents == nullptr) {
        this->result = other.result;
        this->minDegree = other.minDegree;
        this->maxDegree = other.maxDegree;
        this->coefficents = other.coefficents;
    }
    else {
        this->result = other.result;
        this->minDegree = other.minDegree;
        this->maxDegree = other.maxDegree;
        this->coefficents = new int[this->maxDegree - this->minDegree + 1];
        for (int i = 0; i < this->maxDegree - this->minDegree + 1; ++i) {
            this->coefficents[i] = other.coefficents[i];
        }
    }


}


double Polynomial::get(int x0) const{
    double res = 0;
    int n = maxDegree - minDegree + 1;
    int j = 0;
    double number;
    if (minDegree < 0) {
        j = -minDegree;
        double x_ = 1.0 / x0;
        number = 1.0 / x0;
        for (int i = j - 1; i >= 0; i--) {
            res += x_ * coefficents[i];
            x_ *= number;
        }
    }
    number = x0;
    x0 = 1;
    for (int i = j; i < n; ++i) {
        res += x0 * coefficents[i];
        x0 *= number;
    }
    return res;
}


Polynomial &Polynomial::operator=(const Polynomial &p) {
    this->result = p.result;
    this->minDegree = p.minDegree;
    this->maxDegree = p.maxDegree;
    delete [] coefficents;
    this->coefficents = new int[this->maxDegree - this->minDegree + 1];
    for (int i = 0; i < this->maxDegree - this->minDegree + 1; ++i) {
        this->coefficents[i] = p.coefficents[i];
    }
    return *this;
}


int Polynomial::operator[](int index) const {
    if (index > maxDegree or index < minDegree) {
        return 0;
    }
    return coefficents[index - minDegree];
}


int &Polynomial::operator[](int index) {
    if (index <= maxDegree and index >= minDegree) {
        return coefficents[index - minDegree];
    }
    else if (index < minDegree) {
        int newN = maxDegree - index + 1;
        int* newCoeff = new int[newN];
        for (int i = 0; i < minDegree - index; ++i) {
            newCoeff[i] = 0;
        }
        int j = 0;
        for (int i = minDegree - index; i < newN; ++i) {
            newCoeff[i] = coefficents[j];
            ++j;
        }
        delete [] coefficents;
        coefficents = newCoeff;
        minDegree = index;
        return coefficents[0];
    }
    else {
        int newN = index - minDegree + 1;
        int* newCoeff = new int[newN];
        for (int i = 0; i < maxDegree - minDegree + 1; ++i) {
            newCoeff[i] = coefficents[i];
        }
        for (int i = maxDegree - minDegree + 1; i < newN; ++i) {
            newCoeff[i] = 0;
        }
        delete [] coefficents;
        coefficents = newCoeff;
        maxDegree = index;
        return coefficents[newN - 1];
    }
}

Polynomial Polynomial::operator-() const {
    int* newCoeff = new int[maxDegree - minDegree + 1];
    for (int i = 0; i < maxDegree - minDegree + 1; ++i) {
        newCoeff[i] = coefficents[i] * -1;
    }
    return Polynomial(minDegree, maxDegree, newCoeff);
}

stringstream &operator<<(stringstream &stream, const Polynomial &p) {
    int currentDegree = p.maxDegree;
    if (p.coefficents == nullptr) {
        stream << "0";
        return stream;
    }
    for (int i = p.maxDegree - p.minDegree; i >= 0; --i) {
        if (i == p.maxDegree - p.minDegree) {
            if (p.coefficents[i] != 0) {
                if (p.coefficents[i] == 1 or p.coefficents[i] == -1) {
                    if (currentDegree != 0) {
                        if (p.coefficents[i] == 1) {
                            if (currentDegree != 1) {
                                stream << "x^" << currentDegree;
                            }
                            else {
                                stream << "x";
                            }
                        }
                        else {
                            if (currentDegree != 1) {
                                stream << "-x^" << currentDegree;
                            }
                            else {
                                stream << "-x";
                            }
                        }
                    }
                    else {
                        stream << p.coefficents[i];
                    }
                }

                else {
                    if (currentDegree != 0) {
                        if (currentDegree != 1) {
                            stream << p.coefficents[i] << "x^" << currentDegree;
                        }
                        else {
                            stream << p.coefficents[i] << "x";
                        }
                    }
                    else {
                        stream << p.coefficents[i];
                    }
                }
            }
        }
        else {
            if (p.coefficents[i] != 0) {
                if (stream.str().empty()) {
                    if (currentDegree != 0) {
                        if (p.coefficents[i] != 1) {
                            if (currentDegree != 1) {
                                stream << p.coefficents[i] << "x^" << currentDegree;
                            }
                            else {
                                stream << p.coefficents[i] << "x";
                            }
                        }
                        else {
                            if (currentDegree != 1) {
                                stream << "x^" << currentDegree;
                            }
                            else {
                                stream << "x";
                            }
                        }
                    }
                    else {
                        stream << p.coefficents[i];
                    }
                }
                else {
                    if (p.coefficents[i] > 0) {
                        if (currentDegree != 0) {
                            if (p.coefficents[i] != 1) {
                                if (currentDegree != 1) {
                                    stream << "+" << p.coefficents[i] << "x^" << currentDegree;
                                }
                                else {
                                    stream << "+" << p.coefficents[i] << "x";
                                }
                            }
                            else {
                                if (currentDegree != 1) {
                                    stream << "+" << "x^" << currentDegree;
                                }
                                else {
                                    stream << "+" << "x";
                                }
                            }
                        }
                        else {
                            stream << "+" << p.coefficents[i];
                        }
                    }
                    else {
                        if (currentDegree != 0) {
                            if (p.coefficents[i] != 1) {
                                if (currentDegree != 1) {
                                    stream << p.coefficents[i] << "x^" << currentDegree;
                                }
                                else {
                                    stream << p.coefficents[i] << "x";
                                }
                            }
                            else {
                                if (currentDegree != 1) {
                                    stream << "x^" << currentDegree;
                                }
                                else {
                                    stream << "x";
                                }
                            }
                        }
                        else {
                            stream << p.coefficents[i];
                        }
                    }
                }
            }
        }
        --currentDegree;
    }
    if (stream.str().empty()) {
        stream << "0";
    }
    return stream;
}

bool Polynomial::operator==(const Polynomial &second) {
    if (coefficents == nullptr and second.coefficents != nullptr) {
        return false;
    }
    else if (coefficents != nullptr and second.coefficents == nullptr) {
        return false;
    }
    else if (coefficents == nullptr and second.coefficents == nullptr) {
        return true;
    }
    int n = min(maxDegree - minDegree + 1, second.maxDegree - second.minDegree + 1);
    int f_ind = 0;
    int s_ind = 0;
    while (f_ind < n and s_ind < n) {
        if (coefficents[f_ind] == 0 and second.coefficents[s_ind] == 0) {
            ++f_ind;
            ++s_ind;
        }
        else if (coefficents[f_ind] == 0) {
            if (minDegree + f_ind != second.minDegree + s_ind) {
                ++f_ind;
            }
            else {
                return false;
            }
        }
        else if (second.coefficents[s_ind] == 0) {
            if (minDegree + f_ind != second.minDegree + s_ind) {
                ++s_ind;
            }
            else {
                return false;
            }
        }
        else {
            if (coefficents[f_ind] == second.coefficents[s_ind] and minDegree + f_ind == second.minDegree + s_ind) {
                ++f_ind;
                ++s_ind;
            }
            else if (coefficents[f_ind] != second.coefficents[s_ind] and minDegree + f_ind == second.minDegree + s_ind) {
                return false;
            }
            else if (minDegree + f_ind != second.minDegree + s_ind) {
                return false;
            }
        }
    }
    return true;
}


bool Polynomial::operator!=(const Polynomial &second) {
    return not(*this == second);
}

Polynomial &additition(Polynomial &a, const Polynomial &b, int sign) {
    if (a.coefficents == nullptr) {
        return const_cast<Polynomial &>(b);
    }
    if (b.coefficents == nullptr) {
        return a;
    }
    int n = a.maxDegree - a.minDegree + 1;
    if (a.maxDegree == b.maxDegree and a.minDegree == b.minDegree) {
        for (int i = 0; i < n; ++i) {
            a.coefficents[i] = a.coefficents[i] + sign * b.coefficents[i];
        }
        return a;
    }
    int newN = max(a.maxDegree, b.maxDegree) - min(a.minDegree, b.minDegree) + 1;
    int* newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] = 0;
    }
    if (a.minDegree <= b.minDegree) {
        for (int i = 0; i < n; ++i) {
            newCoeff[i] = a.coefficents[i];
        }
        for (int i = b.minDegree - a.minDegree; i < newN; ++i) {
            newCoeff[i] = newCoeff[i] + sign * b.coefficents[i - (b.minDegree - a.minDegree)];
        }
    }
    else {
        n = b.maxDegree - b.minDegree + 1;
        for (int i = 0; i < n; ++i) {
            newCoeff[i] = b.coefficents[i];
        }
        for (int i = a.minDegree - b.minDegree; i < newN; ++i) {
            newCoeff[i] = newCoeff[i] + sign * a.coefficents[i - (a.minDegree - b.minDegree)];
        }
    }
    a.minDegree = min(a.minDegree, b.minDegree);
    a.maxDegree = max(a.maxDegree, b.maxDegree);
    delete[] a.coefficents;
    a.coefficents = newCoeff;
    return a;
}

Polynomial &Polynomial::operator+=(const Polynomial &other) {
    return additition(*this, other, 1);

}

Polynomial &Polynomial::operator-=(const Polynomial &other) {
    return additition(*this, other, -1);
}

Polynomial &Polynomial::operator/=(int value) {
    if (coefficents == nullptr) {
        minDegree = 0;
        maxDegree = 0;
        delete [] coefficents;
        coefficents = nullptr;
        return *this;
    }
    int newN = maxDegree - minDegree + 1;
    //todo why do you need new array?Oo
    int *newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] = coefficents[i];
    }
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] /= value;
    }
    delete [] coefficents;
    coefficents = newCoeff;
    return *this;
}

Polynomial operator+(const Polynomial &a, const Polynomial &b) {
    Polynomial c(a);
    return c += b;
}

Polynomial operator-(const Polynomial &a, const Polynomial &b) {
    Polynomial c(a);
    return c -= b;
}

Polynomial operator/(const Polynomial &a, int value) {
    Polynomial c(a);
    return c /= value;
}

Polynomial operator*(const Polynomial &a, const Polynomial &other) {
    if (a.maxDegree == 0 and a.minDegree == 0 and (a.coefficents == nullptr or a.coefficents[0] == 0)) {
        return const_cast<Polynomial &>(a);
    }
    if (other.maxDegree == 0 and other.minDegree == 0 and (other.coefficents == nullptr or other.coefficents[0] == 0)) {
        return const_cast<Polynomial &>(other);
    }
    int newN = a.maxDegree + other.maxDegree - (a.minDegree + other.minDegree) + 1;
    int *newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) newCoeff[i] = 0;
    int n1 = a.maxDegree - a.minDegree + 1;
    int n2 = other.maxDegree - other.minDegree + 1;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            newCoeff[i + j] += a.coefficents[i] * other.coefficents[j];
        }
    }
    auto res = Polynomial(a.minDegree + other.minDegree, a.maxDegree + other.maxDegree, newCoeff);
    return res;

}

Polynomial &operator*(const Polynomial &other, int value) {
    if (other.coefficents == nullptr) {
        const auto result = new Polynomial();
        return *result;
    }
    int newN = other.maxDegree - other.minDegree + 1;
    int *newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] = other.coefficents[i];
    }
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] *= value;
    }
    //todo everywhere pointers
    const auto result = new Polynomial(other.minDegree, other.maxDegree, newCoeff);
    return *result;
}

Polynomial &operator*(int value, const Polynomial &other) {
    if (other.coefficents == nullptr) {
        const auto result = new Polynomial();
        return *result;
    }
    int newN = other.maxDegree - other.minDegree + 1;
    int *newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] = other.coefficents[i];
    }
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] *= value;
    }
    //todo without pointers
    const auto result = new Polynomial(other.minDegree, other.maxDegree, newCoeff);
    return *result;
}



Polynomial::~Polynomial() {
    delete[] coefficents;
}