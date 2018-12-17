#ifndef MYLABEL_H
#define MYLABEL_H


#include <iostream>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

using std::cout;
using std::endl;


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
    void mouseClicked(QPoint point);// event emit signals,signals connect slot
//    void mouseReleased(QPoint point);
private:

};
#endif // MYLABEL_H
