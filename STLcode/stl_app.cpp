#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>
#include <cstdio>  //snprintf()

const long ASIZE=50000l;
using namespace std; //allocator

long get_a_target_long()
{
    long target=0;
    cout<<"target (0-"<<RAND_MAX<<"):";
    cin>>target;
    return target;
}
string get_a_target_string()
{
    long target =0;
    char buf[10];
     cout<<"target (0-"<<RAND_MAX<<"):";
    cin>>target;
    snprintf(buf,10,"%d",target);
    return string(buf);
}
int compareLongs(const void* a,const void* b)
{
    return (*(long*)a - *(long*)b);
}
int compareStrings(const void* a,const void* b)
{
    if(*(string*)a > *(string*)b)
        return 1;
    else if(*(string*)a< *(string*)b)
            return -1;

    else
        return 0;    
}
#include <array>
#include <iostream>
#include <ctime> 
#include <cstdlib> //qsort, bsearch, NULL //RAND_MAX

using namespace std;
namespace bliss_test_array{
    
    void test_array(){
        cout<<"test array start ...."<<endl;
        array <long,ASIZE> c;
        clock_t timestart=clock();
        srand(time(NULL));
        for(long i=0;i<ASIZE;i++)
            c[i]=rand()%ASIZE;//0-(ASIZE-1)
        cout<<"clock-timestart "<<(clock()-timestart)<<endl;
        cout<<"size: "<<c.size()<<endl;
        cout<<"front "<<c.front()<<endl;
        cout<<"back "<<c.back()<<endl;
        cout<<"data "<<c.data()<<endl;
        long target=get_a_target_long();
        timestart=clock();
        qsort(c.data(),ASIZE,sizeof(long),compareLongs);
        long* pitem=(long*)bsearch(&target,(c.data()),ASIZE,sizeof(long),compareLongs);
        cout<<"cost time: "<<clock()-timestart<<" ms"<<endl;
        if(pitem!=NULL)
            cout<<"found, "<<*pitem<<endl;
        else
            cout<<"not found \n";
    }

}
#include <vector>
#include <iostream>
#include <ctime> 
#include <cstdlib> //qsort, bsearch, NULL //RAND_MAX

