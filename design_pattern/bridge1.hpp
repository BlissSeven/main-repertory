#ifndef BRIDGE1_HPP
#define BRIDGE1_HPP
class Message{
public:
    virtual void Login(string username,string pwd){}
    virtual void SendMessage(string m)=0;
    virtual void SendPicture(Image im)=0;

    virtual void PlaySound()=0;
    virtual void DrawShape()=0;
    virtual void WriteText()=0;
    virtual void Connect()=0;

    virtual ~Message(){}
};

class PCMessageBase:public Message
{
    virtual void PlaySound(){}
    virtual void DrawShape(){}
    virtual void WriteText(){}
    virtual void Connect(){}

};
class MobileMessagerBase:public Message
{
    virtual void PlaySound(){}
    virtual void DrawShape(){}
    virtual void WriteText(){}
    virtual void Connect(){}

};


class PCMessageLite:public PCMessageBase
{
public:
    virtual void Login(string username,string pwd){
        PCMessageBase::Connect();
    }
    virtual void SendMessage(string m){
        PCMessageBase::WriteText();
    }
    virtual void SendPicture(Image im){
        PCMessageBase::SendPicture();
    }

};
class PCMessagePerfect:public PCMessageBase
{
public:
    virtual void Login(string username,string pwd){
        PCMessageBase::PlaySound();
        PCMessageBase::Connect();
    }
    virtual void SendMessage(string m){
        PCMessageBase::PlaySound();
        PCMessageBase::WriteText();
    }
    virtual void SendPicture(Image im){
        PCMessageBase::PlaySound();
        PCMessageBase::SendPicture();
    }

};

class MobileMessagerLite:public MobileMessagerBase
{
public:
    virtual void Login(string username,string pwd){
        MobileMessagerBase::Connect();
    }
    virtual void SendMessage(string m){
        MobileMessagerBase::WriteText();
    }
    virtual void SendPicture(Image im){
        MobileMessagerBase::SendPicture();
    }

};
class MobileMessagerPerfect:public MobileMessagerBase
{
public:
    virtual void Login(string username,string pwd){
        MobileMessagerBase::PlaySound();
        MobileMessagerBase::Connect();
    }
    virtual void SendMessage(string m){
        MobileMessagerBase::PlaySound();
        MobileMessagerBase::WriteText();
    }
    virtual void SendPicture(Image im){
        MobileMessagerBase::PlaySound();
        MobileMessagerBase::SendPicture();
    }

};
void Process(){
    Message* m=new MobileMessagerPerfect();
}
#endif // BRIDGE1_HPP
