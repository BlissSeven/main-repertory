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
    mediaplayer=new QMediaPlayer();

    m_pGrabber=new DShowLib::Grabber();
/*
    pSink=FrameHandlerSink::create( eRGB32, 1 );
    pSink->setSnapMode(true);
    m_pGrabber->setSinkType(pSink);

   if(!m_pGrabber->prepareLive(false))
   {
      cout<<"Could not render the VideoFormat into a eRGB32 sink"<<endl;
   }

   pSink->getOutputFrameType(info);//Retrieve the output type and dimension of the handler sink
*/
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


    img=new QImage("C:\\Users\\bliss\\Desktop\\109951163657355652.jpg");
    //long width=m_pGrabber->getAcqSizeMaxX();
    //long height=m_pGrabber->getAcqSizeMaxY();
    //img=new QImage(width,height,QImage::Format_RGB32);
    img_temp=new QImage(img->copy(0,0,img->width(),img->height()));

    x_ratio=img->size().width() ;
    x_ratio /= ui->label->size().width();

    y_ratio=img->size().height() ;
    y_ratio /= ui->label->size().height();

    img->scaled(ui->label->size(),Qt::KeepAspectRatio);


    QPen pen;
    painter.begin(img);
    pen.setColor(Qt::red);
    pen.setWidth(10);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);


    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    painter.setFont(font);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(*img));
    ui->label->show();


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
    delete mediaplayer;
    delete ui;
    delete m_pGrabber;
//    delete Client;
}

void MainWindow::on_openButton_released()
{
    /*a valid video format has to be set after a call to Grabber::openDev before startLive may be called.
     * Please refer to Grabber::setVideoFormat for details on setting a valid video format*/
 //   m_pGrabber->showDevicePage();


    //m_pGrabber->setVideoFormat("RGB32 (1920x1080)");//RGB32 (640x484) [Binning 4x]
    m_pGrabber->openDev("DFK 33GP006");
    m_pGrabber->setVideoFormat("RGB32 (640x484) [Binning 4x]");
    m_pGrabber->setFPS(14.0L);
    cout<<m_pGrabber->getVideoFormat().toString()<<endl;
  {
   m_pGrabber->setDefaultWindowPosition(false);
    m_pGrabber->setWindowSize(ui->video->width(),ui->video->height());
  }

    cout<<"widget->width: "<<ui->video->width()<<endl;
    cout<<"widget->height: "<<ui->video->height()<<endl;
    long x0,y0,width0,height0;
    m_pGrabber->getWindowPosition(x0,y0,width0,height0);
    cout<<"window position: "<<x0<<" "<<y0<<" "<<width0<<" "<<height0<<endl;

   // m_pGrabber->setHWND(static_cast<HWND>((void *)ui->widget->winId()));
    m_pGrabber->setHWND(static_cast<HWND>((void *)ui->video->winId()));
// /*
   {
    m_pGrabber->setOverlayBitmapPathPosition(ePP_NONE);
    pSink = FrameHandlerSink::create( eRGB32, 1 );
    pSink->setSnapMode( true ); //可有可无
     m_pGrabber->setSinkType(pSink);//A sink may only be set, if the image stream is in neither live mode, nor prepared mode.
/*
      if(!m_pGrabber->prepareLive(false))
      {
         cout<<"Could not render the VideoFormat into a eRGB32 sink"<<endl;
      }

      pSink->getOutputFrameType(info);//Retrieve the output type and dimension of the handler sink

      long width=m_pGrabber->getAcqSizeMaxX();
      long height=m_pGrabber->getAcqSizeMaxY();

        snapimage=new QImage (width,height,QImage::Format_RGB32);
        cout<<"info.buffersize: "<<info.buffersize<<endl;
        cout<<"width: "<<width<<endl;
        cout<<"height: "<<height<<endl;
       BYTE* pBuf[1];
      //pBuf[0]=new BYTE[info.buffersize];
       pBuf[0]=snapimage->bits();

      tMemBufferCollectionPtr pCollection = MemBufferCollection::create( info, 1, pBuf );
      //pCollection->getFrameSize();
      if( pCollection == 0 || !pSink->setMemBufferCollection( pCollection ) )// 是否在startlive之前？？？
      {
          std::cerr << "Could not set the new MemBufferCollection, because types do not match.";
      }// */
   } //*/
 //  pSink->setSnapMode( false );
   m_pGrabber->startLive(true);

}

