#include "wave.h"

Wave::Wave(QWidget *parent) :
    QChartView(parent),
    chart(new Chart),
    m_isTouching(false)
{
    series = new QSplineSeries();
    series->setUseOpenGL(true);
    //connect(series,SIGNAL(hovered()),this,SLOT(onSeriesHovered()));

    chart->addSeries(series);
    chart->setAcceptHoverEvents(true);
    chart->legend()->hide();

    axisX = new QValueAxis;
    axisY = new QValueAxis;

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setRubberBand(QChartView::RectangleRubberBand);
    setRubberBand(QChartView::RectangleRubberBand);

}

bool Wave::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        m_isTouching = true;
        chart->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void Wave::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void Wave::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void Wave::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView::mouseReleaseEvent(event);
}

void Wave::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart->zoomIn();
        break;
    case Qt::Key_Minus:
        chart->zoomOut();
        break;
    case Qt::Key_Left:
        chart->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
QValueAxis *Wave::getAxis(Qt::Orientation orientation){
    if(orientation == Qt::Horizontal){
        return axisX;
    }
    if(orientation == Qt::Vertical){
        return axisY;
    }
    return nullptr;
}
QLineSeries *Wave::getSeries(){
    return series;
}
void Wave::setSeries(const QVector<QPointF> &points){
    series->replace(points);
}

Wave::~Wave(){

}
