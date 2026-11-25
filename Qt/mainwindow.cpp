#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPolygonF>
#include <QRegion>
#include <QMessageBox>

MainWindow::MainWindow(QString puertoSerial, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setWindowTitle("Control de Ascensor - Puerto: " + puertoSerial);

    m_serial = new QSerialPort(this);
    m_serial->setPortName(puertoSerial);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Puerto serie abierto correctamente:" << puertoSerial;
    } else {
        qDebug() << "Error al abrir" << puertoSerial << ":" << m_serial->errorString();
        QMessageBox::warning(this, "Error de puerto serie",
                             "No se pudo abrir " + puertoSerial + ":\n" + m_serial->errorString());
    }
////////////////////////////////  BOTONERA DE MUSICA ///////////////////////
    QPolygonF trianguloDerecho;
    trianguloDerecho << QPointF(0,0)    // Punta superior (centro X, arriba Y)
                    << QPointF(0,20)    // Esquina inferior izquierda
                    << QPointF(20,10);   // Esquina inferior derecha

    // Creamos la región (máscara) y se la aplicamos al botón
    QRegion regionDerecho(trianguloDerecho.toPolygon());
    ui->pushButton_7->setMask(regionDerecho);

    QPolygonF trianguloIzquierdo;
    trianguloIzquierdo << QPointF(20,0)    // Punta superior (centro X, arriba Y)
                     << QPointF(20,20)    // Esquina inferior izquierda
                     << QPointF(0,10);   // Esquina inferior derecha

    // Creamos la región (máscara) y se la aplicamos al botón
    QRegion regionIzquierdo(trianguloIzquierdo.toPolygon());
    ui->pushButton_9->setMask(regionIzquierdo);

    // Habilitar para que el botón de pausa/play funcione como un interruptor
    ui->pushButton_8->setCheckable(true);

    // Texto inicial (Play)
    ui->pushButton_8->setText("▶");

    // Conectar la señal toggled (se dispara cada vez que cambia su estado de presionado/liberado)
    connect(ui->pushButton_8, &QPushButton::toggled, this, [=](bool checked){
        if (checked) {
            // Cuando está "hundido" / activado
            ui->pushButton_8->setText("⏸"); // Cambia a pausa
            qDebug() << "Música de ascensor pausada.";
            // ACÁ LLAMAS A TU FUNCIÓN DE PAUSAR LA MÚSICA
        } else {
            // Cuando vuelve a su estado normal
            ui->pushButton_8->setText("▶"); // Cambia a play
            qDebug() << "Reproduciendo música de ascensor...";
            // ACÁ LLAMAS A TU FUNCIÓN DE REPRODUCIR LA MÚSICA
        }
    });
//////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///////////////////////MOVIMIENTO DEL ASCENSOR/////////////////////////
    // --- CUANDO EL ASCENSOR SUBE ---
    // Enciende la flecha de arriba y apaga la de abajo
    ui->lblFlechaArriba->setStyleSheet("background-color: #00FF66; color: black; border-radius: 4px; font-weight: bold;"); // Luz verde encendida
    ui->lblFlechaAbajo->setStyleSheet("background-color: #222222; color: #444444; border-radius: 4px;"); // Apagada

    // --- CUANDO EL ASCENSOR BAJA ---
    // Enciende la flecha de abajo y apaga la de arriba
    ui->lblFlechaArriba->setStyleSheet("background-color: #222222; color: #444444; border-radius: 4px;"); // Apagada
    ui->lblFlechaAbajo->setStyleSheet("background-color: #00FF66; color: black; border-radius: 4px; font-weight: bold;"); // Luz verde encendida

    // --- CUANDO EL ASCENSOR LLEGA A DESTINO (Detenido) ---
    // Ambas apagadas
    ui->lblFlechaArriba->setStyleSheet("background-color: #222222; color: #444444; border-radius: 4px;");
    ui->lblFlechaAbajo->setStyleSheet("background-color: #222222; color: #444444; border-radius: 4px;");


    // --- ESTADO APAGADO (Triángulo gris oscuro) ---
    QString estiloApagado = "background-color: transparent; color: #3a3a3a; font-size: 48px;";

    // --- ESTADO ENCENDIDO (Triángulo verde neón brillante) ---
    QString estiloEncendido = "background-color: transparent; color: #00ff66; font-size: 48px;";

    // --- ESTADO INICIAL / REPOSO ---
    ui->lblFlechaArriba->setStyleSheet(estiloApagado);
    ui->lblFlechaAbajo->setStyleSheet(estiloApagado);

    //texto inicial del piso actual en reposo
    ui->label_2->setText("Piso N°PB");

    ///////////////////////////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    if (m_serial && m_serial->isOpen()) {
        m_serial->close();
    }
    delete ui;
}
