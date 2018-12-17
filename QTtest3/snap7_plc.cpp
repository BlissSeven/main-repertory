
#include "snap7_plc.hpp"


bool SNAP7_PLC::plc_check(int res,const char* str)
{
    if(res==0)
    {
        qDebug()<<str<<" opertion ok!"<<endl;
    }
    else
    {
        qDebug()<<str<<"opertion failure!: error code: "<<res<<endl;
    }
    return res==0;
}
bool SNAP7_PLC::plc_init(const char* ip)
{
    const char*  Address= ip;
    int Rack=0;
    int Slot=1;
    int res=0;
    res=Client->ConnectTo(Address,Rack,Slot);
    if(plc_check(res,"plc connect ..."))
    {
        qDebug()<<"connect to plc ip:"<<Address<<" Rack: "<<Rack<<" Slot: "<<Slot<<endl;
    }
    else return false;

    TS7OrderCode info;
    res=Client->GetOrderCode(&info);
    if(plc_check(res,"Get order code"))
    {
       qDebug()<<"Order Code : "<<info.Code<<endl;
    }
    else
        return false;
}

bool SNAP7_PLC::plc_online_test(const char* ip)
{
    QProcess exc;
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    string str("ping ");
    str+=ip;
    QString cmdstr=QString::fromStdString(str);//"ping 192.168.191.2";//ping 192.168.110.179  -n 2 -w 4000
    exc.start(cmdstr);//执行ping
    exc.waitForFinished(-1);//等待ping完成
    QString  outstr=codec->toUnicode(exc.readAll());//获取ping结果
    if((-1 !=outstr.indexOf("往返行程的估计时间")))
    {
        qDebug()<<ip<<" plc  on line "<<endl;
        return true;
    }
    else
    {
        qDebug()<<ip<<"plc out line"<<endl;
        return false;
    }
}
short SNAP7_PLC::DB_read_short(const int& db,const int& offset)
{
    byte buffer[2];
    int res;
    res=Client->DBRead(db,offset,2,&buffer);//read 2 bytes
    plc_check(res,"DB_read_short");
    return (short)((buffer[0]<<8) | buffer[1]);
}
float SNAP7_PLC::DB_read_float(const int&  db,const int& offset)
{
    float f;
    byte *p=(byte*)&f;

    byte buffer[4];
    int res;
    res=Client->DBRead(db,offset,4,&buffer);//read 2 bytes
    plc_check(res,"DB_read_float");

    p[0]=buffer[3];
    p[1]=buffer[2];
    p[2]=buffer[1];
    p[3]=buffer[0];

    return f;
}
bool SNAP7_PLC::DB_read_bit(const int& db,const int& offset,const int& bitnum)
{
    byte buffer[1];
    byte Mask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    int res;
    res=Client->DBRead(db,offset,1,&buffer);
    plc_check(res,"DB_read_bit");
    //if(bitnum<0) bitnum=0;
   // if(bitnum>7) bitnum=7;
    return (buffer[0] & Mask[bitnum]) != 0;
}
void SNAP7_PLC::DB_write_short(const int& db,const int& offset,const short& value)
{
    int res=0;
    byte buffer[2];
    buffer[0]=(byte)(value>>8);
    buffer[1]=(byte)(value&0x00ff);
    res=Client->DBWrite(db,offset,2,&buffer);//read 2 bytes
    plc_check(res,"DB_write_short");
}
void SNAP7_PLC::DB_write_float(const int& db,const int& offset,const float& value)
{
    byte *p=(byte*)&value;

    byte buffer[4];
    int res;

    buffer[3]=p[0];
    buffer[2]=p[1];
    buffer[1]=p[2];
    buffer[0]=p[3];
    res=Client->DBWrite(db,offset,4,&buffer);//write 4 bytes
    plc_check(res,"DB_write_float");
}
void SNAP7_PLC::DB_write_bit(const int& db,const int& offset,const bool& value,const int& bitnum)
{
    byte Mask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

   //if (bitnum < 0) bitnum = 0;
  // if (bitnum > 7) bitnum = 7;

   byte buffer[1];
   int res=0;
   res=Client->DBRead(db,offset,1,&buffer);
   plc_check(res,"DB_write_bit_1");
   if(value)
     buffer[0]=(byte) (buffer[0]|Mask[bitnum]);
   else
      buffer[0]=(byte) (buffer[0]& ~Mask[bitnum]);
   res=Client->DBWrite(db,offset,1,&buffer);
   plc_check(res,"DB_write_bit_2");
}
void SNAP7_PLC::plc_test(const char* ip)
{
    plc_online_test(ip);

    bool res=plc_init(ip);
    /* 实时位置 204 208 212 216 float*/
    /* 辐射点 300 314 318 312  316 318 210 f f f f i i f*/
    if(res)
    {
        float num=DB_read_float(300,204);
        qDebug()<<"300.204= "<<num<<endl;
         num=DB_read_float(300,208);
        qDebug()<<"300.208= "<<num<<endl;
         num=DB_read_float(300,212);
        qDebug()<<"300.212= "<<num<<endl;

        num=DB_read_float(300,216);
        qDebug()<<"300.216= "<<num<<endl;

        int num2=DB_read_short(300,316);
        qDebug()<<"300.316= "<<num2<<endl;
        num2=DB_read_short(300,318);
        qDebug()<<"300.318= "<<num2<<endl;

        DB_write_float(300,204,-5.23f);
        num=DB_read_float(300,204);
        qDebug()<<"300.204= "<<num<<endl;


        DB_write_short(300,318,1);
        num2=DB_read_short(300,318);
        qDebug()<<"300.318= "<<num2<<endl;
         Client->Disconnect();
     }
    else
    {
        qDebug()<<"plc test fail!!!"<<endl;
    }


}

