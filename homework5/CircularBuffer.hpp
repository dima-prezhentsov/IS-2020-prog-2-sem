#ifndef LABA5_CIRCULARBUFFER_HPP
#define LABA5_CIRCULARBUFFER_HPP
#include <iostream>

//fixed warnings
template<class T>
class CircularBuffer {
private:
    int n;
    T* data;
    T* beginOfBuffer;
    T* endOfBuffer;
    T* ptrFirst = nullptr;
    T* ptrLast = nullptr;
    int count = 0;
public:
    class Iterator;
    explicit CircularBuffer(int n_) : n(n_)
    {
        data = new T[n + 1];
        beginOfBuffer = &data[0];
        endOfBuffer = &data[n];
    }

    class Iterator {
    private:
        T* ptr;
        T* beginBuf;
        T* endBuf;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = int;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(T* ptr_, T* beginBuf_, T* endBuf_) :
                ptr(ptr_),
                beginBuf(beginBuf_),
                endBuf(endBuf_)
        {}

        Iterator() = default;

        Iterator(const Iterator&) = default;

        Iterator& operator=(const Iterator& other) {
            auto tmp = other.ptr;
            this->ptr = tmp;
            return *this;
        }

        Iterator& operator++() {
            if (ptr == endBuf)
                ptr = beginBuf;
            else ++ptr;
            return *this;
        }

        const Iterator operator++(int) {
            auto old = *this;
            ++(*this);
            return old;
        }

        Iterator& operator--() {
            if (ptr == beginBuf)
                ptr = endBuf;
            else --ptr;
            return *this;
        }

        const Iterator operator--(int) {
            auto old = *this;
            --(*this);
            return old;
        }

        reference operator*() {
            return *ptr;
        }

        Iterator& operator+=(difference_type value) {
            if (value == 0) {
                return *this;
            }
            int k = 0;
            while (k < value) {
                if (ptr == endBuf)
                    ptr = beginBuf;
                else ++ptr;
                ++k;
            }
            return *this;
        }

        Iterator& operator-=(difference_type value) {
            if (value == 0) {
                return *this;
            }
            int k = 0;
            while (k < value) {
                if (ptr == beginBuf)
                    ptr = endBuf;
                else --ptr;
                ++k;
            }
            return *this;
        }

        friend Iterator operator+(Iterator it, Iterator::difference_type value) {
            it += value;
            return it;
        }

        friend Iterator operator+(Iterator::difference_type value, Iterator it) {
            return it + value;
        }

        friend Iterator operator-(Iterator it, Iterator::difference_type value) {
            it -= value;
            return it;
        }

        friend Iterator::difference_type operator-(const Iterator& leftIt, const Iterator& rightIt) {
            int k = 0;
            auto tmp = leftIt;
            while (tmp != rightIt) {
                --tmp;
                ++k;
            }
            return k;
        }


        friend bool operator<(const Iterator& leftIt, const Iterator& rightIt) {
            return leftIt.ptr < rightIt.ptr;
        }
        friend bool operator>(const Iterator& leftIt, const Iterator& rightIt) {
            return leftIt.ptr > rightIt.ptr;
        }
        friend bool operator<=(const Iterator& leftIt, const Iterator& rightIt) {
            return !(leftIt > rightIt);
        }
        friend bool operator>=(const Iterator& leftIt, const Iterator& rightIt) {
            return !(leftIt < rightIt);
        }
        friend bool operator==(const Iterator& leftIt, const Iterator& rightIt) {
            return leftIt.ptr == rightIt.ptr;
        }
        friend bool operator!=(const Iterator& leftIt, const Iterator& rightIt) {
            return !(leftIt == rightIt);
        }
    };

