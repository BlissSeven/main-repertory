#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<char> set1;
    set1.insert('p');
    set1.insert('w');
     //set1.insert('m');


    for(auto it=set1.begin();it!=set1.end();it++)
        cout<<*it<<endl;
    cout<<endl;
    auto pair=set1.insert('w');
    auto b=set1.begin();
    b++;
    auto bb=set1.end();
    bb--;
    cout<<(pair.first == (set1.begin()))<<endl;
    cout<<(pair.first == (set1.end()))<<endl;
     cout<<(pair.first == b)<<endl;
    cout<<(pair.first == bb)<<endl;


     cout<<*pair.first<<endl;

    cout<<&(pair.first)<<endl;
    cout<<&b<<endl;

    cout<<&(set1.begin())<<endl;
    cout<<&(b)<<endl;





    for(auto it=set1.begin();it!=set1.end();it++)
        cout<<*it<<" ";

    cout << "Hello World!" << endl;
    return 0;
}