void MainWindow::on_closeButton_released()
{
    /*
    QImage * imgxx=new QImage(3,3,QImage::Format_RGB32);
    for(int i=0;i<imgxx->width();i++)
    {
         for(int j=0;j<imgxx->height();j++)
         {

             imgxx->setPixel(i,j,qRgb(rand()*255,rand()*255,rand()*255));
         }
    }*/

    QImage img_test=ui->video->grab(QRect(0,0,ui->video->width(),ui->video->height())).toImage();
    img_test.save("img_test.jpg","jpg",100);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(img_test));
    ui->label->show();

    m_pGrabber->stopLive();
    m_pGrabber->closeDev();
    //*/
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
    //cout<<"on_timer2_timeout"<<endl;

}
void MainWindow::on_mouseClicked(QPoint point)
{
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

    cout<<"ratio: "<<x_ratio<<" : "<<y_ratio<<endl;
    cout<<"on_mouseClicked"<<endl;
    cout<<point.x()<<" "<<point.y()<<endl;
    cout<<"pointno: "<<pointno<<endl;
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

}
void MainWindow::on_Cancel_released()
{
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
}

void MainWindow::on_captureButton_released()
{
  /* {
        //init
       m_pSaveImageFilter=FilterLoader::createFilter("grab img");
       if( m_pSaveImageFilter == NULL)
       {

          cout<<"m_pSaveImageFilter is null"<<endl;
           //MessageBox("Failed to load the \"Save Image\" frame filter!","Error",MB_OK|MB_ICONEXCLAMATION);
       }
       else
       {

           // The frame filter has been loaded successfully. Now it should be added
                   // to the Grabber object.
           if( !m_pGrabber->setDeviceFrameFilters( m_pSaveImageFilter.get()) )
           {
               cout<<"Failed to add the \"Save Image\" frame filter to the grabber"<<endl;
               //MessageBox("Failed to add the \"Save Image\" frame filter to the grabber!","Error",MB_OK|MB_ICONEXCLAMATION);
           }
       }
       // button event
   if( m_pSaveImageFilter != NULL && m_pGrabber->isDevValid() && m_pGrabber->isLive())
       {
          static  int m_iImageCounter=0;
           char szImageFileName[MAX_PATH+1];
           m_iImageCounter++;
           sprintf(szImageFileName,"Image%03d.jpg",m_iImageCounter);

           m_pSaveImageFilter->beginParamTransfer();
           // Setting the parameter "ImageName" of the filter causes the filter to
           // snap the next incoming image and save it to a file.

           m_pSaveImageFilter->setParameter("ImageName",std::string(szImageFileName));
           //m_pSaveImageFilter->getData("ImageName",);
           m_pSaveImageFilter->endParamTransfer();
       }
   } */
   // /*
//   m_pGrabber->stopLive();//一定有
//    m_pGrabber->closeDev();
//    m_pGrabber->showDevicePage();

     long width=m_pGrabber->getAcqSizeMaxX();
     long height=m_pGrabber->getAcqSizeMaxY();
/*
   m_pGrabber->setOverlayBitmapPathPosition(ePP_NONE);

   pSink = FrameHandlerSink::create( eRGB32, 1 );
    pSink->setSnapMode( true ); //可有可无
    m_pGrabber->setSinkType(pSink);//A sink may only be set, if the image stream is in neither live mode, nor prepared mode.

     if(!m_pGrabber->prepareLive(false))
     {
        cout<<"Could not render the VideoFormat into a eRGB32 sink"<<endl;
     }

     pSink->getOutputFrameType(info);//Retrieve the output type and dimension of the handler sink
    // */
  /*
     QImage img2(width,height,QImage::Format_RGB32);
     cout<<"info.buffersize: "<<info.buffersize<<endl;
      cout<<"width: "<<width<<endl;
      cout<<"height: "<<height<<endl;
    BYTE* pBuf[1];
   //pBuf[0]=new BYTE[info.buffersize];
    pBuf[0]=img2.bits();

   tMemBufferCollectionPtr pCollection = MemBufferCollection::create( info, 1, pBuf );
   //pCollection->getFrameSize();
   if( pCollection == 0 || !pSink->setMemBufferCollection( pCollection ) )// 是否在startlive之前？？？
   {
       std::cerr << "Could not set the new MemBufferCollection, because types do not match.";
   }
   */
//   m_pGrabber->startLive(true);// 一定有Specifies whether the image stream is displayed while the grabber is in live mode.
  // pSink->setSnapMode( true );
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
    QImage img_test=QImage(pSink->getLastAcqMemBuffer()->getPtr(),width,height,QImage::Format_RGB32);

    cout<<"cx: "<<cx<<" cy: "<<cy<<endl;


    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(img_test));
    ui->label->show();
  // */
}

