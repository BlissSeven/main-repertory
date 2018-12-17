#ifndef MY_ALGORITHM_HPP
#define MY_ALGORITHM_HPP

#include <iterator>

#include <iostream>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>
using namespace std;

using _STD iterator_traits;
using _STD size_t;
//bidirectional_iterator_tag
void _display_category(random_access_iterator_tag)
{
    cout<<"random_access_iterator_tag"<<endl;
}
void _display_category(bidirectional_iterator_tag)
{
    cout<<"bidirectional_iterator_tag"<<endl;
}
void _display_category(forward_iterator_tag)
{
    cout<<"forward_iterator_tag"<<endl;
}
void _display_category(output_iterator_tag)
{
    cout<<"output_iterator_tag"<<endl;
}
void _display_category(input_iterator_tag)
{
    cout<<"input_iterator_tag"<<endl;
}

template <typename I>
void display_category(I itr)
{
    typename iterator_traits <I>::iterator_category cagy;

    cout<<typeid(itr).name()<<"  ";
    _display_category(cagy);
}
void test_iterator_category()
{
    cout<<"test_iterator_category start..."<<endl;
    display_category(array<int,10>::iterator());
    display_category(vector<int>::iterator());
    display_category(deque<int>::iterator());
    display_category(list<int>::iterator());

    display_category(set<int>::iterator());
    display_category(map<int,int>::iterator());
    display_category(unordered_set<int,int>::iterator());
    display_category(unordered_map<int,int>::iterator());
}
/*   iterator category 对算法影响*/
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first,InputIterator last,input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n=0;
    while(first!=last)
    {
        ++first;
        ++n;
    }
    return n;
}

template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first,InputIterator last,random_access_iterator_tag){

    return last-first;
}


template<class InputIterator>
inline typename iterator_traits <InputIterator>::difference_type
distance(InputIterator first,InputIterator last){
    typename iterator_traits<InputIterator>::iterator_category category;
    return _distance(first,last,category);
}
/**************************************************    advance ************************************************************/
template<class InputIterator ,class Distance>
void _advance(InputIterator& i ,Distance n,input_iterator_tag)
{
    while(n--)++i;
}
template<class BidirectionalIterator,class Distance>
void _advance(BidirectionalIterator& i ,Distance n,bidirectional_iterator_tag)
{
    if(n>=0)
        while(n--) ++i;
    else
        while(n++) --i;
}

template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
    typename iterator_traits<Iterator>::iterator_category category;
    return category();
}
template<class InputIterator,class Distance>
inline void advance(InputIterator&i, Distance n){
    _advance(i,n,iterator_category(i));
}

#endif // MY_ALGORITHM_HPP
