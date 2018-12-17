#ifndef MYADAPTER_HPP
#define MYADAPTER_HPP

#include <functional>

/* count_if(vi.begin(),vi.end(),bind2nd(less<int>(),40))*/
/************************binder2nd*************/
template<class Operation>
class binder2nd:public std::unary_function<typename Operation::first_argument_type,
        typename Operation::result_type>
{
protected:
    Operation op;
    typename Operation::second_argument_type value;
public:
    binder2nd(const Operation& x,const typename Operation::second_argument_type& y)
        :op(x),value(y){}
    typename Operation:: result_type
    operator()(const typename Operation::first_argument_type &x)const
    {
        return op(x,value);
    }
};

template<class Operation,class T>
inline binder2nd<Operation> bind2nd(const Operation& op,const T&x)
{
    typedef typename Operation::second_argument_type arg2_type;
    return binder2nd<Operation>(op,arg2_type(x));
}
/***********************not1***********************************************/
template<class Predicate>
class unary_negate:public std::unary_function<Predicate::argument_type,bool>
{
protected:
    Predicate pred;
public:
    explicit unary_negate(const Predicate& x)
        :pred(x){}
    bool operator()(const typename Predicate::argument_type& x)const
    {
        return !pred(x);
    }

};

template<class Predicate>
inline unary_negate<Predicate>not1(const Predicate& pred)
{
    return unary_negate<Predicate>(pred);
}

#endif // MYADAPTER_HPP
