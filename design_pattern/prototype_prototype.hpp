#ifndef PROTOTYPE_PROTOTYPE_HPP
#define PROTOTYPE_PROTOTYPE_HPP

class ISplitter
{
public:
    virtual void split()=0;
    virtual ISplitter* clone()=0;
};

class BinarySplitter:public ISplitter
{
public:
    virtual ISplitter* clone(){
        return new BinarySplitter(*this);
    }
};
class TxtSplitter:public ISplitter
{
public:
    virtual ISplitter* clone(){
        return new TxtSplitter(*this);
    }
};
#endif // PROTOTYPE_PROTOTYPE_HPP
