#include "qmywidget.h"
#include <QApplication>

#include <iostream>
#include <QElapsedTimer>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QmyWidget w;
    w.show();

    a.exec();


    return 0;
}
