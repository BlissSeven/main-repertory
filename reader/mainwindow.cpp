#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using std::endl;
using std::cout;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

   // showtxt("D:\\test.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::showtxt(QString path)
{
    QFile file(path);
    if(!file.exists())
        return false;
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
        return false;
   // QTextStream filestream(&file);
    //filestream.setAutoDetectUnicode(true);

    ui->textEdit->clear();
   // ui->textEdit->append(filestream.readAll());
    ui->textEdit->append(file.readAll());
    file.close();
    return true;
}
//当用户拖动文件到窗口部件上时候，就会触发dragEnterEvent事件
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    cout<<"dragEnterEvent"<<endl;
    //如果为文件，则支持拖放
   // if (event->mimeData()->hasFormat("text/uri-list"))
   //     event->acceptProposedAction();
    if(event->mimeData()->hasUrls())
    {
        cout<<"hasUrls"<<endl;
        event->acceptProposedAction();
    }
}

//当用户放下这个文件后，就会触发dropEvent事件
void MainWindow::dropEvent(QDropEvent *event)
{

    cout<<"dropEvent"<<endl;

    //注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    //如果想读取整个目录，则在不同的操作平台下，自己编写函数实现读取整个目录文件名
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    //往文本框中追加文件名
     ui->textEdit->clear();
    foreach(QUrl url, urls)
    {
        QString path = url.path();
        ui->textEdit->append(path);
        cout<<path.toStdString()<<endl;
        QFile file(path);
        if(!file.exists())
            return ;
        if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
            return ;
        ui->textEdit->append(file.readAll());
        file.close();  //*/
    }
}