    void addFirst(T value) {
        if (count == 0) {
            ptrFirst = beginOfBuffer;
            *ptrFirst = value;
            ptrLast = &(*(++Iterator(beginOfBuffer, beginOfBuffer, endOfBuffer)));
        }
        else {
            auto tmp = Iterator(ptrFirst, beginOfBuffer, endOfBuffer);
            --tmp;
            *tmp = value;
            ptrFirst = &(*tmp);
            if (ptrFirst == ptrLast) {
                ptrLast = &(*(--Iterator(ptrLast, beginOfBuffer, endOfBuffer)));
            }
        }
        if (count != n) {
            ++count;
        }
    }

    void addLast(T value) {
        if (count == 0) {
            ptrFirst = beginOfBuffer;
            *ptrLast = value;
            ptrLast = &(*(++Iterator(beginOfBuffer, beginOfBuffer, endOfBuffer)));
        }
        else {
            *ptrLast = value;
            ptrLast = &(*(++Iterator(ptrLast, beginOfBuffer, endOfBuffer)));
            if (ptrLast == ptrFirst) {
                ptrFirst = &(*(++Iterator(ptrFirst, beginOfBuffer, endOfBuffer)));
            }
        }
        if (count != n) {
            ++count;
        }
    }

    void delFirst() {
        if (count == 0)
            throw std::out_of_range("Buffer is empty!");
        else {
            if (ptrFirst == ptrLast) {
                ptrFirst = &(*(++Iterator(ptrFirst, beginOfBuffer, endOfBuffer)));
                ptrLast = &(*(++Iterator(ptrFirst, beginOfBuffer, endOfBuffer)));
            }
            else
                ptrFirst = &(*(++Iterator(ptrFirst, beginOfBuffer, endOfBuffer)));
            --count;
        }
    }

    void delLast() {
        if (count == 0)
            throw std::out_of_range("Buffer is empty!");
        else {
            if (ptrLast == ptrFirst) {
                ptrLast = &(*(--Iterator(ptrLast, beginOfBuffer, endOfBuffer)));
                ptrFirst = ptrLast;
            }
            else
                ptrLast = &(*(--Iterator(ptrLast, beginOfBuffer, endOfBuffer)));
            --count;
        }
    }

    void changeCapacity(int newN) {
        T* copyData = new T[newN + 1];
        int k = 0;
        for (auto it = this->begin(); it != this->end(); ++it) {
            copyData[k] = *it;
            ++k;
        }
        delete [] data;
        data = copyData;
        ptrFirst = copyData;
        ptrLast = copyData + k;
        n = newN;
        beginOfBuffer = &data[0];
        endOfBuffer = &data[n];
    }

    //fixed information about size and index in exception
    T& operator[](int ind) {
        if (ind < 0 or ind >= count) {
            throw std::out_of_range("Element " + std::to_string(ind + 1) + " not available there are " + std::to_string(count) + " elements in buffer");
        }
        return *(Iterator(ptrFirst, beginOfBuffer, endOfBuffer) + ind);
    }

    T& operator[](int ind) const {
        if (ind < 0 or ind >= count) {
            throw std::out_of_range("Element " + std::to_string(ind + 1) + " not available there are " + std::to_string(count) + " elements in buffer");
        }
        return *(Iterator(ptrFirst, beginOfBuffer, endOfBuffer) + ind);
    }

    T first() const {
        if (count != 0) {
            return *ptrFirst;
        }
        //fixed throw normal exception not string
        throw std::out_of_range("Buffer is empty");
    }


    T last() const {
        if (count != 0) {
            return *(--Iterator(ptrLast, beginOfBuffer, endOfBuffer));
        }
        throw std::out_of_range("Buffer is empty");
    }
    Iterator begin() const {
        return Iterator(ptrFirst, beginOfBuffer, endOfBuffer);
    }

    Iterator end() const {
        return Iterator(ptrLast, beginOfBuffer, endOfBuffer);
    }

    ~CircularBuffer() {
        delete[] data;
    }

};



#endif //LABA5_CIRCULARBUFFER_HPP