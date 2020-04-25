#ifndef DATAACQUIRE_H
#define DATAACQUIRE_H
#include<QVector>
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QDataStream>
#include<QStringLiteral>
#include<QMessageBox>
#include<QIODevice>
#include<QTime>
#include<QBuffer>
#include<QAudioInput>
#include<QByteArray>
#include<QtMath>
#include<ctime>
#include<QThread>
#include"dataiodevice.h"
class DataIODevice;
//从网口获得数据
class NetDataAcquire:public QThread{
    Q_OBJECT
public:
    explicit NetDataAcquire(long fs,DataIODevice *ioDevice,QObject *parent = nullptr);
    void netConnect() ;
    void run();
    void stop();
private:
    QBuffer m_buffer;
    long m_fs;
    bool m_isStop = true;
    DataIODevice *m_ioDevice;
};
//从文件获得数据
class FileDataAcquire:public QThread{
    Q_OBJECT
public:
    explicit FileDataAcquire(const QString &path,long fs,long bufferSize,DataIODevice *device,QObject *parent = nullptr);
    void readFile(const QString &filePath);
    void run() override;
    void stop();
private:
    long m_fs;
    QString m_filePath;
    QBuffer m_buffer;
    long m_sampleNum;
    unsigned m_sampleTime;
    long m_bufferSize;
    QVector<double> m_vecBuffer;
    bool m_isStop = true;
    DataIODevice *m_ioDevice;
};
//从NI设备获得数据
class NIDeviceAcquire:public QThread{
    Q_OBJECT
public:
    explicit NIDeviceAcquire(long fs,DataIODevice *device,QObject *parent = nullptr);
    void openDevice();
    void run() ;
    void start(const QAudioDeviceInfo &inputDevice) ;
    void stop();
private:
    QBuffer m_buffer;
    long m_fs;

    bool m_isStop = true;
    DataIODevice *m_ioDevice;
    QAudioInput *m_audioInput;
};
#endif // DATAACQUIRE_H
