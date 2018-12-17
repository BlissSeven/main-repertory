#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tisudshl.h"
#include "cmdhelper.h"
#include <QMediaPlayer>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QSize>
#include <QLabel>
#include <QMessageBox>
#include <snap7/snap7.h>
#include <QPointF>
#include <QDebug>

#include <iostream>
using namespace std;


#include <QProcess>
#include <QTextCodec>
#include <vector>
namespace Ui {
class MainWindow;
}

using namespace  DShowLib;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_released();
    void on_closeButton_released();

    void on_timer_timeout(); //定时器中断处理槽函数,手工定义
    void on_timer2_timeout(); //定时器中断处理槽函数,手工定义

    void on_mouseClicked(QPoint point);
    void on_captureButton_released();

    void on_savetable_released();
    void on_saveButton_released();

    void on_Cancel_released();

private:
    QLabel* remote_status;// 状态栏 远程主机ping
    QLabel* plc_status; //状态栏 plc连接状态
    unsigned int pointno=0;// point no
    vector<QPoint> point_vector;
private:
    Ui::MainWindow *ui;

    QTimer *fTimer;  //定时器
    QTimer * fTimer2;// camera flush


    QImage *img_temp;

   // QTime   fTimeCounter;//计时器
    QPainter painter;
   // QPen  pen;

     //QSize pt_ratio;
    double x_ratio;
    double y_ratio;

private:
    DShowLib::Grabber* m_pGrabber;    
    DShowLib::tFrameHandlerSinkPtr pSink;

private:
    TS7Client* Client;
public:
    void plc_init();
    bool plc_check(int res,const char* str);

    short DB_read_short(const int& db,const int& offfset);
    float DB_read_float(const int&  db,const int& offset);
    bool DB_read_bit(const int& db,const int& offset,const int& bitnum);
    void DB_write_short(const int& db,const int& offset,const short& value);
    void DB_write_float(const int& db,const int& offset,const float& value);
    void DB_write_bit(const int& db,const int& offset,const bool& value,const int& bitnum);

public:
    bool online_test(const QString& ip,const char* device);
};

#endif // MAINWINDOW_H
