#ifndef MYFUNCTORS_HPP
#define MYFUNCTORS_HPP

#include <functional>

//public std::binary_function  c++11中被废弃 c++17被删除
template<class Arg1,class Arg2,class Result>
struct binary_function{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template<class Arg,class Result>
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};

template<class T>
struct logical_and:public binary_function<T,T, bool>
{
  bool operator()(const T&x,const T&y) const
  {
      return x && y;
  }
};

#endif // MYFUNCTORS_HPP
