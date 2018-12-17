#ifndef BRIDGE2_HPP
#define BRIDGE2_HPP
#include<string>
using namespace std;

class MessageIpl{
public:
    virtual void PlaySound()=0;
    virtual void DrawShape()=0;
    virtual void WriteText()=0;
    virtual void Connect()=0;

    virtual ~MessageIpl(){}
};

class Message{
protected:
    MessageIpl* messageipl;
public:
     Message(MessageIpl* messageimpl1)
        :messageipl(messageimpl1){}

    virtual void Login(string username,string pwd){}
    virtual void SendMessage(string m)=0;
    virtual void SendPicture(Image im)=0;


    virtual ~Message(){}
};


class PCMessageIpl:public MessageIpl
{
    virtual void PlaySound(){}
    virtual void DrawShape(){}
    virtual void WriteText(){}
    virtual void Connect(){}

};
class MobileMessagerIpl:public MessageIpl
{
    virtual void PlaySound(){}
    virtual void DrawShape(){}
    virtual void WriteText(){}
    virtual void Connect(){}
};


class MessageLite:public Message
{
public:
    MessageLite(MessageIpl* ms):
        Message(ms){  }
    virtual void Login(string username,string pwd){
        messageipl->Connect();
    }
    virtual void SendMessage(string m){
        messageipl->WriteText();
    }
    virtual void SendPicture(Image im){
        messageipl->DrawShape();
    }
};
class MessagePerfect:public Message
{
public:
    MessagePerfect(MessageIpl* ms):
        Message(ms){  }
    virtual void Login(string username,string pwd){
        messageipl->PlaySound();
        messageipl->Connect();
    }
    virtual void SendMessage(string m){
        messageipl->PlaySound();
        messageipl->WriteText();
    }
    virtual void SendPicture(Image im){
        messageipl->PlaySound();
        messageipl->DrawShape();
    }
};
void Process(){
    MessageIpl* mImp=new PCMessageIpl();
    Message *m =new Message(mImp);
}
#endif // BRIDGE1_HPP
