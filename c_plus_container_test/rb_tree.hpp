#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include <memory>
template <class Key,
          class Value,//(key|data)合起来 =value
          class KeyOfValue,//在这个value里，这个key要怎么拿到
          class Compare,// 两个元素比大小 函数
          class Alloc=alloc>
class rb_tree{
  protected:
    typedef _rb_tree_node<Value> rb_tree_node;
  public:
    typedef rb_tree_node* link_type;
    typedef size_t size_type;
protected:
    size_type node_count;//rb_tree 大小 节点数量
    link_type header;
    Compare key_compare;//key 大小判定 函数
};

template <class Arg,class Result>
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};
template <class T>//仿函数
    struct identity:public unary_function<T,T>{
        const T& operator()(const T&x){return x;}
    };
#endif // RB_TREE_HPP
    template <class Arg1,class Arg2,class Result>
    struct binary_function{
        typedef  Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };
template <class T>
struct less:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T&y)
    {
        return x<y;
    }
};
rb_tree<int,
        int,
        identity<int>,
        less<int>,
        allocator>
mytree;


