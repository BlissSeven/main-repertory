#ifndef MYLIST_HPP
#define MYLIST_HPP

//#include <list>
#include <iterator>
//#include <bits/stl_iterator_base_types.h>
#include <cstddef>
#include <iostream>
template <class T>
struct _list_node
{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <class T,class Ref,class Ptr>
struct _list_iterator{
    /* five typedef */
    typedef std::bidirectional_iterator_tag iterator_category;// wei sheng ming????
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef ptrdiff_t difference_type;

    typedef _list_iterator<T,Ref,Ptr> self;

    typedef  _list_node<T>* link_type;
    link_type node;// 有一个list_node数据

    reference operator*()const {return (*node).data;}
    pointer operator->() const {return &(operator*());}
    self& operator++()// prev ++ //++i
    {
        node=(link_type)((*node).next);
        return *this;
    }
    self operator++(int)//post ++ //i++
    {
        self tmp=*this;
        ++this;
        return tmp;
    }
};
template <class T>
struct iterator_traits
{
    typedef typename T::iterator_category iterator_category;
    typedef typename T::value_type value_type;
    typedef typename T::pointer pointer;
    typedef typename T::reference reference;
    typedef typename T::difference_type difference_type;
};
template <class T>
struct iterator_traits<T*>{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};
template <class T>
struct iterator_traits<const T*>{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};
template<class T,class Alloc>
class mylist{
protected:
    typedef _list_node<T> list_node;
public:
    typedef list_node* link_type;
    typedef _list_iterator<T,T&,T*> iterator;
protected:
    link_type node;
};

#endif // MYLIST_HPP
