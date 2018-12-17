#ifndef OBSERVER_FILESPLITTER_HPP
#define OBSERVER_FILESPLITTER_HPP
#include <string>
using namespace std;
class IProgess
{
public:
    virtual void Doprogess(float ){}
    virtual ~IProgess(){}
};

class FileSplitter
{
    string filepath;
    int filenumber;
    //ProgessBar* progressbar;
    List<IProgess*> iprogesslist;
public:
    FileSplitter(const string& filepath1,int filenumber1,ProgessBar progessbar1)
        :filepath(filepath1),filenumber(filenumber1),progressbar(progessbar1){}
    void split(){
        for(int i=0;i<filenumber;i++)
        {
            float value=(i+1)/filenumber;
            ///progressbar->setvalue(value);
             iprogess->Doprogess(value);
        }
    }
    void addIprogess(Iprogess* iprogess1)
    {iprogess.pushback(iprogess1);}
    void removeIprogess(Iprogess* iprogess1)
    {iprogess.remove(iprogess1);}
    void onprogess(float value)
    {
        for(auto it=iprogesslist.begin(),it!=iprogesslist.end(),++it)
        {
            (*it)->Doprogess(value);
        }
    }
};
#endif // OBSERVER_FILESPLITTER_HPP
