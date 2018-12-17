#ifndef DECORATOR2_HPP
#define DECORATOR2_HPP
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


class CryptoStream:public Stream
{
    Stream* stream;
public:
    CryptoStream(Stream* str)
        :stream(str){}
    virtual char read(int num)
    {
        stream->read(num);
    }
    virtual void seek(int num)
    {
        stream->seek(num);
    }
    virtual void write(char num)
    {
        stream->write(num);
    }
};

class BufferedStream:public Stream
{
    Stream* stream;
public:
    BufferedStream(Stream* str)
        :stream(str){}
    virtual char read(int num)
    {
        stream->read(num);
    }
    virtual void seek(int num)
    {
        stream->seek(num);
    }
    virtual void write(char num)
    {
        stream->write(num);
    }
};


void Process(){
    //编译时装配
//CryptoFileStream *fs1 = new CryptoFileStream();

//BufferedFileStream *fs2 = new BufferedFileStream();
    FileStream* s1=new FileStream();
    CryptoStream* s2=new CryptoStream(s1);

    BufferedStream* s3=new BufferedStream(s2);

}
#endif // DECORATOR1_HPP
