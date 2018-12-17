#ifndef MYLABEL_HPP
#define MYLABEL_HPP

#include <iostream>

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>


using std::cout;
using std::endl;
using std::string;

namespace Ui {
class myLabel;
}
class myLabel:public QLabel
{
    Q_OBJECT
public:

    //explicit myLabel(const QString &text,QWidget *parent=0);
    myLabel(QWidget* parent)
        :QLabel(parent){}

    ~myLabel(){}
//private slots:
protected:
    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void mouseClicked(QPoint point);
//    void mouseReleased(QPoint point);
private:

};

#endif // MYLABEL_HPP
