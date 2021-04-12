#include <iostream>
#include "SmartPointer.cpp"

using std::cout;

int main() {
    SmartPointer<int> sp_int1(new int(5));
    SmartPointer<int> sp_int2 = sp_int1;

    cout << *sp_int1 << '\n';    // Output: 5
    cout << *sp_int2 << '\n';    // Output: 5

    *sp_int1 = 3;

    cout << *sp_int1 << '\n';    // Output: 3
    cout << *sp_int2 << '\n';    // Output: 3

    cout << sp_int1.getRefCount() << '\n';    // Output: 2
    cout << sp_int2.getRefCount() << '\n';    // Output: 2

    // Check the assigning a smart pointer to itself does not increase the
    // reference count
    sp_int1 = sp_int1;
    cout << sp_int1.getRefCount() << '\n';    // Output: 2

    // Smart Pointers also work with object (class) types
    SmartPointer<TestClass1> sp_obj_test1(new TestClass1());
    SmartPointer<TestClass1> sp_obj_test2(new TestClass1());

    sp_obj_test1->print();    // Output: TestClass1 at address 0x4d8590
    sp_obj_test2->print();    // Output: TestClass1 at address 0x4d85b0

    sp_obj_test1 = sp_obj_test2;

    // We can call methods on objects stored in smart pointers
    sp_obj_test1->print();    // Output: TestClass1 at address 0x4d85b0

    // We even have virtual functions behaving correctly
    sp_obj_test1 = new DerivedClass();
    sp_obj_test1->print();    // Output: DerivedClass at address 0x4d85d0

    // Our smart pointers are typesafe
    TestClass1* test3 = new TestClass1();
    TestClass2* test4 = new TestClass2();

    // test3 = test4
    // this gives a compiler error since TestClass1 and TestClass 2 are NOT
    // compatible types

    SmartPointer<TestClass1> sp_test3(test3);
    SmartPointer<TestClass2> sp_test4(test4);

    // This should also give a compiler error: no match for operator=
    // sp_test3 = sp_test4;

    // Now we test that memory is reclaimed
    test4->number = 4;
    cout << "Number: " << test4->number << '\n';
    {
        SmartPointer<TestClass2> sp_test5(test4);
    } // 'last' reference to TestClass2 object goes out of scope here

    // This should give a runtime error or print a different number because the
    // object at this memory address has been freed
    //cout << "Number: " << test4->number << '\n';

    // A handle to a PtrLoop object
    PtrLoop* loop = new PtrLoop();
    loop->number = 8;
    cout << "Number: " << loop->number << '\n';

    /*
     * A new scope block: in here we will create a smart pointer reference to the
     * loop object and make it point to itself so that even when our last reference
     * to the object in the main body of the program is lost the object is not
     * deleted from memory
     */

    {
        // Create the object and reference it by a smart pointer
        SmartPointer<PtrLoop> sp_loop(loop);

        // Make it point to itself
        sp_loop->self_ptr = sp_loop;
    }

    // This does NOT cause a runtime error or prints a different number as the
    // object has not been freed by the smart pointer
    cout << "Number: " << loop->number << '\n';

    return 0;
}
