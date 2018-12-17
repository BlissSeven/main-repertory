#ifndef MYDEQUE_HPP
#define MYDEQUE_HPP

#include <deque>
#include <memory>
#include <cstddef>//ptrdiff_t
template<class T,class Ref,class Ptr,size_t BuffSize>

struct _deque_iterator
{
    /*5 ge typedef */
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr Pointer;
    typedef Ref reference;
    typedef ptrdiff_t difference_type;

    typedef T** map_pointer;
    typedef _deque_iterator self;
    typedef Ptr pointer;
    /* 4 个 数据 */
    T* cur;
    T* first;
    T* last;
    map_pointer node;

    self& set_node(map_pointer new_node)
    {
        node=new_node;
        first=*new_node;/////
        last=first+difference_type(buffersize());
    }
    reference operator*()const
    {return *cur;}
    pointer operator->() const
    {return &(operator*());}
    difference_type operator-(const self&x)const// 当前-x,那么当前一定在x后边
    {
        return difference_type(buffer_size())*(node-x.node-1)+(cur-first)+(x.last-x.cur);
    }
    self& operator++()
    {
        ++cur;
        if(cur==last){
            set_node(node+1);
            cur=first;
        }
        return *this;
    }
    self operator++(int)
    {
        self tmp=*this;
        ++*this;
        return tmp;
    }
    self& operator--(){
        if(cur==first){
            set_node(node-1);
            cur=last;
        }
        --cur;
        return *this;
    }
    self operator--(int)
    {
        self tmp=*this;
        --*this;
        return tmp;
    }
    self& operator+=(difference_type n){
        difference_type offset=n+(cur-first);
        if(offset>=0 && offset <difference_type(buffer_size()))
        {
            cur+=n;
        }
        else{
            difference_type node_offset=offset>0? offset/difference_type(buffer_size()):
                                                  -difference_type((-offset-1)/buffer_size())-1;
            set_node(node+node_offset);
            cur=first+(offset-node_offset*difference_type(buffer_size()));
        }
        return *this;
    }
    self operator+(difference_type n) const{
        self tmp=*this;
        return tmp+=n;
    }
    self& operator-=(difference_type n)
    {
        return *this+=-n;
    }
    self operator -(difference_type n)const
    {
        self tmp=*this;
        return tmp-=n;
    }
    reference operator[](difference_type n)
    {
        return *(*this+n);
    }
};
template<class T,class Alloc,size_t BufSize=0>
class mydeque
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef ptrdiff_t difference_type;

    typedef _deque_iterator<T,T&,T*,BufSize> iterator;
    typedef pointer* map_pointer;
    typedef  size_t size_type;
protected:
    iterator start;
    iterator finish;
    map_pointer map;
    size_type map_size;
public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size() const {return finish-start;}
    reference operator[](size_type n)
    {
        return start[difference_type(n)];
    }
    reference front()
    {return *start;}
    reference back()////????? 返回引用？？？
    { iterator tmp=finish;--tmp;return *tmp;}
    bool empty() const
    {return start ==finish;}

    iterator insert(iterator position,const value_type & x)
    {
        if(position.cur==start.cur)
        {
            push_front(x);
            return start;
        }
        else if(position.cur==finish.cur)
        {
            push_back(x);
            iterator tmp=finish;
            --tmp;
            return tmp;
        }
        else
        {
            return insert_aux(position,x);
        }
    }
    iterator insert_aux(iterator pos,const value_type&x )
    {
        difference_type index=pos-start;
        value_type x_copy=x;
        if(index<size()/2){
            push_front(front());
//            copy(front2,pos1,front1);
        }
        else
        {
            push_back(back());
//            copy_backward(pos,back2,back1);
        }
        *pos=x_copy;
        return pos;
    }

};


#endif // MYDEQUE_HPP
