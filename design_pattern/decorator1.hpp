#ifndef DECORATOR1_HPP
#define DECORATOR1_HPP
class Stream{
public:
    virtual char read(int number)=0;
    virtual void seek(int position)=0;
    virtual void write(char data)=0;

    virtual ~Stream(){}
};
class FileStream:public Stream{
  public:
    virtual char read(int num){}
    virtual void seek(int p){}
    virtual void write(char data){}
};
class NetWorkStream:public Stream{
  public:
    virtual char read(int num){}
    virtual void seek(int p){}
    virtual void write(char data){}
};

class CryptoFileStream:public FileStream
{
public:
    virtual char read(int num)
    {
        FileStream::read(num);
    }
    virtual void seek(int num)
    {
        FileStream::seek(num);
    }
    virtual void write(char num)
    {
        FileStream::write(num);
    }
};
class CryptoNetWorkStream:public NetWorkStream
{
public:
    virtual char read(int num)
    {
        NetWorkStream::read(num);
    }
    virtual void seek(int num)
    {
        NetWorkStream::seek(num);
    }
    virtual void write(char num)
    {
        NetWorkStream::write(num);
    }
};
class BufferedFileStream:public FileStream
{
public:
    virtual char read(int num)
    {
        FileStream::read(num);
    }
    virtual void seek(int num)
    {
        FileStream::seek(num);
    }
    virtual void write(char num)
    {
        FileStream::write(num);
    }
};
class BufferedNetWorkStream:public NetWorkStream
{
public:
    virtual char read(int num)
    {
        NetWorkStream::read(num);
    }
    virtual void seek(int num)
    {
        NetWorkStream::seek(num);
    }
    virtual void write(char num)
    {
        NetWorkStream::write(num);
    }
};

void Process(){
    //编译时装配
CryptoFileStream *fs1 = new CryptoFileStream();

BufferedFileStream *fs2 = new BufferedFileStream();


}
#endif // DECORATOR1_HPP
