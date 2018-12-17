#ifndef MYHASHTABLE_HPP
#define MYHASHTABLE_HPP

#include <vector>
#include <hash_set>
#include <string>

template <class Value>
struct _hashtable_node{
    _hashtable_node* next;
    Value val;
};


template<class Value,class Key,class HashFcn,
         class ExtractKey,class EqualKey,
         class Alloc>
class hashtable{
public:
    typedef HashFcn hasher;
    typedef EqualKey key_equal;
    typedef size_t size_type;
private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;
    typedef _hashtable_node<Value> node;
    std::vector<node*,Alloc> buckets;
    size_type num_elements;
public:
    size_type bucket_count() const{return buckets.size();}
};

template <class Value,class Key,class HashFcn,
          class ExtractKey,class EqualKey,class Alloc>
struct _hash_iterator{
    _hashtable_node<class Value>* cur;
    hashtable<class Value,class Key,class HashFcn,
            class ExtractKey,class EqualKey,class Alloc>* ht;
};


struct eqstr{
    bool operator()(const char* s1,const char* s2)const{
        return (strcmp(s1,s2)==0);
    }
};
void hashtable_test()
{
    hashtable< std::string,
            std::string,
            std::hash<std::string>,
            std::identity<std::string>,eqstr,
            std::allocator<std::string> >
            ht("123","123",std::hash<std::string >(),std::identity<std::string>(),eqstr(),std::allocator<std::string>());

    ht.insert_unique("kiwi");
    ht.insert_unique("plum");
}




#endif // MYHASHTABLE_HPP
