#include "dialogpuerto.h"
#include "ui_dialogpuerto.h"
#include <QSerialPortInfo>

DialogPuerto::DialogPuerto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogPuerto)
{
    ui->setupUi(this);
    setWindowTitle("Configuración de Puerto Serie - Ascensor");

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->comboBoxPuertos->addItem(info.portName());
    }

    connect(ui->btnConectar, &QPushButton::clicked, this, &DialogPuerto::onConectarClicked);
}

DialogPuerto::~DialogPuerto()
{
    delete ui;
}

QString DialogPuerto::obtenerPuertoSeleccionado() const
{
    return ui->comboBoxPuertos->currentText();
}

void DialogPuerto::onConectarClicked()
{
    if (!ui->comboBoxPuertos->currentText().isEmpty()) {
        accept();
    }
}
