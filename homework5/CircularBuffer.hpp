#ifndef LABA5_CIRCULARBUFFER_HPP
#define LABA5_CIRCULARBUFFER_HPP
#include <iostream>

using namespace std;

template<class T>
class CircularBuffer {
public:
    class Iterator;
    explicit CircularBuffer(size_t n_)
    {
        n = n_;
        data = new T(n);
        beginOfBuffer = &data[0];
        endOfBuffer = &data[n - 1];
    }
    void get() {
        for (int i = 0; i < count; ++i) {
            cout << *(beginOfBuffer + (ptrFirst - beginOfBuffer + i) % n) << " ";
        }
        cout << endl;
    }

    void addFirst(T value) {
        if (count == 0) {
            ptrFirst = beginOfBuffer;
            ptrLast = beginOfBuffer;
            *ptrFirst = value;
        }
        else {
            if (ptrFirst == beginOfBuffer) {
                ptrFirst = endOfBuffer;
            }
            else --ptrFirst;
            *ptrFirst = value;
        }
        if (count == n) {
            if (ptrLast == beginOfBuffer) {
                ptrLast = endOfBuffer;
            }
            else --ptrLast;
        }
        if (count < n) {
            ++count;
        }
    }

    void addLast(T value) {
        if (count == 0) {
            ptrLast = beginOfBuffer;
            ptrFirst = beginOfBuffer;
            *ptrLast = value;
        }
        else {
            if (ptrLast == endOfBuffer) {
                ptrLast = beginOfBuffer;
            }
            else ++ptrLast;
            *ptrLast = value;
        }
        if (count == n) {
            if (ptrFirst == endOfBuffer) {
                ptrFirst = beginOfBuffer;
            }
            else ++ptrFirst;
        }
        if (count < n) {
            ++count;
        }
    }

    void delFirst() {
        if (ptrFirst == endOfBuffer) {
            ptrFirst = beginOfBuffer;
        }
        else ++ptrFirst;
        --count;
    }

    void delLast() {
        if (ptrLast == beginOfBuffer) {
            ptrLast = endOfBuffer;
        }
        else --ptrLast;
        --count;
    }

    T first() {
        if (count != 0) {
            return *ptrFirst;
        }
        //todo throw normal exception not string
        throw "buffer is empty";
    }

    T last() {
        if (count != 0) {
            return *ptrLast;
        }
        throw "buffer is empty";
    }

    //todo information about size and index in exception
    T operator[](int ind) const {
        if (ind < 0 or ind >= count) {
            throw "index out of range";
        }
        return *(beginOfBuffer + (ptrFirst - beginOfBuffer + ind) % n);
    }

    T& operator[](int ind) {
        return *(beginOfBuffer + (ptrFirst - beginOfBuffer + ind) % n);
    }

    void changeCapacity(size_t newN) {
        T* copyData = new T[newN];
        if (newN < count) {
            for (size_t i = 0; i < newN; ++i) {
                copyData[i] = *(beginOfBuffer + (ptrFirst - beginOfBuffer + i) % n);
            }
            delete [] data;
            this->data = new T[newN];
            for (size_t i = 0; i < newN; ++i) {
                this->data[i] = copyData[i];
            }
            n = newN;
            count = newN;
            ptrFirst = &data[0];
            ptrLast = &data[n - 1];
            beginOfBuffer = &data[0];
            endOfBuffer = &data[n - 1];
        }
        else {
            for (size_t i = 0; i < count; ++i) {
                copyData[i] = *(beginOfBuffer + (ptrFirst - beginOfBuffer + i) % n);
            }
            delete [] data;
            this->data = new T[newN];
            for (size_t i = 0; i < newN; ++i) {
                this->data[i] = copyData[i];
            }
            n = newN;
            ptrFirst = &data[0];
            ptrLast = &data[count - 1];
            beginOfBuffer = &data[0];
            endOfBuffer = &data[n - 1];
        }
    }

    Iterator begin() {
        return Iterator(ptrFirst, beginOfBuffer, endOfBuffer, n, count, ptrFirst, ptrLast);
    }
    Iterator end() {
        return Iterator(nullptr, beginOfBuffer, endOfBuffer, n, count, ptrFirst, ptrLast);
    }

