#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <iostream>

using std::cout;
using std::endl;

/*
工控机IP 192.168.1.11
ABB IP  192.168.1.12
PLC IP  192.168.1.10
*/
int main(int argc, char *argv[])
{
    double i=0;
//    QImage image(10,10,QImage::Format_RGB32);

//    qDebug()<<image.sizeInBytes()<<endl;
//    qDebug()<<"test"<<endl;
    qDebug()<<1920*1080*4/1024/1024<<endl;//8100M 7m
//    if(!DShowLib::InitLibrary())
//    {
//        qDebug()<<"DShowLib::InitLibrary error!"<<endl;
//    }

   // /*
   qDebug()<<"INT_MAX"<<INT_MAX<<endl;
   qDebug()<<"INT_MIN"<<INT_MIN<<endl;

    float f=-5.23F;//63 157 112 164
    byte *p=(byte*)&f;
    qDebug()<<"0: "<<(int)p[0]<<endl;
    qDebug()<<"1: "<<(int)p[1]<<endl;
    qDebug()<<"2: "<<(int)p[2]<<endl;
    qDebug()<<"3: "<<(int)p[3]<<endl;


    float ff;
    byte *p2=(byte *)&ff;

    p2[3]=p[3];
    p2[2]=p[2];
    p2[1]=p[1];
    p2[0]=p[0];
    qDebug()<<"ff: "<<ff<<endl;


    qDebug()<<"sizeof(int): "<<sizeof(int)<<endl;//4
    qDebug()<<"sizeof(short): "<<sizeof(short)<<endl;//2
    qDebug()<<"sizeof(float): "<<sizeof(float)<<endl;//4
    qDebug()<<"sizeof (bool): "<<sizeof (bool)<<endl;//1


  // /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
   // */
}
