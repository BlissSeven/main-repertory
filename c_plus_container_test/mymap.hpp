#ifndef MYMAP_HPP
#define MYMAP_HPP

#include <algorithm>
#include<map>
template <class Arg,class Result >
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};
template <class Pair>
struct select1st:
        public unary_function<Pair,typename Pair::first_type>{
  const typename Pair::first_type& operator()(const Pair& x)const
  {
      return x.first;
  }
};
template<class Key,class T,class Compare=less< Key >,class Alloc=alloc>
class map{
public:
    typedef Key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<const Key,T> value_type;
    typedef Compare key_compare;
private:
    typedef rb_tree <key_type,value_type,
                    select1st<value_type>,key_compare,Alloc> rep_type;
    rep_type t;
public:
    typedef typename rep_type::iterator iterator;
}
#endif // MYMAP_HPP
