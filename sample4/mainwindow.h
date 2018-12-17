#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_actBold_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    void initsignalslots();
    void on_spinboxfontsize_valuechanged(int a);

    void on_combofont_currentindexchanged(const QString & arg);

private:
    Ui::MainWindow *ui;
    //add
    QLabel * flabcurfile;  //状态栏显示当前文件
    QProgressBar* progressbar;//状态栏进度条
    QSpinBox* spinfontsize;//字体大小
    QFontComboBox* combofont;//字体名称
    void initUI();

};

#endif // MAINWINDOW_H
