#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windowsx.h"

#include    <QDateTime>
#include    <QString>

#include   <string>
#include <QStringList>
#include <QFileDialog>
#include <QDesktopServices>

#include <MemBufferCollection.h>
#include <MemBuffer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);

      remote_status=new QLabel("远程工控机未连接",this);
      remote_status->setMinimumWidth(250);

     plc_status=new QLabel("plc not connect",this);
     plc_status->setMinimumWidth(250);

      ui->statusBar->addWidget(remote_status);
      ui->statusBar->addWidget(plc_status);
      //相机
    img_temp=new QImage();// 防止第一次delete 失败

    m_pGrabber=new DShowLib::Grabber();

    fTimer=new QTimer(this);  //创建定时器
    fTimer->stop();
    fTimer->setInterval(1000);//设置定时周期,单位：毫秒
    connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout())); //关联定时器的信号与槽
    fTimer->start();

    fTimer2=new QTimer(this);  //创建定时器
    fTimer2->stop();
    fTimer2->setInterval(100);//设置定时周期,单位：毫秒
    connect(fTimer2,SIGNAL(timeout()),this,SLOT(on_timer2_timeout())); //关联定时器的信号与槽
    fTimer2->start();


    //表格数据

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            QTableWidgetItem *item;
            item=new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i,j,item);

        }
    }
    connect(ui->label,SIGNAL(mouseClicked(QPoint )),this,SLOT(on_mouseClicked(QPoint )));
}

MainWindow::~MainWindow()
{

    delete ui;
    delete m_pGrabber;

    delete img_temp;
    delete Client;
}

void MainWindow::on_openButton_released()
{
    /*a valid video format has to be set after a call to Grabber::openDev before startLive may be called.
     * Please refer to Grabber::setVideoFormat for details on setting a valid video format*/
 //   m_pGrabber->showDevicePage();


    //m_pGrabber->setVideoFormat("RGB32 (1920x1080)");//RGB32 (640x484) [Binning 4x]
    bool res=m_pGrabber->openDev("DFK 33GP006");
    if(!res)
    {
        QMessageBox::critical(this,"警告提示","打开相机失败，请检查相机连接！");
        return;
    }
    //m_pGrabber->setVideoFormat("RGB32 (640x484) [Binning 4x]");
    m_pGrabber->setVideoFormat("RGB32 (1920x1080)");
    m_pGrabber->setFPS(14.0L);
    qDebug()<<m_pGrabber->getVideoFormat().toString().c_str()<<endl;// //?????????????

    m_pGrabber->setDefaultWindowPosition(false);
    m_pGrabber->setWindowSize(ui->video->width(),ui->video->height());


    qDebug()<<"widget->width: "<<ui->video->width()<<endl;
    qDebug()<<"widget->height: "<<ui->video->height()<<endl;
    long x0,y0,width0,height0;
    m_pGrabber->getWindowPosition(x0,y0,width0,height0);
    qDebug()<<"window position: "<<x0<<" "<<y0<<" "<<width0<<" "<<height0<<endl;

   // m_pGrabber->setHWND(static_cast<HWND>((void *)ui->widget->winId()));
    m_pGrabber->setHWND(static_cast<HWND>((void *)ui->video->winId()));

    m_pGrabber->setOverlayBitmapPathPosition(ePP_NONE);
    pSink = FrameHandlerSink::create( eRGB32, 1 );
    pSink->setSnapMode( true ); //
    m_pGrabber->setSinkType(pSink);//A sink may only be set, if the image stream is in neither live mode, nor prepared mode.

   m_pGrabber->startLive(true);

}

