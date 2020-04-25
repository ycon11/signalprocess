#ifndef DATAIODEVICE_H
#define DATAIODEVICE_H


#include <iostream>

#include <QIODevice>
#include <QPointF>
#include <QVector>
#include <QtCharts/QChartGlobal>
#include <QDebug>
#include<QByteArray>
#include <itpp/itbase.h>
#include <itpp/itsignal.h>
#include <string>
#include"dataacquire.h"
#include"signalprocess.h"

using namespace itpp;
extern  long  SAMPLE_COUNT;

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
class DataIODevice:public QIODevice
{
    Q_OBJECT
public:
    static const int sampleCount = 2500;
    explicit DataIODevice(QObject *parent = nullptr);
    void addXYSeries(QXYSeries *series,QVector<double> (*pFunc)(const QVector<double> &,int));
    void setFile(QFile *file);
    QVector<double> getData() const ;
    bool blockBufferSignal(bool isBlock);

public:
    bool open(QIODevice::OpenMode mode) override;
    qint64 writeBuffer(const QByteArray &byteArray,qint64 maxSize);
    qint64 readBuffer(char *data, qint64 maxSize);
    QByteArray readBuffer(qint64 maxSize);
    void close() override;
protected slots:
    void writeData(qint64 maxSize);
protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;
    qint64 writeData(QByteArray data, qint64 maxSize);
    friend class NetDataAcquire;
    friend class FileDataAcquire;
    friend class NIDeviceAcquire;
signals:
    void readyReadBuffer(qint64 maxSize);
private:
    typedef QVector<double>(*pSignalFunc)(const QVector<double>&v,int);
    QList<QXYSeries *> m_seriesList;
    QList<pSignalFunc> m_signalFuncList;
    QBuffer m_buffer;
    QVector<QPointF> m_pointBuffer;
    QVector<double> m_xData;
    QVector<double> m_yData;
    QFile *m_file;
};

#endif // DATAIODEVICE_H
