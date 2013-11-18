#include <iostream>
#include <memory>
#include "make_unique.h"

using namespace std;

struct A {
    A ()
    {
    }
    virtual ~A () {}
    virtual auto doSomething() -> void
    {
        cout << "Hello from A" << endl;
    }

};

struct B : public A {
    B()
    {
    }

    virtual ~B()
    {
    }

    virtual auto doSomething() -> void
    {
        cout << "Hello from B" << endl;
    }

};


int main(int argc, const char *argv[])
{
    auto sa = shared_ptr<A>(new A());
    sa->doSomething();
    auto sb = shared_ptr<A>(new B());
    sb->doSomething();
    
    cout << "=======================" << endl;

    auto a = make_shared<A>(A());
    a->doSomething();
    auto b = make_shared<A>(B());
    b->doSomething();
    shared_ptr<A> c = make_shared<B>(B());
    c->doSomething();
    cout << "=======================" << endl;
    auto ua = unique_ptr<A>(new A());
    ua->doSomething();
    auto ub = unique_ptr<A>(new B());
    ub->doSomething();

    cout << "=======================" << endl;

    //But we want make_unique ah.. c++14
    auto u2a = make_unique<A>(A());
    u2a->doSomething();
    auto u2b = make_unique<A>(B());
    u2b->doSomething();
    unique_ptr<A> u2c = make_unique<B>(B());
    u2c->doSomething();

///Output    
//bash-3.2$ g++ -std=c++11 RuntimeShared.cpp
//bash-3.2$ ./a.out
//Hello from A
//Hello from B
//=======================
//Hello from A
//Hello from A
//Hello from B
//=======================
//Hello from A
//Hello from B
//=======================
//Hello from A
//Hello from A
//Hello from B
//
    return 0;
}
