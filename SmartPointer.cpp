//
// Created by Edgar Eggert on 12.04.21.
//


template<typename T>
class SmartPointer {
private:
    T* heapObject;
    int* refCount;
};
