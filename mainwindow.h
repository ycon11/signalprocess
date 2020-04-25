#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include<QtCharts/QChartGlobal>
#include<QAudioInput>
#include<QVBoxLayout>
#include<QDebug>
#include"ui_mainwindow.h"
#include"wave.h"
#include"dataiodevice.h"
#include"signalprocess.h"
#include"dataacquire.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; }
class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
class QAudioDeviceInfo;
QT_END_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QAudioDeviceInfo& deviceInfo, QWidget* parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindowClass *ui;
    Wave* wave1, * wave2, * wave3;
    QWidget* widget;
    DataIODevice* m_device1;
    NIDeviceAcquire* m_NIDevice;
    FileDataAcquire* m_fileData;
};
#endif // MAINWINDOW_H
