#ifndef MEMENTO_HPP
#define MEMENTO_HPP
class memento
{
  string state;
public:
  memento(const string& s):state(s){}
  string getstate() const {return state;}
  void setstate(const string&s )
  {
      this->state=s;
  }
};
class originator{
    string state;
public:
    originator(){}
    memento creatememento(){
        memento m(state);
        return m;
    }
    void setmemento(const memento& m)
    {
        state=m.getstate();
    }
};
int main2()
{
    originator ori;
    memento mem=ori.creatememento();
      //... 改变orginator状态

    ori.setmemento(mem);
}
#endif // MEMENTO_HPP
