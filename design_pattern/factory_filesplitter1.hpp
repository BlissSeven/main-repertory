#ifndef FACTORY_FILESPLITTER1_HPP
#define FACTORY_FILESPLITTER1_HPP

class ISplitter{
public:
    virtual void split()=0;
    virtual ~ISplitter(){}
};
class SplitterFactory{
public:
    virtual ISplitter* CreateSplitter()=0;
    virtual ~SplitterFactory(){}
};


//////////////////////////////////////////////
class BinarySplitter:public ISplitter
{
    virtual void split()
    {}
};
class TxtSplitter:public ISplitter
{
    virtual void split()
    {}
};
///////////////////////////////////////////////

class BinarySplitterFactory:public SplitterFactory
{
public:
    virtual ISplitter* CreateSplitter()
    {
        return new BinarySplitter();
    }
};
class TxtSplitterFactory:public SplitterFactory
{
public:
    virtual ISplitter* CreateSplitter()
    {
        return new TxtSplitter();
    }
};


#endif // FACTORY_FILESPLITTER1_HPP
