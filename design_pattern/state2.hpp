#ifndef STATE2_HPP
#define STATE2_HPP

class NetworkState
{
public:
    NetworkState* pnext;
    virtual void operation1()=0;
     virtual void operation2()=0;
     virtual void operation3()=0;
    virtual ~NetworkState(){}
};
class openstate:public NetworkState{
    static NetworkState* m_instance;
public:
    static NetworkState* getinstance(){
        if(m_instance==nullptr)
        {
            m_instance=new openstate();
        }
        return m_instance;
    }
    void operation1(){
        //
        pnext=closestate::getinstance();
    }
    void operation2(){
        //
        pnext=connectstate::getinstance();
    }
    void operation3(){
        //
        pnext=openstate::getinstance();
    }
};

class closestate:public NetworkState{
    static NetworkState* m_instance;
public:
    static NetworkState* getinstance(){
        if(m_instance==nullptr)
        {
            m_instance=new openstate();
        }
        return m_instance;
    }
    void operation1(){
        //
        pnext=closestate::getinstance();
    }
    void operation2(){
        //
        pnext=connectstate::getinstance();
    }
    void operation3(){
        //
        pnext=openstate::getinstance();
    }
};


class connectstate:public NetworkState{
    static NetworkState* m_instance;
public:
    static NetworkState* getinstance(){
        if(m_instance==nullptr)
        {
            m_instance=new openstate();
        }
        return m_instance;
    }
    void operation1(){
        //
        pnext=closestate::getinstance();
    }
    void operation2(){
        //
        pnext=connectstate::getinstance();
    }
    void operation3(){
        //
        pnext=openstate::getinstance();
    }
};

class networkprocessor{
    NetworkState* pstate;
public:
    networkprocessor(NetworkState* pstate)
    {
        this->pstate=pstate;
    }
    void operation1(){
        pstate->operation1();
        pstate=pstate->pnext;
    }
    void operation2(){
        pstate->operation2();
        pstate=pstate->pnext;
    }
    void operation3(){
        pstate->operation3();
        pstate=pstate->pnext;
    }
};
#endif // STATE2_HPP
