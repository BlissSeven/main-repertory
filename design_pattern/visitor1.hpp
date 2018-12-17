#ifndef VISITOR1_HPP
#define VISITOR1_HPP
#include <iostream>
using namespace std;


class Element{
public:
    virtual void Func1()=0;
    virtual void Func2(int data)=0;
    virtual void Func3(int data)=0;

    virtual ~Element(){}
};
class ElementA:public Element
{
public:
    void Func1()override {

    }
    void Func2(int data){

    }
};
class ElementB:public Element
{
public:
    void Func1()override {

    }
    void Func2(int data){

    }
};
#endif // VISITOR1_HPP
