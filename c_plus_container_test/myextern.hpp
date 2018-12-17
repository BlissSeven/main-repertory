#ifndef MYEXTERN_HPP
#define MYEXTERN_HPP
#include <iostream>
#include <functional>
#include <unordered_set>
#include <tuple>
#include <string>
using namespace std;

/*4444444444444444444444444444444444*/
template<typename T>
inline void hash_combine(size_t& seed,const T& val)
{
    seed^=std::hash<T>()(val)+0x9e3779b9+(seed<<6)+(seed>>2);
}
/**3333333333333333333333333333333*/
template<typename T>
inline void hash_val(size_t& seed,const T& val)
{
    hash_combine(seed,val);
}

/**2222222222222222222222222222*/
template <typename T,typename... Types>
inline void hash_val(size_t& seed,const T& val,const Types&... args)
{
    hash_combine(seed,val);
    hash_val(seed,args...);
}
/**11111111111111111111111111111*/
template <typename... Types>
inline size_t hash_val(const Types&... args)
{
    size_t seed=0;
    hash_val(seed,args...);
    return seed;
}

class Customer{
public:
    float fname;
    long lname;
    int no;
public:
    Customer(const float x,const long y,const int z )
        :fname(x),lname(y),no(z){}
};

class CustomerHash
{
public:
    size_t operator()(const Customer& c)const
    {
        return hash_val(c.fname,c.lname,c.no);
    }
};

size_t customer_hash_func(const Customer& c)
{
    return hash_val(c.fname,c.lname,c.no);
}

void test_my_hash()
{
    unordered_set<Customer,CustomerHash> cutset;
    /*函数类型*/
    unordered_set<Customer,size_t(*)(const Customer&)> cutsets;

}
void test_tuple()
{
    tuple<string,int,int> t("str",1,2);
    cout<<"sizeof(tuple<string,int,int>): "<<sizeof(t)<<endl;

    std::cout<<"t: "<<get<0>(t)<<" "<<get<1>(t)<<std::endl;

    auto t2=make_tuple("stacy",22,33);

    t2=t;
    typedef  tuple<string,int,int> TupleType;
    cout<<tuple_size<TupleType >::value <<endl;
}

///*
template <typename... Value> class mytuple;

template<> class mytuple<>{};

template <typename Head,typename... Tail>
class mytuple<Head,Tail...>
:private mytuple<Tail...>{
   typedef tuple<Tail...> inherited;

   public:
   mytuple(){}
   mytuple(Head v,Tail... vtail)
       : m_head(v),inherited(vtail...){}

   typename Head::type head(){return m_head;}
   inherited& tail(){return this;}
protected:
   Head m_head;
};

//*/

//*****************type traits**********************/

template<typename>
struct _is_void_helper:public false_type{};
template<>
struct _is_void_helper<void>: public true_type{};
template <typename Tp>
struct is_void:public _is_void_helper<typename remove_cv<Tp>::type>::type
{};
#endif // MYEXTERN_HPP
