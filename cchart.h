#ifndef CCHART_H
#define CCHART_H

#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLineSeries>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QList>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

class CChart: public QChartView
{
    Q_OBJECT
public:
    explicit CChart(QGridLayout *_GridLayout,QChartView *parent = 0);

    QChartView* GetChart();
    void setTitle(QString Title);
    void setLabel(QString Label);
    void setRangeView(const uint32_t &TimeViewPast,const uint32_t &TimeViewFuture);
    void setAxisX(QDateTime min, QDateTime max);
    void setAxisX(int min, int max);


    void setAxisY(double min,double max);
    void setmaxAxisY(double max);
    void setminAxisY(double min);



    void showChart();
    void addPoint(QDateTime DateTime,float valueY);
    void addPoint(int DateTime,float valueY);
    void clearData();


    QChart *chart;


    bool getRealTime() const;
    void setRealTime(bool value);


private:
    QGridLayout *GridLayout;
    QChartView *chartView;
    QValueAxis *axisY;
    QValueAxis *axisX;
    QLineSeries *lineseries;

    int32_t RangeTimeViewPast;
    int32_t RangeTimeViewFuture;
    bool m_isTouching;
    bool RealTime;
    int Point;
    int WindowWiht;


};

#endif // CCHART_H