void MainWindow::on_closeButton_released()
{

    QImage img_test=ui->video->grab(QRect(0,0,ui->video->width(),ui->video->height())).toImage();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(img_test));
    ui->label->show();
    if(m_pGrabber->isLive())
        m_pGrabber->stopLive();
    if(m_pGrabber->isDevOpen())
        m_pGrabber->closeDev();
}
void MainWindow::on_timer_timeout()
{
    //painter.drawPoint(QPoint(10,20));
    ui->dateTimeEdit->setDateTime( QDateTime::currentDateTime()); //读取当前日期时间
 //   ui->label->setPixmap(QPixmap::fromImage(*img));
 //   ui->label->show();

}
void MainWindow::on_timer2_timeout()
{
    //qDebug<<"on_timer2_timeout"<<endl;

}
void MainWindow::on_mouseClicked(QPoint point)
{
    if(img_temp->isNull())
    {
        QMessageBox::information(this,"提示信息","请先获取图像");
        return;
    }

    QImage temp;
    temp =img_temp->copy(0,0,img_temp->width(),img_temp->height());

    QPainter painter;

     QPen pen;
     painter.begin(&temp);
     pen.setColor(Qt::red);
     pen.setWidth(10);
     pen.setStyle(Qt::SolidLine);
     painter.setPen(pen);


     QFont font;
     font.setPointSize(30);
     font.setBold(true);
     painter.setFont(font);

    qDebug()<<"ratio: "<<x_ratio<<" : "<<y_ratio<<endl;
    qDebug()<<"on_mouseClicked"<<endl;
    qDebug()<<point.x()<<" "<<point.y()<<endl;
    qDebug()<<"pointno: "<<pointno<<endl;
   if(pointno<=9)//0-9
   {
       QPoint tp;
       tp.setX(point.x()*x_ratio);
       tp.setY(point.y()*y_ratio);

      ui->tableWidget->item(pointno,0)->setText(QString::number(tp.x()));
      ui->tableWidget->item(pointno,1)->setText(QString::number(tp.y()));

      if(point_vector.size()<10)
            point_vector.push_back(tp);

      for(auto it=point_vector.begin();it<point_vector.end();it++)
      {

          painter.drawPoint(*it);
          painter.drawText(*it,QString::number(it-point_vector.begin()+1));

      }
      ui->label->setPixmap(QPixmap::fromImage(temp));
      ui->label->show();

   }
   if(pointno<=9)
   {
       pointno++;
   }
   painter.end();

}
void MainWindow::on_Cancel_released()
{
    if(img_temp->isNull())
        return;

    QImage temp;
    temp= img_temp->copy(0,0,img_temp->width(),img_temp->height());

     QPainter painter;

     QPen pen;
     painter.begin(&temp);
     pen.setColor(Qt::red);
     pen.setWidth(10);
     pen.setStyle(Qt::SolidLine);
     painter.setPen(pen);


     QFont font;
     font.setPointSize(30);
     font.setBold(true);
     painter.setFont(font);

     if(point_vector.size()>0)
         point_vector.pop_back();

    if(pointno>0)
    {
        pointno--;
    }
    if(pointno<=9)
    {

        ui->tableWidget->item(pointno,0)->setText("");
        ui->tableWidget->item(pointno,1)->setText("");
        for(auto it=point_vector.begin();it<point_vector.end();it++)
        {

            painter.drawPoint(*it);
            painter.drawText(*it,QString::number(it-point_vector.begin()+1));

        }

        ui->label->setPixmap(QPixmap::fromImage(temp));
        ui->label->show();
    }
    painter.end();
}

void MainWindow::on_captureButton_released()
{
    if(!m_pGrabber->isLive())
    {
        QMessageBox::warning(this,"警告提示","相机未打开，请先打开相机");
        return;
    }
     pointno=0;
     point_vector.clear();
     pSink->snapImages(1);
   /* Changes this sink's operating mode between Grab and Snap mode.
    * In grab mode, all frames reaching the sink are presented to the frame filter or filter chain and then copied into the MemBufferCollection.
    * After that, the frameReady event of the GrabberListener is called.
    * In snap mode, snapImages or snapImagesAsync has to be called in order to trigger the image acquisition process.
    * If live mode has not been started, this method starts live mode before grabbing the image
    * and stops live mode afterward. Because starting live mode is a very time-consuming operation,
    * it is usually preferable to start live mode before calling snapImage more than once*/
//    m_pGrabber->stopLive();//// new add
    int cx=pSink->getLastAcqMemBuffer()->getSize().cx;
    int cy=pSink->getLastAcqMemBuffer()->getSize().cy;



     delete img_temp;// 防止第一次时为空，需要在初始化时img_temp=new Image();
    //QImage::mirrored(bool horizontal = false, bool vertical = true) const
    QImage temp=QImage(pSink->getLastAcqMemBuffer()->getPtr(),cx,cy,QImage::Format_RGB32);
    int width=temp.width();
    int height=temp.height();
    /*
    QPainter painter(&temp);
    QPointF center(width/qreal(2),height/qreal(2));
    painter.translate(center);
    painter.rotate(-270);
    painter.drawImage(QRect(0,0,width,height),temp,QRect(0,0,width,height));

    QMatrix matrix;
    matrix.rotate(180);
    QImage temp2=temp.transformed(matrix,Qt::FastTransformation);
    */

    //img_temp=new QImage(pSink->getLastAcqMemBuffer()->getPtr(),cx,cy,QImage::Format_RGB32);
     img_temp=new QImage(temp.mirrored(false,true));

    x_ratio=img_temp->size().width() ;
    x_ratio /= ui->label->size().width();

    y_ratio=img_temp->size().height() ;
    y_ratio /= ui->label->size().height();

    img_temp->scaled(ui->label->size(),Qt::KeepAspectRatio);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(*img_temp));
    ui->label->show();

}

