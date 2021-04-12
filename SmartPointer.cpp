//
// Created by Edgar Eggert on 12.04.21.
//


template<typename T>
class SmartPointer {
public:
    SmartPointer(T* heapObject) : heapObject(heapObject){
        refCount = new int;
        *refCount = 1;
    }

private:
    T* heapObject;
    int* refCount;
};
