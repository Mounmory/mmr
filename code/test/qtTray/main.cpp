#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");    //获取系统编码
    //QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
