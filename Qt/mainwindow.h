#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//Necesito incluir la clase QSerialPort para usar el objeto puerto serie
#include <QSerialPort>
//Necesito incluir la clase QSerialPortInfo para acceder al listado
//de puerto series que posee el sistema operativo
#include <QSerialPortInfo>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Modificamos el constructor para que reciba el nombre del puerto serie
    MainWindow(QString puertoSerial, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //Declaro aqui el objeto que utilizaré para comunicarme
    //RECORDAR agregar la linea QT += serialport en el .pro
    QSerialPort *m_serial = nullptr;
};
#endif // MAINWINDOW_H
