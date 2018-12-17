#ifndef FACTORY_FILESPLITTER2_HPP
#define FACTORY_FILESPLITTER2_HPP


class ISplitter{
public:
    virtual void split()=0;
    virtual ~ISplitter(){}
};
class BinarySplitter:public ISplitter
{
};
class TxtSplitter:public ISplitter
{
};
class PictureSplitter:public ISplitter
{
};
class VideoSplitter:public ISplitter
{
};

#endif // FACTORY_FILESPLITTER2_HPP