namespace bliss_test_vector
{
    void test_vector(long& value){
        cout<<"\n test vector start ,,,\n";
        vector<string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
                snprintf(buf,10,"%d",rand()%ASIZE);
                c.push_back(buf);
            }
            catch(exception& p){
                cout<<"i: "<<i<<" "<<p.what()<<endl;
                abort();
            }
        }
        cout<<"cost time: "<<clock()-timestart<<endl;
        cout<<"size: "<<c.size()<<endl;
        cout<<"front: "<<c.front()<<endl;
        cout<<"back: "<<c.back()<<endl;
        cout<<"data: "<<c.data()<<endl;
        cout<<"capacity: "<<c.capacity()<<endl;
        string target=get_a_target_string();
        {
            timestart=clock();
            auto pitem=::find(c.begin(),c.end(),target);
            cout<<"find cost time ms "<<clock()-timestart<<endl;
            if(pitem!=c.end())
                cout<<"found, is "<<*pitem<<endl;
            else
                cout<<"not found "<<endl;
        }
        {
            timestart=clock();
            sort(c.begin(),c.end());
            //qsort(c.data(),value,sizeof(string),compareStrings);
            clock_t timestart2=clock();
            string* pitem=(string*)bsearch(&target,c.data(),c.size(),sizeof(string),compareStrings);
            cout<<"sort+bsearch cost time ms "<<clock()-timestart<<endl;
            cout<<"sot cost time : "<<timestart2-timestart<<"\n ratio: "<<(timestart2-timestart)*1.0/(clock()-timestart)<<endl;
            if(pitem!=NULL)
                cout<<"found, is "<<*pitem<<endl;
            else
                cout<<"not found "<<endl;
        }
    }
}
#include <list>
namespace bliss_test_list
{
    void test_list(long& value)
    {
        cout<<"\n test list start"<<endl;
        list <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.push_back(string(buf));
            }
            catch(exception& p){
                    cout<<"i "<<i<<"  "<<p.what()<<endl;
                    abort();
            }
        }
        cout<<"list cost time: "<<clock()-timestart<<endl;
        cout<<"list size "<<c.size()<<endl;
        cout<<"list max_size "<<c.max_size()<<endl;
        cout<<"list front "<<c.front()<<endl;
        cout<<"list back "<<c.back()<<endl;
        string target=get_a_target_string();
        {
            timestart=clock();
            auto pitem=::find(c.begin(),c.end(),target);
            cout<<"list find cost time ms "<<clock()-timestart<<endl;
            if(pitem!=c.end())
                cout<<"list found, is "<<*pitem<<endl;
            else
                cout<<"list not found "<<endl;
        }
        {
            timestart=clock();
            c.sort();
            //qsort(c.data(),value,sizeof(string),compareStrings);
            clock_t timestart2=clock();
            //string* pitem=(string*)bsearch(&target,c.data(),c.size(),sizeof(string),compareStrings);
            cout<<"list c.sort+bsearch cost time ms "<<clock()-timestart<<endl;
            //cout<<"c.sot cost time : "<<timestart2-timestart<<"\n ratio: "<<(timestart2-timestart)*1.0/(clock()-timestart)<<endl;
           // if(pitem!=NULL)
            //    cout<<"found, is "<<*pitem<<endl;
           // else
            //    cout<<"not found "<<endl;
        }
    }
}
#include <deque>
namespace bliss_test_deque
{
    void test_deque(long& value)
    {
        cout<<"\n test deque start"<<endl;
        deque <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.push_back(string(buf));
            }
            catch(exception& p){
                    cout<<"i "<<i<<"  "<<p.what()<<endl;
                    abort();
            }
        }
        cout<<"deque cost time: "<<clock()-timestart<<endl;
        cout<<"deque size "<<c.size()<<endl;
        cout<<"deque max_size "<<c.max_size()<<endl;
        cout<<"deque front "<<c.front()<<endl;
        cout<<"deque back "<<c.back()<<endl;
        string target=get_a_target_string();
        {
            timestart=clock();
            auto pitem=::find(c.begin(),c.end(),target);
            cout<<"deque find cost time ms "<<clock()-timestart<<endl;
            if(pitem!=c.end())
                cout<<"deque found, is "<<*pitem<<endl;
            else
                cout<<"deque not found "<<endl;
        }
        {
            timestart=clock();
            ::sort(c.begin(),c.end());
            //qsort(c.data(),value,sizeof(string),compareStrings);
            clock_t timestart2=clock();
            //string* pitem=(string*)bsearch(&target,c.data(),c.size(),sizeof(string),compareStrings);
            cout<<"deque c.sort+bsearch cost time ms "<<clock()-timestart<<endl;
            //cout<<"c.sot cost time : "<<timestart2-timestart<<"\n ratio: "<<(timestart2-timestart)*1.0/(clock()-timestart)<<endl;
           // if(pitem!=NULL)
            //    cout<<"found, is "<<*pitem<<endl;
           // else
            //    cout<<"not found "<<endl;
        }
    }
}
#include <stack>
namespace bliss_test_stack
{
    void test_stack(long& value)
    {
        cout<<"\n test stack start"<<endl;
        stack <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.push(string(buf));
            }
            catch(exception& p){
                    cout<<"i "<<i<<"  "<<p.what()<<endl;
                    abort();
            }
        }
        cout<<"stack cost time: "<<clock()-timestart<<endl;
        cout<<"stack size "<<c.size()<<endl;
        cout<<"stack top "<<c.top()<<endl;
        cout<<"stack pop "<<endl;
        c.pop();
        cout<<"stack size "<<c.size()<<endl;
        cout<<"stack top "<<c.top()<<endl;
        //cout<<"deque max_size "<<c.max_size()<<endl;
        //cout<<"deque front "<<c.front()<<endl;
        //cout<<"deque back "<<c.back()<<endl;
        
    }
}
#include <queue>
namespace bliss_test_queue
{
    void test_queue(long& value)
    {
        cout<<"\n test queue start"<<endl;
        queue <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.push(string(buf));
            }
            catch(exception& p){
                    cout<<"i "<<i<<"  "<<p.what()<<endl;
                    abort();
            }
        }
        cout<<"queue cost time: "<<clock()-timestart<<endl;
        cout<<"queue size "<<c.size()<<endl;
        cout<<"queue front "<<c.front()<<endl;
        cout<<"queue back "<<c.back()<<endl;
        cout<<"queue pop "<<endl;
        c.pop();
        cout<<"queue size "<<c.size()<<endl;
        cout<<"queue front "<<c.front()<<endl;
        cout<<"queue back "<<c.back()<<endl;
        //cout<<"deque max_size "<<c.max_size()<<endl;
        //cout<<"deque front "<<c.front()<<endl;
        //cout<<"deque back "<<c.back()<<endl;
        
    }
}