    ~CircularBuffer() {
        delete[] data;
    }

    class Iterator {
    private:
        T* ptr;
        T* endBuf;
        T* beginBuf;
        size_t size;
        size_t countBuf;
        T* head;
        T* tail;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator() = default;

        Iterator(const Iterator&) = default;

        Iterator& operator=(const Iterator&) = default;

        Iterator(T* ptr_, T* beginBuf_, T* endBuf_, size_t size_, size_t countBuf_, T* head_, T* tail_) :
            ptr(ptr_),
            beginBuf(beginBuf_),
            endBuf(endBuf_),
            size(size_),
            countBuf(countBuf_),
            head(head_),
            tail(tail_)
        {}

        Iterator operator++() {
            if (ptr == nullptr) {
                ptr = head;
                return *this;
            }
            if (ptr == tail) {
                ptr = nullptr;
                return *this;
            }
            if (ptr == endBuf) {
                ptr = beginBuf;
            }
            else ++ptr;
            return *this;
        }

        Iterator operator++(int i) {
            auto old = *this;
            if (ptr == nullptr) {
                ptr = head;
                return old;
            }
            if (ptr == tail) {
                ptr = nullptr;
                return *this;
            }
            if (ptr == endBuf) {
                ptr = beginBuf;
            }
            else ++ptr;
            return old;
        }

        Iterator operator--() {
            if (ptr == nullptr) {
                ptr = tail;
                return *this;
            }
            if (ptr == tail) {
                ptr = nullptr;
                return *this;
            }
            if (ptr == beginBuf) {
                ptr = endBuf;
            }
            else --ptr;
            return *this;
        }

        Iterator operator--(int i) {
            auto old = *this;
            if (ptr == nullptr) {
                ptr = tail;
                return *this;
            }
            if (ptr == tail) {
                ptr = nullptr;
                return *this;
            }
            if (ptr == beginBuf) {
                ptr = endBuf;
            }
            else --ptr;
            return old;
        }

        reference operator[](difference_type ind) {
            if (ind < 0 or ind > size) {
                throw "index out of range";
            }
            return *(beginBuf + (ptr - beginBuf + ind) % size);
        }

        reference operator*() {
            return *ptr;
        }
        Iterator& operator+=(difference_type value) {
            if (ptr == tail) {
                ptr = nullptr;
                return *this;
            }
            ptr = beginBuf + (ptr - beginBuf + value) % size;
            return *this;
        }
        Iterator& operator-=(difference_type value) {
            if (ptr == tail) {
                ptr = nullptr;
                return *this;
            }
            if (ptr - beginBuf - value < 0) {
                ptr = endBuf - (-1 * (ptr - beginBuf - value + 1)) % size;
            }
            else {
                ptr = beginBuf + (ptr - beginBuf - value);
            }
            return *this;
        }

        Iterator operator+(int value) {
            if (beginBuf + (ptr - beginBuf + value) % size == tail) {
                return Iterator(nullptr, beginBuf, endBuf, size, countBuf, head, tail);
            }
            else {
                T* newPtr = beginBuf + (ptr - beginBuf + value) % size;
                return Iterator(newPtr, beginBuf, endBuf, size, countBuf, head, tail);
            }
        }

        bool operator<(const Iterator& other) {
            return this->ptr < other.ptr;
        }
        bool operator>(const Iterator& other) {
            return this->ptr > other.ptr;
        }
        bool operator<=(const Iterator& other) {
            return !(this->ptr > other.ptr);
        }
        bool operator>=(const Iterator& other) {
            return !(this->ptr < other.ptr);
        }
        bool operator==(const Iterator& other) {
            return this->ptr == other.ptr;
        }
        bool operator!=(const Iterator& other) {
            return !(this->ptr == other.ptr);
        }




    };

private:
    size_t n;
    T* data = nullptr;
    T* beginOfBuffer;
    T* endOfBuffer;
    T* ptrFirst = nullptr;
    T* ptrLast = nullptr;
    size_t count = 0;

};



#endif //LABA5_CIRCULARBUFFER_HPP
