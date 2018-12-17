#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace  std;

class Component{
public:
    virtual void process()=0;
    virtual ~Component(){}

};

//tree node
class Composite:public Component{
    string name;
    list<Component*> elem;
public:
    Composite(const string&s):name(s){}
    void add(Component* element)
    {
        elem.push_back(element);
    }
    void remove(Component* element)
    {
        elem.remove(element);
    }
    void process(){
        //1. process current node
        //2. process leaf node
        cout<<"process composite"<<endl;
        for(auto &e:elem)
        {
            e->process();
        }
    }
};
class leaf:public Component{
    string name;
public:
    leaf(string s):name(s){

    }
    void process(){
        cout<<"process leaf"<<endl;
    }
};

void invoke(Component&c)
{
    c.process();
}


int main2(){
    Composite root("root");
    Composite treenode1("treenode1");
    Composite treenode2("treenode2");

    leaf leaf1("leaf1");
    leaf leaf2("leaf2");

    root.add(&treenode1);
    treenode1.add(&treenode2);
    treenode2.add(&leaf1);

    invoke(root);

    invoke(leaf2);

    invoke(treenode2);
}
#endif // COMPOSITE_HPP
