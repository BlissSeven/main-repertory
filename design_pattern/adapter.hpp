#ifndef ADAPTER_HPP
#define ADAPTER_HPP
// 目标接口(新接口)
class ITarget{
public:
    virtual void process()=0;
};
class IAdaptee{
public:
    virtual void foo(int dta)=0;
    virtual int bar()=0;
};

class OldClass:public IAdaptee
{

};
class Adapter2:public ITarget{
protected:
    IAdaptee* padaptee;
public:
    Adapter(IAdaptee* padaptee){
        this->padaptee=padaptee;
    }
    virtual void process(){
        int data=padaptee->bar;
        padaptee->foo(data);
    }
};

class Adapter:public ITarget,protected OldClass
{

};
int main(){
    IAdaptee* padaptee=new OldClass();
    ITarget* ptarget=new Adapter(padaptee);
    ptarget->process();
}
#endif // ADAPTER_HPP