void MainWindow::on_savetable_released()
{
  if(!img_temp->isNull())
  {
    delete img_temp;
      img_temp=new QImage();
  }
    qDebug()<<"save pic"<<endl;
    qDebug()<<QCoreApplication::applicationDirPath().toStdString().c_str()<<endl;

    ui->label->grab(QRect(0,0,ui->label->width(),ui->label->height())).save("test1234.jpg","jpg",100);


    //QDesktopServices::openUrl(QUrl("file://BLISS-G41MT-S2P/share", QUrl::TolerantMode));// windows 资源管理器打开目录

    QString curPath=QCoreApplication::applicationDirPath();
    //curPath="file:‪//BLISS-G41MT-S2P/share";
     QString aFilename=QFileDialog::getSaveFileName(this,"please select a file",curPath,"(text*.txt);;(all*.*)");

     //qDebug<<aFilename.toStdString()<<endl;
     if(aFilename.isEmpty())
     {
         qDebug()<<"aFilename.isEmpty()"<<endl;
         return;
     }
     //QFile aFile(aFilename);
     QFile aFile("//BLISS-G41MT-S2P/share/share1.txt");//ok
     if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate)))
     {
         qDebug()<<"aFile.open failure"<<endl;
         return;
     }
     QTextStream aStream(&aFile);
     QString str;
     QTableWidgetItem *cellItem;
     str="";
     for(int i=0;i<ui->tableWidget->rowCount();i++)
     {
         for(int j=0;j< ui->tableWidget->columnCount();j++)
         {
             cellItem=ui->tableWidget->item(i,j);
             if(cellItem == 0)// 表格为空
             {
                 str=str+" "+QString::asprintf("\t\t");
             }
             else
             {
                 str=str+cellItem->text()+QString::asprintf("\t\t");
             }

         }
         str=str+QString::asprintf("\n");
     }
     qDebug()<<str.toStdString().c_str()<<endl;
     aStream<<str;
     aFile.close();

}
bool MainWindow::plc_check(int res,const char* str)
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
void MainWindow::plc_init()
{


   Client=new TS7Client();
   const char*  Address= "192.168.1.10";
   int Rack=0;
   int Slot=1;
   int res=0;
   res=Client->ConnectTo(Address,Rack,Slot);
   if(plc_check(res,"connect ..."))
   {
       qDebug()<<"connect to plc ip:"<<Address<<" Rack: "<<Rack<<" Slot: "<<Slot<<endl;
   }

   TS7OrderCode info;
   res=Client->GetOrderCode(&info);
   if(plc_check(res,"Get order code"))
   {
      qDebug()<<"Order Code : "<<info.Code<<endl;
   }

   // Client->Disconnect();

}
/*
 * USINT 8
 * SINT 8
 * UINT 16
 * INT 16
 * REAL 32 4byte
 * LREAL 64
*/
short MainWindow::DB_read_short(const int& db,const int& offset)
{
   byte buffer[2];
   int res;
   res=Client->DBRead(db,offset,2,&buffer);//read 2 bytes
   plc_check(res,"DB_read_short");
   return (short)((buffer[0]<<8) | buffer[1]);
}
void MainWindow::DB_write_short(const int& db,const int& offset,const short& value)
{
   int res=0;
   byte buffer[2];
   buffer[0]=(byte)(value>>8);
   buffer[1]=(byte)(value&0x00ff);
   res=Client->DBWrite(db,offset,2,&buffer);//read 2 bytes
   plc_check(res,"DB_write_short");
}
bool MainWindow::DB_read_bit(const int& db,const int& offset,const int& bitnum=0)
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
void MainWindow::DB_write_bit(const int& db,const int& offset,const bool& value,const int& bitnum=0)
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
float MainWindow::DB_read_float(const int&  db,const int& offset)
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
void MainWindow::DB_write_float(const int& db,const int& offset,const float& value)
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
bool MainWindow::online_test(const QString& ip,const char* device)
{
    QProcess exc;
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString cmdstr=ip;//"ping 192.168.191.2";//ping 192.168.110.179  -n 2 -w 4000
    exc.start(cmdstr);//执行ping
    exc.waitForFinished(-1);//等待ping完成
    QString  outstr=codec->toUnicode(exc.readAll());//获取ping结果
    if((-1 !=outstr.indexOf("往返行程的估计时间")))
    {
        qDebug()<<device<<" on line "<<endl;
        return true;
    }
    else
    {
        qDebug()<<device<<" out line"<<endl;
        return false;
    }
}

void MainWindow::on_saveButton_released()
{
   online_test("ping 192.168.1.10","plc");
   plc_init();
   /* 实时位置 204 208 212 216 float*/
   /* 辐射点 300 314 318 312  316 318 210 f f f f i i f*/
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


