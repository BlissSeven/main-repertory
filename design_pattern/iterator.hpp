#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iostream>
using namespace std;

template<typename T>
class iterator{
public:
    virtual void first()=0;
    virtual void next()=0;
    virtual bool iddone() const=0;
    virtual T& current()=0;
};

template<typename T>
class mycollection{
public:
    iterator<T> getiterator(){}

};
template <typename T>
class collectioniterator:public iterator <T>{
    mycollection<T> mc;
public:
    collectioniterator(const mycollection<T>&c)
        :mc(c){}
    void first ()override{

    }
    void next() override{

    }
    bool isdone() const override{

    }
    T& current() override{

    }

};
void myalgorithm()
{
    mycollection<int> mc;
    iterator <int> iter=mc.getiterator();
    for(iter.first();iter.isdone();iter.next())
    {
        cout<<iter.current()<<endl;
    }
}
#endif // ITERATOR_HPP
