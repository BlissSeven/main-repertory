#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    initsignalslots();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initUI()
{
    flabcurfile=new QLabel();
    flabcurfile->setMinimumWidth(150);
    flabcurfile->setText("当前文件");
    ui->statusBar->addWidget(flabcurfile);//添加到状态栏

    progressbar=new QProgressBar();
    progressbar->setMaximumWidth(200);
    progressbar->setMinimum(5);
    progressbar->setMaximum(50);
    progressbar->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressbar);//添加到状态栏

    spinfontsize=new QSpinBox;
    spinfontsize->setMinimum(5);
    spinfontsize->setMaximum(50);
    spinfontsize->setValue(ui->textEdit->font().pointSize());
    spinfontsize->setMinimumWidth(50);
    ui->mainToolBar->addWidget(new QLabel("字体大小"));
    ui->mainToolBar->addWidget(spinfontsize);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(new QLabel("字体"));

    combofont=new QFontComboBox();
    combofont->setMinimumWidth(150);
    ui->mainToolBar->addWidget(combofont);

    setCentralWidget(ui->textEdit);
}

void MainWindow::on_actBold_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    if(checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);

    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt=ui->textEdit->currentCharFormat();
    ui->actItalic->setChecked(fmt.fontItalic());
    ui->actBold->setChecked(fmt.font().bold());
    ui->actUnderline->setChecked(fmt.fontUnderline());
}
void MainWindow::initsignalslots()
{
    //connect(actBold,SIGNAL(triggered(bool)),this,SLOT(on_actBold_triggered(bool)));
    connect(spinfontsize,SIGNAL(valueChanged(int)),this,SLOT(on_spinboxfontsize_valuechanged(int)));
    connect(combofont,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_combofont_currentindexchanged(const QString&)));

}
void MainWindow::on_spinboxfontsize_valuechanged(int a)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(a);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressbar->setValue(a);
}

void MainWindow::on_combofont_currentindexchanged(const QString & arg)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}