void MainWindow::on_savetable_released()
{

    cout<<"save pic"<<endl;
    cout<<QCoreApplication::applicationDirPath().toStdString()<<endl;
    //img->save(QCoreApplication::applicationDirPath()+"test123.jpg","jpg");
    ui->label->grab(QRect(0,0,ui->label->width(),ui->label->height())).save(QCoreApplication::applicationDirPath()+"test123.jpg","jpg",100);


    //QDesktopServices::openUrl(QUrl("file://BLISS-G41MT-S2P/share", QUrl::TolerantMode));// windows 资源管理器打开目录

    QString curPath=QCoreApplication::applicationDirPath();
    curPath="file:‪//BLISS-G41MT-S2P/share";
     QString aFilename=QFileDialog::getSaveFileName(this,"please select a file",curPath,"(text*.txt);;(all*.*)");

     //cout<<aFilename.toStdString()<<endl;
     if(aFilename.isEmpty())
     {
         cout<<"aFilename.isEmpty()"<<endl;
         return;
     }
     //QFile aFile(aFilename);
     QFile aFile("//BLISS-G41MT-S2P/share/share1.txt");//ok
     if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text|QIODevice::Truncate)))
     {
         cout<<"aFile.open failure"<<endl;
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
     cout<<str.toStdString()<<endl;
     aStream<<str;
     aFile.close();

}
bool MainWindow::plc_check(int res,const char* str)
{
    if(res==0)
    {
        cout<<str<<" opertion ok!"<<endl;
    }
    else
    {
        cout<<str<<"opertion failure!: error code: "<<res<<endl;
    }
    return res==0;
}
void MainWindow::plc_init()
{


   Client=new TS7Client();
   const char*  Address= "192.168.1.1";
   int Rack=0;
   int Slot=0;
   int res=0;
   res=Client->ConnectTo(Address,Rack,Slot);
   if(plc_check(res,"connect ..."))
   {
       cout<<"connect to plc ip:"<<Address<<" Rack: "<<Rack<<" Slot: "<<Slot<<endl;
   }

   TS7OrderCode info;
   res=Client->GetOrderCode(&info);
   if(plc_check(res,"Get order code"))
   {
      cout<<"Order Code : "<<info.Code<<endl;
   }

    Client->Disconnect();

}
/*
 * USINT 8
 * SINT 8
 * UINT 16
 * INT 16
 * REAL 32 4byte
 * LREAL 64
*/
int MainWindow::DB_read_int(const int& db,const int& offset)
{
   byte buffer[2];
   int res;
   res=Client->DBRead(db,offset,2,&buffer);//read 2 bytes
   plc_check(res,"read db");
   return (int)((buffer[0]<<8) | buffer[1]);
}
void MainWindow::DB_write_int(const int& db,const int& offset,const int& value)
{
   int res=0;
   byte buffer[2];
   buffer[0]=(byte)(value>>8);
   buffer[1]=(byte)(value&0x00ff);
   res=Client->DBWrite(db,offset,2,&buffer);//read 2 bytes
   plc_check(res,"write db");
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
    res=Client->DBWrite(db,offset,4,&buffer);//read 2 bytes
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
        cout<<device<<" on line "<<endl;
        return true;
    }
    else
    {
        cout<<device<<" out line"<<endl;
        return false;
    }
}

void MainWindow::on_saveButton_released()
{

}


