#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->radioButton,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(ui->radioButton_3,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_checkBox_clicked(bool checked)
{

   QFont font=ui->label->font();
   font.setUnderline(checked);
   ui->label->setFont(font);
}

void Dialog::on_checkBox_2_clicked(bool checked)
{
    QFont font=ui->label->font();
    font.setItalic(checked);
    ui->label->setFont(font);
}

void Dialog::on_checkBox_3_clicked(bool checked)
{
    QFont font=ui->label->font();
    font.setBold(checked);
    ui->label->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette plet=ui->label->palette();
    if(ui->radioButton->isChecked())
    {
        plet.setColor(QPalette::WindowText,Qt::blue);
    }
    else if(ui->radioButton_2->isChecked())
    {
        plet.setColor(QPalette::WindowText,Qt::black);
    }
    else if(ui->radioButton_3->isChecked())
    {
        plet.setColor(QPalette::WindowText,Qt::red);
    }
    else
         plet.setColor(QPalette::WindowText,Qt::red);

    ui->label->setPalette(plet);
}

void Dialog::on_radioButton_clicked(bool checked)
{
//     QPalette plet=ui->label->palette();
//     if(checked)
//     {
//         plet.setColor(QPalette::WindowText,Qt::white);
//     }
//     else
//         plet.setColor(QPalette::WindowText,Qt::white);

//     ui->label->setPalette(plet);
}
