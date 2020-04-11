#include "monitorcardiaco.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MonitorCardiaco w;


    w.show();
    return a.exec();
}