#include <set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace bliss_test_multiset
{
    void test_multiset(long& value)
    {
        cout<<"\n test multiset start"<<endl;
        multiset <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.insert(string(buf));   
            }
            catch(exception& p){
                    cout<<"i "<<i<<"  "<<p.what()<<endl;
                    abort();
            }
        }
        cout<<"multiset cost time: "<<clock()-timestart<<endl;
        cout<<"multiset size "<<c.size()<<endl;
        cout<<"multiset max_size "<<c.max_size()<<endl;
         string target=get_a_target_string();
        {
            timestart=clock();
            auto pitem=::find(c.begin(),c.end(),target);
            cout<<"multiset find cost time ms "<<clock()-timestart<<endl;
            if(pitem!=c.end())
                cout<<"multiset found, is "<<*pitem<<endl;
            else
                cout<<"multiset not found "<<endl;
        }
        {
           // cout<<"find cost time :"<<clock()-timestart<<endl;
            timestart=clock();
           
            auto pitem=c.find(target);
            cout<<"c.find cost time :"<<clock()-timestart<<endl;
            if(pitem != c.end())
                cout<<"found "<<*pitem<<endl;

            else
                cout<<"not found!"<<endl;
        }
        
    }
}
#include <map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime>
namespace bliss_test_multimap
{
    void test_multimap(long &value)
    {
        cout<<"test multimap start..."<<endl;
        multimap<long,string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++){
            try{
                snprintf(buf,10,"%d",rand()%value);
                c.insert(pair<long,string> (i,buf));
            }
            catch(exception& p){
                cout<<"i: "<<i<<" "<<p.what()<<endl;
                abort();
            }
        }
        cout<<"inset cost time "<<clock()-timestart<<endl;
        cout<<"multimap size "<<c.size()<<endl;
        cout<<"multimap maxsize "<<c.max_size()<<endl;
        long target=get_a_target_long();
        timestart=clock();
        auto pitem=c.find(target);
        cout<<"c.find cost time "<<clock()-timestart<<endl;
        if(pitem!=c.end())
            cout<<"find "<<(*pitem).first<<" : " <<(*pitem).second<<endl;
        else
            cout<<"not found !"<<endl;
    }
}
#include <unordered_set>
namespace bliss_test_umultiset
{
     void test_umultiset(long& value)
    {
        cout<<"\n test unordered multiset start"<<endl;
        unordered_multiset <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.insert(string(buf));   
            }
            catch(exception& p){
                    cout<<"i "<<i<<"  "<<p.what()<<endl;
                    abort();
            }
        }
        cout<<"unordered multiset cost time: "<<clock()-timestart<<endl;
        cout<<"unorderedmultiset size "<<c.size()<<endl;
        cout<<"unordered multiset max_size "<<c.max_size()<<endl;
        cout<<"unordered multiset c.bucket_count "<<c.bucket_count()<<endl;
        cout<<"unordered multiset c.max_bucket_count "<<c.max_bucket_count()<<endl;
        cout<<"unordered multiset c.load_factor "<<c.load_factor()<<endl;
        cout<<"unordered multiset c.max_load_factor "<<c.max_load_factor()<<endl;
        
        for(unsigned i=0;i<20;i++){
            cout<<"bucket "<<i<<" has "<<c.bucket_size(i)<<" elements!"<<endl;
        }
          string target=get_a_target_string();
        {
            timestart=clock();
            auto pitem=::find(c.begin(),c.end(),target);
            cout<<"unordered multiset find cost time ms "<<clock()-timestart<<endl;
            if(pitem!=c.end())
                cout<<"unordered multiset found, is "<<*pitem<<endl;
            else
                cout<<"unordered multiset not found "<<endl;
        }
        {
           // cout<<"find cost time :"<<clock()-timestart<<endl;
            timestart=clock();
           
            auto pitem=c.find(target);
            cout<<"unordered multiset c.find cost time :"<<clock()-timestart<<endl;
            if(pitem != c.end())
                cout<<"found "<<*pitem<<endl;

            else
                cout<<"not found!"<<endl;
        }
    }
}
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime>
namespace bliss_test_umultimap
{
    void test_umultimap(long &value)
    {
        cout<<"test unordered multimap start..."<<endl;
        unordered_multimap<long,string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++){
            try{
                snprintf(buf,10,"%d",rand()%value);
                c.insert(pair<long,string> (i,buf));
            }
            catch(exception& p){
                cout<<"i: "<<i<<" "<<p.what()<<endl;
                abort();
            }
        }
        cout<<"unordered multimap inset cost time "<<clock()-timestart<<endl;
        cout<<"unordered multimap size "<<c.size()<<endl;
        cout<<"unordered multimap maxsize "<<c.max_size()<<endl;
        long target=get_a_target_long();
        timestart=clock();
        auto pitem=c.find(target);
        cout<<"unordered multimap c.find cost time "<<clock()-timestart<<endl;
        if(pitem!=c.end())
            cout<<"unordered multimap find "<<(*pitem).first<<" : " <<(*pitem).second<<endl;
        else
            cout<<"unordered multimap not found !"<<endl;
    }
}
void test_range()
{
    int ia[6] = {27, 210,2,3,41,40};
    vector<int, allocator<int> > vi(ia, ia + 6);
    cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)))<<endl;
    vector<int, allocator<int> > ::iterator it=vi.begin();
    for(;it!=vi.end();it++)
        cout<<*it<<endl;
    cout<<"c++11 range for"<<endl;
    for(auto its:vi){
        cout<<its<<endl;
    }
}

