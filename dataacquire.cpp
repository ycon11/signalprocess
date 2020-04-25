#include "dataacquire.h"

//从网口获得数据
NetDataAcquire::NetDataAcquire(long fs,DataIODevice *device,QObject *parent)
    :QThread(parent),m_fs(fs),m_ioDevice(device)
{

}
void NetDataAcquire::netConnect() {


}
void NetDataAcquire::run() {
    m_isStop = false;
    while(!m_isStop){

    }
}
void NetDataAcquire::stop(){
    m_isStop = true;
}

//从文件获得数据
FileDataAcquire::FileDataAcquire(const QString &path,long fs,long bufferSize,DataIODevice *device,QObject *parent)
    :QThread(parent),m_filePath(path),m_fs(fs),m_bufferSize(bufferSize),m_ioDevice(device)
{
    m_vecBuffer.resize(m_bufferSize);
}
void FileDataAcquire::readFile(const QString &filePath) {

}
void FileDataAcquire::run() {
    m_isStop = false;
    QFile file(m_filePath);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
       // QMessageBox::warning(this,QString("Error"),QString("Failed to open file!"));
    }
    QTextStream fileStream(&file);

    qsrand(1);
    while(!m_isStop){
        QByteArray byteArray;
        QDataStream byteStream(&byteArray,QIODevice::WriteOnly);
        QDataStream out(&byteArray,QIODevice::ReadOnly);
        for(int i = 0;i<m_bufferSize;i++){
            double val ;
            //val = qSin(static_cast<double>(i*M_PI*2)/m_bufferSize)*5;
            val = rand()%5;
            //fileStream>>val;
            byteStream<<val;
        }
        m_ioDevice->open(QIODevice::WriteOnly);
        m_ioDevice->writeBuffer(byteArray,m_bufferSize);
        m_ioDevice->close();
        QThread::msleep(30);
    }
    file.close();
}
void FileDataAcquire::stop(){
    m_isStop = true;
}

//从NI设备获得数据
NIDeviceAcquire::NIDeviceAcquire(long fs,DataIODevice *device,QObject *parent)
    :QThread(parent),m_fs(fs),m_ioDevice(device)
{

}
void NIDeviceAcquire::openDevice() {

}
void NIDeviceAcquire::run(){

}
void NIDeviceAcquire::start(const QAudioDeviceInfo &inputDevice) {
    m_isStop = false;

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(m_fs);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    m_audioInput = new QAudioInput(inputDevice, formatAudio,this);
    //m_audioInput->start(m_device);

}
void NIDeviceAcquire::stop(){
    m_isStop = true;
}
