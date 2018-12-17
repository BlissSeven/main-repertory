#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <iostream>
using namespace  std;
int main(int argc, char *argv[])
{

  QString str("123");
  cout<< str.toStdString()<<endl;
    /*
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();

   */
}
