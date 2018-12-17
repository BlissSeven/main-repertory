#ifndef PROXY_CLIENT_HPP
#define PROXY_CLIENT_HPP

class ISubject{
public:
    virtual void process();
    virtual ~ISubject(){}
};
class RealSubject:public ISubject{
public:
    virtual void process(){

    }
};

class ClientApp{
    ISubject* subject;
public:
    ClientApp(){
        subject=new RealSubject();
    }
    void DoTask(){
        //...
        subject->process();
        //..
    }
};
#endif // PROXY_CLIENT_HPP
