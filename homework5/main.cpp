#include<iostream>
#include<sstream>
#include<vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <string>
#include <exception>
#include <cassert>
#include "CircularBuffer.hpp"
using namespace std;

stringstream ss;


template <auto& out=cout, typename T>                                                         //function that prints any values with space delimeter
void print(const T& t)                                                                           //and make endl in the end (but it doesn't even matter)
{                                                                                                //e.g print(1, "plus", 2, '=', 3);
    out << t << endl;                                                                            //1 plus 2 = 3
}                                                                                                //use template for another ostream
//e.g. print<cerr>("I am here")
template<auto& out=cout, class T, class... Args>
void print(const T& el, Args... args)
{
    out << el << " ";
    print<out>(args...);
}

#define callAssert(...) assert(assertPrint(__VA_ARGS__))

template<class P, class... Args>
bool assertPrint(const P& pred, Args&&... args) {
    if (!pred(forward<Args>(args)...)) {
        print<cerr>(forward<Args>(args)...);
        return false;
    }
    return true;
}

int main() {
    CircularBuffer<int> c(4);
    c.addFirst(1);
    callAssert(equal_to<>(), c.first(), 1);
    callAssert(equal_to<>(), c.last(), 1);
    c.addLast(2);
    callAssert(equal_to<>(), c.first(), 1);
    callAssert(equal_to<>(), c.last(), 2);
    callAssert(equal_to<>(), c[0], 1);
    callAssert(equal_to<>(), c[1], 2);
    c.delFirst();
    callAssert(equal_to<>(), c[0], 2);
    callAssert(equal_to<>(), c.first(), 2);
    callAssert(equal_to<>(), c.last(), 2);
    c.delLast();
    c.addFirst(1);
    c.addFirst(2);
    c.addFirst(3);
    c.addFirst(4);
    c.get();
    c.addFirst(5);
    c.get();
    c.changeCapacity(5);
    c.addFirst(6);
    c.get();
    
    return 0;
}
