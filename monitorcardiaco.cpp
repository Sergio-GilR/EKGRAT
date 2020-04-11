#include "monitorcardiaco.h"
#include "ui_monitorcardiaco.h"

MonitorCardiaco::MonitorCardiaco(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MonitorCardiaco)
    ,m_settings(new SettingsDialog)
{
    ui->setupUi(this);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setPalette(pal);

    m_status = new QLabel();
    gridLayout = new QGridLayout(ui->widget);
    chart = new CChart(gridLayout);

    chart->showChart();
    chart->setRangeView(50,30);
    chart->setAxisY(0,5);
    chart->setRealTime(true);

    port=new QSerialPort(this);
    connect(port,&QSerialPort::readyRead,this,&MonitorCardiaco::readDataSerial);

    QTimer *Timer = new QTimer();
    Timer->setInterval(1);
    Timer->start();
    connect(Timer,&QTimer::timeout, this, &MonitorCardiaco::AddPoint);

    QTimer *Timer2 = new QTimer();
    Timer2->setInterval(50);
    Timer2->start();
    connect(Timer,&QTimer::timeout, chart, &CChart::showChart);

    posValue=0;
}

MonitorCardiaco::~MonitorCardiaco()
{
    delete ui;
}

void MonitorCardiaco::AddPoint()
{

    chart->setTitle("CardioRat");

    while(values.length() > posValue)
    {
        chart->addPoint(posValue,values.value(posValue));
        qDebug() << "a " <<values.value(posValue);
        posValue++;
    }
    chart->showChart();

}


bool MonitorCardiaco::openPortSerial()
{

    const SettingsDialog::Settings p = m_settings->settings();
    port->setPortName(p.name);
    port->setBaudRate(p.baudRate);
    port->setDataBits(p.dataBits);
    port->setParity(p.parity);
    port->setStopBits(p.stopBits);
    port->setFlowControl(p.flowControl);
    if (port->open(QIODevice::ReadWrite)) {

        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), port->errorString());

        showStatusMessage(tr("Open error"));
    }
    return false;

}

void MonitorCardiaco::closeSerialPort()
{
    if (port->isOpen())
        port->close();

    showStatusMessage(tr("Disconnected"));
}

void MonitorCardiaco::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MonitorCardiaco::readDataSerial()
{
    static QByteArray Data ;
    Data += port->readAll();
    int pSLinea = Data.indexOf(QByteArray("\n"));

    if(pSLinea>0)
    {
        do
        {
            float dato = Data.left(pSLinea).simplified().toInt()*0.004887585532746823069403714565;
            qDebug() << dato;
            values.append(dato);
            Data.remove(0, pSLinea+1);
            pSLinea = Data.indexOf('\n');
        }while(pSLinea>0);
    }
    else if(pSLinea == 0) Data.remove(0,1);

}

void MonitorCardiaco::OnErrorPort()
{

    QMessageBox::warning(this,tr("Error"),tr("Falla del puerto"));
}



void MonitorCardiaco::on_actionCerrar_triggered()
{
    this->close();
}

void MonitorCardiaco::on_actionAbrir_Puerto_triggered()
{
    openPortSerial();
}

void MonitorCardiaco::on_actionPuerto_triggered()
{
    m_settings->show();
}



void MonitorCardiaco::on_actionCerrar_Puerto_triggered()
{
    closeSerialPort();
}
