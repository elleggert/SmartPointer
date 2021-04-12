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

    SmartPointer& operator=(SmartPointer const& other){
        //CHECK FOR SELF ASSIGNMENT
        delete this->heapObject;
        this->heapObject = other.heapObject;
        this->refCount = other.refCount;
        *(this->refCount)++;

    }

    virtual ~SmartPointer() {
        *refCount--;
        if ((*refCount) <= 0) {
            delete heapObject;
            delete refCount;
        }
    }
};

