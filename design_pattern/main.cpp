#include <iostream>

#include <composite.hpp>

using namespace std;

int main()
{

    cout << "Hello World!" << endl;
    short tell[10]={10};
    cout<<"tell: "<<tell<<endl;
    short (*pas)[10]=&tell;
    //cout<<<"&tell: "<< *pas<endl;

    main2();
    return 0;
}
