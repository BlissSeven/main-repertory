#ifndef MYSET_HPP
#define MYSET_HPP
#include<algorithm>


template<class Key,class Compare =less<Key>,class Alloc>
class set{
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
private:
    typedef rb_tree<key_type,value_type,
                    identity<value_type>,key_compare,Alloc> rep_type;
    rep_type t;
public:
    typedef typename retype::const_iterator iterator;
};

#endif // MYSET_HPP
