#ifndef MONITORCARDIACO_H
#define MONITORCARDIACO_H

#include <QMainWindow>
#include "cchart.h"
#include "settingsdialog.h"
#include <QLabel>
#include <QtSerialPort>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MonitorCardiaco; }
QT_END_NAMESPACE

class MonitorCardiaco : public QMainWindow
{
    Q_OBJECT

public:
    MonitorCardiaco(QWidget *parent = nullptr);
    ~MonitorCardiaco();
    bool openPortSerial();
    void AddPoint();

    void closeSerialPort();
    void showStatusMessage(const QString &message);


public slots:

    void readDataSerial();
    void OnErrorPort();


private slots:


    void on_actionCerrar_triggered();
    void on_actionAbrir_Puerto_triggered();
    void on_actionPuerto_triggered();
    void on_actionCerrar_Puerto_triggered();


private:
    Ui::MonitorCardiaco *ui;
    QList<float> values;
    int posValue;
    CChart *chart;
    CChart *chart2;

    QGridLayout *gridLayout;
    QGridLayout *gridLayout2;
    QLabel *m_status = nullptr;

    SettingsDialog *m_settings = nullptr;

    QSerialPort *port = nullptr;



};
#endif // MONITORCARDIACO_H
