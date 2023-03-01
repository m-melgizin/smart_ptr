#include <iostream>

#include "smart_ptr.h"

class A
{
protected:

    int m_a;

public:

    A(int a = 0) : m_a(a) {}

    ~A() { m_a = 0; }

    virtual void add(int other) { m_a += other; }

    virtual void print() { std::cout << "A::print(): " << m_a << std::endl; }

};

class B : public A
{
private:

    float m_b;

public:

    B(int a = 0, float b = 0.0f) : m_b(b) { A::m_a = a; }

    ~B() { m_a = 0; m_b = 0.0f; }

    void add(int other) override { m_a += other; m_b += (float)other; }

    void print() override { std::cout << "B::print(): " << m_a << " " << m_b << std::endl; }

};

int main(int argc, char* argv[]) try
{
    smart_ptr<A> p1(new A(42));
    smart_ptr<A> p2(new B(5, 69.0f));

    p1->print();
    p2->print();

    p1->add(5);
    p2->add(5);

    p1.get()->print();
    p2.get()->print();

    (*p1).print();
    (*p2).print();

    return 0;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << std::endl;
}

/*
==92== Memcheck, a memory error detector
==92== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==92== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==92== Command: ./a.out
==92==
A::print(): 42
B::print(): 5 69
A::print(): 47
B::print(): 10 74
A::print(): 47
B::print(): 10 74
==92==
==92== HEAP SUMMARY:
==92==     in use at exit: 0 bytes in 0 blocks
==92==   total heap usage: 4 allocs, 4 frees, 73,760 bytes allocated
==92==
==92== All heap blocks were freed -- no leaks are possible
==92==
==92== For lists of detected and suppressed errors, rerun with: -s
==92== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
