#ifndef SNAP7_PLC_HPP
#define SNAP7_PLC_HPP
#include <snap7/snap7.h>
#include <QDebug>
#include <iostream>
#include <QProcess>
#include <QTextCodec>
#include <string>

using std::endl;
using std::cout;
using std::string;

class SNAP7_PLC{
private:
    TS7Client* Client;
public:
    SNAP7_PLC(){
        Client=new TS7Client();
    }
    ~SNAP7_PLC(){
        Client->Disconnect();
        delete Client;
    }

    SNAP7_PLC(const SNAP7_PLC& a) =delete;
    SNAP7_PLC operator=(const SNAP7_PLC& a)=delete;

    bool plc_init(const char* ip="192.168.1.10");
    void plc_disconnect()
    {
        int res=Client->Disconnect();
        plc_check(res,"plc disconnect");
    }
    bool plc_check(int res,const char* str);
    bool plc_online_test(const char* ip);
    short DB_read_short(const int& db,const int& offfset);
    float DB_read_float(const int&  db,const int& offset);
    bool DB_read_bit(const int& db,const int& offset,const int& bitnum);
    void DB_write_short(const int& db,const int& offset,const short& value);
    void DB_write_float(const int& db,const int& offset,const float& value);
    void DB_write_bit(const int& db,const int& offset,const bool& value,const int& bitnum);

    void plc_test(const char* ip="192.168.1.10");
};
#endif // SNAP7_PLC_HPP
