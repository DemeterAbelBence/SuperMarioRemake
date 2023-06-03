#pragma once

#include "SDLhandling.hpp"

template <class T>
class Collection {

private:
    T** data;
    int size;

public:
    Collection() {
        data = nullptr;
        size = 0;
    }
    int getSize() const { return size; }
    void insert(T* p) {
        if (size == 0) {
            size++;
            data = new T * [1];
            data[0] = p;
            return;
        }

        T** newData = new T * [size + 1];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        newData[size] = p;

        delete[] data;
        data = newData;
        size++;
    }
    void insertAsFirst(T* p) {
        if (size == 0) {
            size++;
            data = new T * [1];
            data[0] = p;
            return;
        }

        ++size;
        T** newData = new T * [size];
        newData[0] = p;
        for (int i = 1; i < size; ++i)
            newData[i] = data[i - 1];

        delete[] data;
        data = newData;
    }
    void remove(T* p, bool deletePointer) {
        int index = 0;
        bool exists = false;
        for (int i = 0; i < size; ++i) {
            if (p == data[i]) {
                index = i;
                exists = true;

                if (deletePointer)
                    delete data[index];

                break;
            }
        }

        if (exists) {
            if (size > 1) {
                T** newData = new T * [size - 1];
                for (int i = 0; i < index; ++i)
                    newData[i] = data[i];

                for (int i = index + 1; i < size; ++i)
                    newData[i - 1] = data[i];

                delete[] data;
                data = newData;
                --size;
            }
            else if (size == 1) {


                delete[] data;
                data = nullptr;
                --size;
            }
        }
    }
    T* get(int index) const {
        if (index < 0 || index >= size) {
            throw "Index out of bounds for collection!";
        }
        else {
            return data[index];
        }
    }
    T* operator[](int id) const {
        if (id < 0 || id >= size) {
            throw "Index out of bounds for collection!";
        }
        else {
            return data[id];
        }
    }
    void draw(const SDL::Manager& manager) const {
        for (int i = 0; i < size; ++i)
            data[i]->draw(manager);
    }
    ~Collection() {
        for (int i = 0; i < size; ++i)
            delete data[i];
        
        delete[] data;
    }
};