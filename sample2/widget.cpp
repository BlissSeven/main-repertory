#include "widget.h"
#include "ui_widget.h"

Widget2::Widget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget3)
{
    ui->setupUi(this);
}

Widget2::~Widget2()
{
    delete ui;
}
