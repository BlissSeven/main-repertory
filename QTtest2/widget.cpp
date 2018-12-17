#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

//this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    //this->setFixedSize(400,400);
    this->setGeometry(200,200,600,600);
    this->setFixedSize(600,600);
   this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);//隐藏边框后还想要把该界面至于其他界面的顶层

    ui->setupUi(this);
    connect(ui->label,SIGNAL(mouseClicked(QPoint )),this,SLOT(on_mouseClicked(QPoint )));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_mouseClicked(QPoint point)
{
    QPixmap pic("C:\\Users\\bliss\\Desktop\\109951163657355652.jpg");
    pic.scaled(ui->label->size(),Qt::KeepAspectRatio);
   // QString dirname=QFileDialog::getExistingDirectory(this,"select dir");
   // qDebug()<<"dir name: "<<dirname<<endl;

    QStringList file_name = QFileDialog::getOpenFileNames(this,"pls select two files",".","*.*");
    if(file_name.size() !=2)
    {
        QMessageBox::critical(this,"warning","please select two files");
        return ;
    }
    qDebug()<<"file name 1: "<<file_name[0]<<endl;
    qDebug()<<"file name 2: "<<file_name[1]<<endl;
    QPixmap img;
    QString txtfile;
    if(file_name[0].endsWith("txt",Qt::CaseInsensitive) && file_name[1].endsWith("jpg",Qt::CaseInsensitive))
    {
        img=QPixmap(file_name[1]);
        txtfile=file_name[0];
    }
    else if(file_name[1].endsWith("txt",Qt::CaseInsensitive) && file_name[0].endsWith("jpg",Qt::CaseInsensitive))
    {
        img=QPixmap(file_name[0]);
        txtfile=file_name[1];
    }
    else
    {
        QMessageBox::critical(this,"warning","please select one txt files,one jpg picture");
        return ;
    }
     qDebug()<<"txt file is "<<txtfile<<endl;


     QString newtxtfile= QString::fromStdString(string("G:\\新建文件夹啊\\123.txt").data());//偶数中文 S
     qDebug()<<"newtxtfile: "<<newtxtfile<<endl;


    //QFile::exists
     if(QFile::exists(newtxtfile))
     {
         QFile::remove(newtxtfile);
     }
     if(!QFile::copy(txtfile,newtxtfile))
     {
        QMessageBox::critical(this,"warning","copy txt file error,please retry");
     }



    ui->label->setPixmap(img);
}
