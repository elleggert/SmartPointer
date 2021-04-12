//
// Created by Edgar Eggert on 12.04.21.
//


template<typename T>
class SmartPointer {
private:
    T* heapObject;
    int* refCount;
public:
    SmartPointer(T* heapObject) : heapObject(heapObject){
        refCount = new int;
        *refCount = 1;
    }

    virtual ~SmartPointer() {
        *refCount--;
        if ((*refCount) <= 0) {
            delete heapObject;
            delete refCount;
        }
    }
};

