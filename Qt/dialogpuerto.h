#ifndef DIALOGPUERTO_H
#define DIALOGPUERTO_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogPuerto;
}

class DialogPuerto : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPuerto(QWidget *parent = nullptr);
    ~DialogPuerto();

    QString obtenerPuertoSeleccionado() const;

private slots:
    void onConectarClicked();

private:
    Ui::DialogPuerto *ui;
};

#endif // DIALOGPUERTO_H
