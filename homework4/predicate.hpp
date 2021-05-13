#ifndef LABA4_PREDICATE_HPP
#define LABA4_PREDICATE_HPP
#include <iostream>

using namespace std;

template <class Iterator, class Predicate>
bool allOf(Iterator begin, Iterator end, Predicate predicate) {
    for (Iterator it = begin; it != end; ++it) {
        if (!predicate(*it)) return false;
    }
    return true;
}

template <class Iterator, class Predicate>
bool anyOf(Iterator begin, Iterator end, Predicate predicate) {
    for (Iterator it = begin; it != end; ++it) {
        if (predicate(*it)) return true;
    }
    return false;
}

template <class Iterator, class Predicate>
bool noneOf(Iterator begin, Iterator end, Predicate predicate) {
    return !anyOf(begin, end, predicate);
}

template <class Iterator, class Predicate>
bool oneOf(Iterator begin, Iterator end, Predicate predicate) {
    bool used = false;
    for (Iterator it = begin; it != end; ++it) {
        if (predicate(*it)) {
            if (used) return false;
            used = true;
        }
    }
    return true;
}

template <class Iterator, class Predicate = less<>>
bool isSorted(Iterator begin, Iterator end, Predicate predicate = Predicate()) {
    for (Iterator it = begin; it != end - 1; ++it) {
        if (!predicate(*it, *(it + 1))) return false;
    }
    return true;
}

template <class Iterator, class Predicate>
bool isPartitioned(Iterator begin, Iterator end, Predicate predicate) {
    bool part = predicate(*begin);
    bool used = false;
    for (Iterator it = begin + 1; it != end; ++it) {
        if (predicate(*it) != part) {
            if (used) return false;
            used = true;
            part = !part;
        }
    }
    return true;
}

template <class Iterator, class T>
Iterator findNot(Iterator begin, Iterator end, T element) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it != element) return it;
    }
    return end;
}

template <class Iterator, class T>
Iterator findBackward(Iterator begin, Iterator end, T element) {
    Iterator result = end;
    for (Iterator it = begin; it != end; ++it) {
        if (*it == element) result = it;
    }
    return result;
}

template <class Iterator, class Predicate>
bool isPalindrome(Iterator begin, Iterator end, Predicate predicate) {
    Iterator left = begin;
    Iterator right = --end;
    while (left != right) {
        if (!predicate(*left, *right)) return false;
        if (++left == right) break;
        --right;
    }
    return true;
}





#endif //LABA4_PREDICATE_HPP