namespace bliss_test_set{
    void test_set(long& value)
    {
        cout<<"test set start .."<<endl;
        set <string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i<value;i++)
        {
            try{
            snprintf(buf,10,"%d",rand()%value);
            c.insert(buf);
            }
            catch(exception & p){
                cout<<"i: "<<i<<p.what()<<endl;
            }
        }
        cout<<"set insert cost time : "<<clock()-timestart<<endl;
        cout<<"set size "<<c.size()<<endl;
        string target=get_a_target_string();
        {
            timestart=clock();
            auto pitem=::find(c.begin(),c.end(),target);
            cout<<".find cost time "<<clock()-timestart<<endl;
            if(pitem!=c.end())
                cout<<"set find "<<*pitem<<endl;
            else    
                cout<<"not find !"<<endl;
        }
        {
            timestart=clock();
            auto pitem=c.find(target);
            cout<<"set c.find cost time "<<clock()-timestart<<endl;
            if(pitem!= c.end())
                cout<<" find "<<*pitem<<endl;
            else    
                cout<<"not find !"<<endl;
        }
    }

}
#include <map>
namespace bliss_test_map
{
    void test_map(long& value)
    {
        cout<<"test map start .."<<endl;
        map<long,string> c;
        char buf[10];
        clock_t timestart=clock();
        for(long i=0;i< value;i++){
            try{
                snprintf(buf,10,"%d",rand()%value);
                c[i]=string(buf);// key=,value= string(buf);
            }
             catch(exception & p){
                cout<<"i: "<<i<<p.what()<<endl;
            }
        }
        cout<<"map insert cost time : "<<clock()-timestart<<endl;
        cout<<"map size "<<c.size()<<endl;
        long target = get_a_target_long();		
        timestart = clock();		
        auto pItem = c.find(target);								
	    cout << "c.find(), milli-seconds : " << (clock()-timestart) << endl;		 
	    if (pItem != c.end())
    	    cout << "found, value=" << (*pItem).second << endl;
  	    else
    	    cout << "not found! " << endl;			
    	
        c.clear();	
    }
}

bool strlonger(const string& s1,const string& s2)
{
    return s1.size()<s2.size();
}
template <class T>
inline const T& max2(const T& a,const T& b)
{
    return a<b? b:a;
}
template <class T,class Compare>
inline const T& max2(const T& a,const T& b,Compare comps)
{
    return comps(a,b)? b:a;
}

void tese_max()
{
   
    cout<<"max(string(\"zoo\"),string(\" hello\")) "<< max2(string("zoo"),string("hello"))<<endl;
    cout<<"max(string(\"zoo\"),string(\" hello\")) 2"<< max2(string("zoo"),string("hello"),strlonger)<<endl;
}
int main()
{
   //bliss_test_array::test_array();
    long value=50000;
   //bliss_test_vector::test_vector(value);
    //bliss_test_list::test_list(value);
    //bliss_test_deque::test_deque(value);
    //bliss_test_stack::test_stack(value);
    //bliss_test_queue::test_queue(value);
   // bliss_test_multiset::test_multiset(value);
    //bliss_test_multimap::test_multimap(value);
    //bliss_test_umultiset::test_umultiset(value);
    //bliss_test_umultimap::test_umultimap(value);
    tese_max();
    char a;
    cout<<"please input anything to exit...";
    cin.get(a);
    cin.get(a);
    return 0;
}