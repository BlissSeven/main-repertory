#ifndef MYADAPTER2_HPP
#define MYADAPTER2_HPP
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace  std;
void test_ostream_iterator()
{
    vector<int > vc;
    for(int i=0;i<10;i++)
        vc.push_back(i*10);
    ostream_iterator<int> out_it(std::cout,",");
    copy(vc.begin(),vc.end(),out_it);

}
void test_istream_iterator()
{
    double value1,value2;
    cout<<"input 2 values: "<<endl;
    istream_iterator<double> eos;
    istream_iterator<double> iit(std::cin);
    if(iit!=eos) value1=*iit;
    ++iit;

    if(iit!=eos)
        value2=*iit;

    cout<<value1<<" * "<<value2<<" = "<<value1*value2<<endl;
}
#endif // MYADAPTER2_HPP
