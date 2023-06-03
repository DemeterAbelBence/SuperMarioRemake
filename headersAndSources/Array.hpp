#pragma once

#include "SDLhandling.hpp"

template<class T>
class Array {

private:
    T* data;
    int size;

public:
    Array() {
        data = nullptr;
        size = 0;
    }
    int getSize() const { return size; }
    bool withinBounds(int index) const {
        if (index < 0 || index >= size)
            return false;

        return true;
    }
    void add(T t) {
        if (size == 0) {
            data = new T[1];
            data[0] = t;
            ++size;
            return;
        }

        T* newData = new T[size + 1];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = t;

        delete[] data;
        data = newData;
        size++;
    }
    void clear() {
        delete[] data;
        size = 0;
    }
    T operator[](int index) const {
        if (index < 0 || index >= size) {
            throw "Index out of bounds for array!";
        }
        else {
            return data[index];
        }
    }
    T get(int index) const {
        if (index < 0 || index >= size) {
            throw "Index out of bounds for array!";
        }
        else {
            return data[index];
        }
    }
    void operator=(const Array<T>& array) {
        int s = array.getSize();

        if (data == nullptr) {
            for (int i = 0; i < s; ++i)
                add(array.get(i));
        }
        else {
            delete[] data;
            size = 0;
            for (int i = 0; i < s; ++i)
                add(array[i]);
        }
    }
    ~Array() {
        delete[] data;
    }
};
