//
// Created by Edgar Eggert on 12.04.21.
//


#include <iostream>

template<typename T>
class SmartPointer {
private:
    T* heapObject;
    int* refCount;

    void release() {
        if(heapObject != nullptr) {
            (*refCount)--;
            if(*refCount == 0) {
                delete heapObject;
                delete refCount;
            }
        }
    }

    void copy(const SmartPointer<T>& other) {
        // Copy the pointers to the referenced object and its reference count
        heapObject = other.heapObjecto;
        refCount = other.refCount;

        if(heapObject != nullptr) {
            (*refCount)++;
        }
    }

public:
    SmartPointer() {
        heapObject = nullptr;
        refCount = nullptr;
    }
    SmartPointer(T* heapObject) : heapObject(heapObject){
        refCount = new int(1);
    }

    SmartPointer& operator=(SmartPointer<T>& other){
        if (&other != this){
            release();
            copy(other);
        }
        return *this;
    }

    SmartPointer(SmartPointer<T> & other){
        copy(other);
    }



    int getRefCount() const {
        if (this->refCount != nullptr){
            return *refCount;
        }
        return 0;
    }

    T & operator*() {
        return *(this->heapObject);
    }

    T* operator->(){
        return this->heapObject;
    }

    ~SmartPointer() {
        release();
    }
};

class TestClass1 {
public:
    virtual void print() { std::cout << "TestClass1 at address " << this << '\n'; }
};

class DerivedClass : public TestClass1 {
public:
    virtual void print() { std::cout << "DerivedClass at address " << this << '\n'; }
};

class TestClass2 {
public:
    int number;
    void print() { std::cout << "TestClass2 at address " << this << '\n'; }
};

class PtrLoop {
public:
    int number;
    SmartPointer<PtrLoop> self_ptr;
    void print() { std::cout << "PtrLoop at address " << this << '\n'; }
};