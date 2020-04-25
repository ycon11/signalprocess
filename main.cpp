#include"mainwindow.h"

#include<QApplication>
#include<QMessageBox>
#include<QtMultimedia/QAudioDeviceInfo>
#include<QtMultimedia/QAudioInput>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const QAudioDeviceInfo inputDevice = QAudioDeviceInfo::defaultInputDevice();
    if (inputDevice.isNull()) {
        QMessageBox::warning(nullptr, "audio",
            "There is no audio input device available.");
        return -1;
    }
    MainWindow w(inputDevice);
    w.show();
    return a.exec();
}
