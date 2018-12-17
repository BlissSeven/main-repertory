#ifndef FLYWEIGHT_HPP
#define FLYWEIGHT_HPP
#include <string>
#include <map>
using namespace std;
using std::string;
class Font{
private:
    string key;
public:
    Font(const string& key){

    }

};
class FontFactory{
private:
    map <string,Font*> fontpool;
public:
    Font* GetFont(const string& key)
    {
        map<string,Font*>::iterator item=fontpool.find(key);
        if(item!=fontpool.end())
        {
            return fontpool[key];
        }
        else{
            Font* font=new Font(key);
            fontpool[key]=font;
            return font;
        }
    }
    void clear()
    {

    }
};
#endif // FLYWEIGHT_HPP
