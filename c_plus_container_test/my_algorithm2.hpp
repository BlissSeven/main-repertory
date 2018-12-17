#ifndef MY_ALGORITHM2_HPP
#define MY_ALGORITHM2_HPP
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
template<class InputIterator,class T>

T accumulate(InputIterator first,InputIterator last,T init)
{
    for(;first!=last;++first)
        init=init+*first;
    return init;
}
template<class InputIterator,class T,class BinaryOperation>
T accumulate(InputIterator first,InputIterator last,T init
             ,BinaryOperation binary_op)
{
    for(;first!=last;++first)
        init=binary_op(init,*first);
    return  init;
}
int myfunc(int x,int y){return x+2*y;}
struct myclass{
    int operator()(int x,int y){return x+3*y;}
}myobj;
void test_accumulate()
{
    int init=100;
    int nums[]={10,20,30};
    cout<< accumulate(nums,nums+3,init)<<endl;
    cout<<accumulate(nums,nums+3,init,minus<int>())<<endl;
    cout<<accumulate(nums,nums+3,init,myfunc)<<endl;
    cout<<accumulate(nums,nums+3,init,myobj)<<endl;
}

/*******************for_each****************************/
template<class InputIterator,class Function>
Function for_each2(InputIterator first,InputIterator last,
                  Function f)
{
    for(;first!=last;++first)
        f(*first);
    return f;
}
void myfunc2(int i)
{cout<<' '<<i;}
struct myclass2{
    void operator()(int i)
    {cout<<i<<' ';}
}myobj2;
void test_for_each()
{
    vector<int> myvec;
    myvec.push_back(10);
    myvec.push_back(90);
    myvec.push_back(20);
    myvec.push_back(30);
    for_each2(myvec.begin(),myvec.end(),myfunc2);
    for_each2(myvec.begin(),myvec.end(),myobj2);

}
/*****************replace replace_if replace_copy*******/
template<class ForwardIterator,class T>
void replace(ForwardIterator first,ForwardIterator last,
             const T& old_value, const T& new_value)
{
    for(;first!=last;++first)
    {
        if(*first==old_value)
        {
            *first=new_value;
        }
    }
}

template<class ForwardIterator,class Predicate,class T>
void replace_if(ForwardIterator first,ForwardIterator last,Predicate pred,
                const T& new_value)
{
    for(;first!=last;++first)
    {
        if(pred(*first))
            *first=new_value;
    }
}


template<class InputIterator,class OutIterator,class T>
OutIterator replace_copy(InputIterator first,InputIterator last,OutIterator result,
                          const T& old_value,const T& new_value)
{
    for(;first!=last;++first)
    {
        *result=
                *first==old_value? new_value:*first;
    }
    return  result;
}

template<class InputIterator ,class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first,InputIterator last,const T& value)
{
    typename iterator_traits<InputIterator>::difference_type n=0;
    for(;first!=last;++first)
        if(*first ==value)
               ++n;
    return n;
}

#endif // MY_ALGORITHM2_HPP
