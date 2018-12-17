#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPoint>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QTextCodec>

#include <iostream>
#include <string>


using std::endl;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_mouseClicked(QPoint point);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
