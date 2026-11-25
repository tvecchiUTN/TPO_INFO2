#include "mainwindow.h"
#include "dialogpuerto.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Instanciamos la ventana de selección de puerto primero
    DialogPuerto dialogoPuerto;

    // 2. Ejecutamos el diálogo de forma modal (.exec() congela la ejecución hasta que se cierre)
    if (dialogoPuerto.exec() == QDialog::Accepted) {
        // Obtenemos el puerto elegido por el usuario
        QString puertoElegido = dialogoPuerto.obtenerPuertoSeleccionado();

        // 3. Si se eligió correctamente, abrimos la ventana principal del ascensor pasándole el puerto
        MainWindow w(puertoElegido);
        w.show();

        return a.exec(); // Arranca el bucle principal de la app del ascensor
    }

    // Si el usuario cerró la ventana de puertos sin conectar, se cierra el programa
    return 0;
}
