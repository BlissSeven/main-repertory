#ifndef PROXY_PROXY_HPP
#define PROXY_PROXY_HPP

class ISubject{
public:
    virtual void process();
};

class SubjectProxy:public ISubject{
public:
    virtual void process()
    {
        //对realsubject 的一种间接访问
    }
};
class ClientApp{
    ISubject* subject;
public:
    ClientApp(){
        subject=new SubjectProxy();
    }
    void DoTask(){
        subject->process();
    }
};
#endif // PROXY_PROXY_HPP
