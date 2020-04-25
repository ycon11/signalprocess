#include "dataiodevice.h"
#include <QtCharts/QXYSeries>
long SAMPLE_COUNT = 8000;
DataIODevice::DataIODevice(QObject *parent) :
    QIODevice(parent)
{
    connect(this,SIGNAL(readyReadBuffer(qint64)),this,SLOT(writeData(qint64)));

}
void DataIODevice::addXYSeries(QXYSeries *series,pSignalFunc pF){
    m_seriesList<<series;
    m_signalFuncList<<pF;
}

void DataIODevice::setFile(QFile *file){
    m_file = file;
}


bool DataIODevice::open(QIODevice::OpenMode mode){
    return m_buffer.open(mode);
}


qint64 DataIODevice::writeBuffer(const QByteArray &byteArray,qint64 maxSize){
     qint64 len = m_buffer.write(byteArray);
     if(len > 0){
        emit readyReadBuffer(maxSize);
     }
     return len;
}

qint64 DataIODevice::readBuffer(char *data, qint64 maxSize){
    return m_buffer.read(data,maxSize);
}
QByteArray DataIODevice::readBuffer(qint64 maxSize){
    return m_buffer.read(maxSize);
}

void DataIODevice::close(){
    m_buffer.close();
}

void DataIODevice::writeData(qint64 maxSize){
    writeData(m_buffer.data(),maxSize);
}


bool DataIODevice::blockBufferSignal(bool isBlock){

    return this->blockSignals(isBlock);
}

qint64 DataIODevice::writeData(QByteArray data, qint64 maxSize)
{
    if (m_pointBuffer.isEmpty()) {
        m_pointBuffer.reserve(sampleCount);
        for (int i = 0; i < sampleCount; ++i){
            //m_pointBuffer.append(QPointF(i, 0));
            m_xData.append(i);
            m_yData.append(0.0);
        }
    }
    int start = 0;
    const int availableSamples = static_cast<int>(maxSize);
    if (availableSamples < sampleCount) {
        start = sampleCount - availableSamples;
        for (int s = 0; s < start; s++){
            //m_pointBuffer[s].setY(m_pointBuffer.at(s + availableSamples).y());
            m_yData[s] = m_yData[s + availableSamples];
        }
    }
    QDataStream out(&data,QIODevice::ReadOnly);
    for (int s = start; s < sampleCount; ++s){
        double val;
        out>>val;
        m_yData[s] = val;
       // m_pointBuffer[s].setY(val);
    }
    for(int i = 0;i<m_seriesList.size();i++){
        if(m_signalFuncList[i]==nullptr){
            m_pointBuffer = zipVec2QVecPointF(m_xData,m_yData);
            m_seriesList[i]->replace(m_pointBuffer);
        }else{
            QVector<double> xk;
            for(int i = 0;i<12000/2;i++){
                xk.append(i);
            }
            auto pf = m_signalFuncList[i];
            auto YK = pf(m_yData,m_yData.size());
            auto points = zipVec2QVecPointF(xk,YK);
            m_seriesList[i]->replace(points);
        }

    }
    return maxSize;
}
qint64 DataIODevice::readData(char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}
qint64 DataIODevice::writeData(const char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}
