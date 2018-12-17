#ifndef VISITOR2_HPP
#define VISITOR2_HPP

#include <iostream>
using namespace std;
class Visitor;

class Element{
public:

//    virtual void Func1()=0;
//    virtual void Func2(int data)=0;
//    virtual void Func3(int data)=0;

    virtual ~Element(){}

    virtual void accept(Visitor& visitor)=0;
};
class ElementA:public Element
{
public:
    /*
    void Func1()override {

    }
    void Func2(int data){

    }*/
    void accept(Visitor& visitor)override{
        visitor.visitElementA(*this);
    }
};
class ElementB:public Element
{
public:
//    void Func1()override {

//    }
//    void Func2(int data){

//    }
    void accept(Visitor& visitor) override{
        visitor.visitElementB(*this);
    }
};

class Visitor{
public:
    virtual void visitElementA(ElementA& element)=0;
    virtual void visitElementB(ElementA& element)=0;
    virtual ~Visitor(){}
};
// *////////////////////////////////
class Visitor1:public Visitor{
public:
    void visitElementA(ElementA& element)
    {
        cout<<"v1 is processing visitElementA"<<endl;
    }
    void visitElementB(ElementB& element)
    {
        cout<<"v1 is processing  visitElementB"<<endl;
    }
};

class Visitor2:public Visitor{
public:
    void visitElementA(ElementA& element)
    {
        cout<<"v2 is processing visitElementA"<<endl;
    }
    void visitElementB(ElementB& element)
    {
        cout<<"v2 is processing  visitElementB"<<endl;
    }
};


int Visitor_main()
{
    Visitor2 v2;
    ElementB eb;
    eb.accept(v2);

    ElementA ea;
    ea.accept(v2);
    return 0;
}
#endif // VISITOR2_HPP
