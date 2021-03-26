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
    result = "";
    //todo not here
    stringstream tmp;
    tmp.str("");
    for (int i = 0; i < maxDegree - minDegree + 1; ++i) {
        coefficents[i] = coefficents_[i];
    }
    int currentDegree = maxDegree;
    for (int i = maxDegree - minDegree; i >= 0; --i) {
        if (i == maxDegree - minDegree) {
            if (coefficents[i] != 0) {
                if (coefficents[i] == 1 or coefficents[i] == -1) {
                    if (currentDegree != 0) {
                        if (coefficents[i] == 1) {
                            if (currentDegree != 1) {
                                tmp << "x^" << currentDegree;
                            }
                            else {
                                tmp << "x";
                            }
                        }
                        else {
                            if (currentDegree != 1) {
                                tmp << "-x^" << currentDegree;
                            }
                            else {
                                tmp << "-x";
                            }
                        }
                    }
                    else {
                        tmp << coefficents[i];
                    }
                }

                else {
                    if (currentDegree != 0) {
                        if (currentDegree != 1) {
                            tmp << coefficents[i] << "x^" << currentDegree;
                        }
                        else {
                            tmp << coefficents[i] << "x";
                        }
                    }
                    else {
                        tmp << coefficents[i];
                    }
                }
            }
        }
        else {
            if (coefficents[i] != 0) {
                if (tmp.str().empty()) {
                    if (currentDegree != 0) {
                        if (coefficents[i] != 1) {
                            if (currentDegree != 1) {
                                tmp << coefficents[i] << "x^" << currentDegree;
                            }
                            else {
                                tmp << coefficents[i] << "x";
                            }
                        }
                        else {
                            if (currentDegree != 1) {
                                tmp << "x^" << currentDegree;
                            }
                            else {
                                tmp << "x";
                            }
                        }
                    }
                    else {
                        tmp << coefficents[i];
                    }
                }
                else {
                    if (coefficents[i] > 0) {
                        if (currentDegree != 0) {
                            if (coefficents[i] != 1) {
                                if (currentDegree != 1) {
                                    tmp << "+" << coefficents[i] << "x^" << currentDegree;
                                }
                                else {
                                    tmp << "+" << coefficents[i] << "x";
                                }
                            }
                            else {
                                if (currentDegree != 1) {
                                    tmp << "+" << "x^" << currentDegree;
                                }
                                else {
                                    tmp << "+" << "x";
                                }
                            }
                        }
                        else {
                            tmp << "+" << coefficents[i];
                        }
                    }
                    else {
                        if (currentDegree != 0) {
                            if (coefficents[i] != 1) {
                                if (currentDegree != 1) {
                                    tmp << coefficents[i] << "x^" << currentDegree;
                                }
                                else {
                                    tmp << coefficents[i] << "x";
                                }
                            }
                            else {
                                if (currentDegree != 1) {
                                    tmp << "x^" << currentDegree;
                                }
                                else {
                                    tmp << "x";
                                }
                            }
                        }
                        else {
                            tmp << coefficents[i];
                        }
                    }
                }
            }
        }
        --currentDegree;
    }
    if (tmp.str().empty()) {
        result = "0";
        coefficents = nullptr;
    }
    else {
        tmp >> result;
    }
    tmp.str("");

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

string Polynomial::getResult() const {
    return this->result;
}

int Polynomial::getCoeff(int i) const {
    return coefficents[i - minDegree];
}

//todo O(n)
double Polynomial::get(int value) {
    double sum = 0;
    int currentDegree = minDegree;
    for (int i = 0; i < maxDegree - minDegree + 1; ++i) {
        sum += coefficents[i] * pow(value, currentDegree);
        ++currentDegree;
    }

    return sum;
}


Polynomial &Polynomial::operator=(const Polynomial &p) {
    this->result = p.result;
    this->minDegree = p.minDegree;
    this->maxDegree = p.maxDegree;
    //todo memory-leak with old coefficents
    this->coefficents = new int[this->maxDegree - this->minDegree + 1];
    for (int i = 0; i < this->maxDegree - this->minDegree + 1; ++i) {
        this->coefficents[i] = p.coefficents[i];
    }
    return *this;
}

Polynomial &Polynomial::operator/(int value) const {
    if (coefficents == nullptr) {
        const auto result = new Polynomial();
        return *result;
    }
    int newN = maxDegree - minDegree + 1;
    int *newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] = coefficents[i];
    }
    for (int i = 0; i < newN; ++i) {
        newCoeff[i] /= value;
    }
    //todo without pointers
    const auto result = new Polynomial(minDegree, maxDegree, newCoeff);
    return *result;
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
        //todo memory-leak once again
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
        coefficents = newCoeff;
        maxDegree = index;
        return coefficents[newN - 1];
    }
}

Polynomial Polynomial::operator-() const {
    for (int i = 0; i < maxDegree - minDegree + 1; ++i) {
        coefficents[i] *= -1;
    }
    return *this;
}

stringstream &operator<<(stringstream &stream, const Polynomial &p) {
    stream << p.getResult();
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

Polynomial &Polynomial::operator+(const Polynomial &b) const {
    Polynomial c(*this);
    return c += b;
}

Polynomial &Polynomial::operator-(const Polynomial &b) const {
    Polynomial c(*this);
    return c -= b;
}

Polynomial &Polynomial::operator*(const Polynomial &other) const {
    if (maxDegree == 0 and minDegree == 0 and (coefficents == nullptr or coefficents[0] == 0)) {
        return const_cast<Polynomial &>(*this);
    }
    if (other.maxDegree == 0 and other.minDegree == 0 and (other.coefficents == nullptr or other.coefficents[0] == 0)) {
        return const_cast<Polynomial &>(other);
    }
    int newN = maxDegree + other.maxDegree - (minDegree + other.minDegree) + 1;
    int *newCoeff = new int[newN];
    for (int i = 0; i < newN; ++i) newCoeff[i] = 0;
    int n1 = maxDegree - minDegree + 1;
    int n2 = other.maxDegree - other.minDegree + 1;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            newCoeff[i + j] += coefficents[i] * other.coefficents[j];
        }
    }
    auto res = new Polynomial(minDegree + other.minDegree, maxDegree + other.maxDegree, newCoeff);
    return *res;

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
    const auto result = new Polynomial(other.minDegree, other.maxDegree, newCoeff);
    return *result;
}



Polynomial::~Polynomial() {
    delete[] coefficents;
}





