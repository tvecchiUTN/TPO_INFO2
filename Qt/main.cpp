#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QSerialPort>
#include <QSerialPortInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowIcon(QIcon("iconoAsc.png"));
    w.show();
    return a.exec();
}
