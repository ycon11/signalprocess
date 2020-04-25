#ifndef WAVE_H
#define WAVE_H

#include<QWidget>
#include<QtCharts/QLineSeries>
#include<QPainter>
#include<QEvent>
#include<QToolTip>
#include<QMouseEvent>
#include<QValueAxis>
#include <QSplineSeries>
#include <QtWidgets/QRubberBand>
#include <QtCharts/QChartView>
#include"chart.h"


QT_CHARTS_USE_NAMESPACE

//![1]
class Wave : public QChartView
    //![1]
{
public:
    Wave(QWidget* parent = nullptr);
    QValueAxis* getAxis(Qt::Orientation orientation);
    QLineSeries* getSeries();
    void setSeries(const QVector<QPointF>& points);
    ~Wave();
    //![2]
protected:
    bool viewportEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    //![2]

private:
    QValueAxis* axisX;
    QValueAxis* axisY;
    Chart* chart;
    QSplineSeries* series;
    bool m_isTouching;
};
#endif
