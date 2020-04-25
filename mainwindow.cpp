#include "mainwindow.h"

MainWindow::MainWindow(const QAudioDeviceInfo& deviceInfo, QWidget* parent)
    : QMainWindow(parent),ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
#if 0
    widget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    wave1 = new Wave();
    wave1->setMinimumSize(800, 300);
    wave1->getAxis(Qt::Horizontal)->setRange(0, SAMPLE_COUNT);
    wave1->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave1->getAxis(Qt::Horizontal)->setTitleText("Samples");
    wave1->getAxis(Qt::Vertical)->setRange(-10, 10);
    wave1->getAxis(Qt::Vertical)->setTitleText("Audio level");

    wave2 = new Wave();
    wave2->setMinimumSize(800, 300);
    wave2->getAxis(Qt::Horizontal)->setRange(0,SAMPLE_COUNT);
    wave2->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave2->getAxis(Qt::Horizontal)->setTitleText("Samples");

    wave2->getAxis(Qt::Vertical)->setRange(-1, 1);
    wave2->getAxis(Qt::Vertical)->setTitleText("Audio level");


    QAudioFormat formatAudio;
    formatAudio.setSampleRate(24000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    //m_audioInput1 = new QAudioInput(deviceInfo, formatAudio, this);
    //m_audioInput2 = new QAudioInput(deviceInfo, formatAudio, this);

    //m_device1 = new XYSeriesIODevice(wave1->getSeries(), this);
    //m_device1->open(QIODevice::WriteOnly);

    //m_device2 = new XYSeriesIODevice(wave2->getSeries(), this);
    //m_device2->open(QIODevice::WriteOnly);


    //m_audioInput1->start(m_device1);
    //m_audioInput2->start(m_device2);


    //mainLayout->addWidget(wave1);
    //mainLayout->addWidget(wave2);
    //widget->setLayout(mainLayout);
    //setCentralWidget(widget);
#endif
//hilbert 测试
#if 0
    acquire = new SignalAcquire(12000);
    acquire->start();
    wave1 = new Wave();
    wave1->setMinimumSize(800, 300);
    wave1->getAxis(Qt::Horizontal)->setRange(0, SAMPLE_COUNT);
    wave1->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave1->getAxis(Qt::Horizontal)->setTitleText("Samples");
    wave1->getAxis(Qt::Vertical)->setRange(-1, 1);
    wave1->getAxis(Qt::Vertical)->setTitleText("Audio level");
    //connect(acquire,SIGNAL(sendData(double *)),wave1,SLOT())
#endif
#if 1
    //读数据
    QVector<double> points;
    QFile file("E:\\project\\SignalProcess\\SignalProcess\\130.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to open file";
        return;
    }
    QTextStream textInput(&file);
    QString lineStr;
    while (!textInput.atEnd()) {
        lineStr = textInput.readLine();  //读取数据
        points.push_back(lineStr.toDouble());
    }
    file.close();


    //平均傅里叶变换
    int N = 1024;
    int FS = 12000;
    vec pointsVec = qVec2Vec(points);
    auto YK = nSegFFT(pointsVec,N,12000);
    QVector<QPointF> points2(YK.rows() / 2);
    for (int i = 0; i < YK.rows() / 2; i++) {
        points2[i].setX(YK(i,0));
        points2[i].setY(YK(i,1));
    }

   //包络谱
    vec h = EnvelopeSpectrum(pointsVec);
    int size = h.size();
    QVector<QPointF> points3(size);
    for (int i = 0; i < size; i++) {
        points3[i].setX(i*FS/size);
        points3[i].setY(h(i));
    }

    widget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    //wave1 = new Wave();
    //wave1->setMinimumSize(800, 300);
    //wave1->getAxis(Qt::Horizontal)->setRange(0,YK.rows()*FS/N);
    //wave1->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    //wave1->getAxis(Qt::Horizontal)->setTitleText("Samples");
    //wave1->getAxis(Qt::Vertical)->setRange(0, 200);
    //wave1->getAxis(Qt::Vertical)->setTitleText("Audio level");
    //wave1->setSeries(points2);

    wave2 = new Wave();
    wave2->setMinimumSize(800, 300);
    wave2->getAxis(Qt::Horizontal)->setRange(0, FS / 2);
    wave2->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave2->getAxis(Qt::Horizontal)->setTitleText("Samples");
    wave2->getAxis(Qt::Vertical)->setRange(0, 120);
    wave2->getAxis(Qt::Vertical)->setTitleText("Audio level");
    wave2->setSeries(points2);

    /*wave3 = new Wave();
    wave3->setMinimumSize(800, 300);
    wave3->getAxis(Qt::Horizontal)->setRange(0, FS / 2);
    wave3->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave3->getAxis(Qt::Vertical)->setRange(0, 5);
    //wave3->getAxis(Qt::Vertical)->setTitleText("Audio level");
    wave3->setSeries(points3);*/

    mainLayout->addWidget(wave2);
    //mainLayout->addWidget(wave3);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

#endif
#if 0
    int N = 8;
    QVector<double> x(8, 1);
    for (int i = 0; i < 8; i++) {
        x[i] = i + 1;
    }
    auto y = FFT(x, 16);
    auto x2 = IFFT(y);
    auto h = Hilbert(x);
    qDebug() << "===========FFT======================";
    for (int i = 0; i < y.size(); i++) {
        qDebug() << y[i].real() << " " << y[i].imag();
    }
    qDebug() << "===========IFFT======================";
    for (int i = 0; i < x2.size(); i++) {
        qDebug() << x2[i].real() << " " << x2[i].imag();
    }
    qDebug() << "============Hilbert=====================";
    for (int i = 0; i < h.size(); i++) {
        qDebug() << h[i].real() << " " << h[i].imag();
    }



#endif
#if 0
    widget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    wave1 = new Wave();
    wave1->setMinimumSize(800, 300);
    wave1->getAxis(Qt::Horizontal)->setRange(0, DataIODevice::sampleCount);
    wave1->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave1->getAxis(Qt::Horizontal)->setTitleText("Samples");
    wave1->getAxis(Qt::Vertical)->setRange(-10, 10);
    wave1->getAxis(Qt::Vertical)->setTitleText("Audio level");

    wave2 = new Wave();
    wave2->setMinimumSize(800, 300);
    wave2->getAxis(Qt::Horizontal)->setRange(0, 6000);
    wave2->getAxis(Qt::Horizontal)->setLabelFormat("%g");
    wave2->getAxis(Qt::Horizontal)->setTitleText("Samples");

    wave2->getAxis(Qt::Vertical)->setRange(-10, 10);
    wave2->getAxis(Qt::Vertical)->setTitleText("Audio level");

    m_device1 = new DataIODevice();
    m_device1->addXYSeries(wave1->getSeries(), nullptr);
    m_device1->addXYSeries(wave2->getSeries(), &FFT);

    m_fileData = new FileDataAcquire(QString("E:\\Qt\\signalprocess\\130.txt"), 12000, 200, m_device1);
    m_fileData->start();

    mainLayout->addWidget(wave1);
    mainLayout->addWidget(wave2);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

