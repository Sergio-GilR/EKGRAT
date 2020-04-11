#include "cchart.h"

CChart::CChart(QGridLayout *_GridLayout,QChartView *parent) :
    QChartView(parent)
{
    GridLayout =_GridLayout;

    lineseries = new QLineSeries(); //Inicia nueva lista de puntos(QPointF)
    chart = new QChart();
    chart->addSeries(lineseries);

    axisX = new QValueAxis();
    axisX->setTickCount(5);
    //axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("Muestras ");

    chart->addAxis(axisX, Qt::AlignBottom);
    lineseries->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("Tensión[V]");
    chart->addAxis(axisY, Qt::AlignLeft);
    lineseries->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTheme(QChart::ChartThemeQt);

    RangeTimeViewPast=60;
    RangeTimeViewFuture=60;

    WindowWiht = 700;

}

QChartView* CChart::GetChart()
{
    return chartView;
}

void CChart::showChart()
{
    if(RealTime)setAxisX(Point-WindowWiht,Point+WindowWiht/2);
    chartView->setChart(chart);
    GridLayout->addWidget(GetChart());
}

void CChart::addPoint(int point,float valueY)
{
    static int limpiador;
    Point = point;
    lineseries->append(point,valueY);
    limpiador++;
    if(limpiador > WindowWiht*3) { lineseries->removePoints(0,WindowWiht);   limpiador-=WindowWiht;}
}

void CChart::clearData()
{
    lineseries->clear();
    chart->addSeries(lineseries);
    showChart();
}

bool CChart::getRealTime() const
{
    return RealTime;
}

void CChart::setRealTime(bool value)
{
    RealTime = value;
}


void CChart::setTitle(QString Title)
{
    chart->setTitle(Title);
}

void CChart::setLabel(QString Label)
{
    lineseries->setName(Label);
}

void CChart::setRangeView(const uint32_t &TimeViewPast,const uint32_t &TimeViewFuture)
{
    RangeTimeViewPast = TimeViewPast;
    RangeTimeViewFuture = TimeViewFuture;

}


void CChart::setAxisX(int min, int max)
{
    axisX->setRange(min,max);
}


void CChart::setAxisY(double min, double max)
{
    axisY->setRange(min, max);

}

void CChart::setmaxAxisY(double max)
{
    axisY->setMax(max);
}

void CChart::setminAxisY(double min)
{
    axisY->setMin(min);
}
