#include "stdafx.h"

//#define NOMINMAX
#undef min
#undef max

#include "widget.h"
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QValueAxis>
#include "xyseriesiodevice.h"

QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
	: QWidget(parent),
	m_device(0),
	m_chart(0),
	m_series(0),
	m_audioInput(0)
{
	m_chart = new QChart;
	QChartView *chartView = new QChartView(m_chart);
	chartView->setMinimumSize(800, 600);
	m_series = new QLineSeries;
	m_chart->addSeries(m_series);
	QValueAxis *axisX = new QValueAxis;
	axisX->setRange(0, 2000);
	axisX->setLabelFormat("%g");
	axisX->setTitleText("Samples");
	QValueAxis *axisY = new QValueAxis;
	axisY->setRange(-1, 1);
	axisY->setTitleText("Audio level");
	m_chart->setAxisX(axisX, m_series);
	m_chart->setAxisY(axisY, m_series);
	m_chart->legend()->hide();
	m_chart->setTitle("Data from the microphone");

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(chartView);
	setLayout(mainLayout);

	QAudioFormat formatAudio;
	formatAudio.setSampleRate(8000);
	formatAudio.setChannelCount(1);
	formatAudio.setSampleSize(8);
	formatAudio.setCodec("audio/pcm");
	formatAudio.setByteOrder(QAudioFormat::LittleEndian);
	formatAudio.setSampleType(QAudioFormat::UnSignedInt);

	QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
	m_audioInput = new QAudioInput(inputDevices, formatAudio, this);

	m_device = new XYSeriesIODevice(m_series, this);
	m_device->open(QIODevice::WriteOnly);

	m_audioInput->start(m_device);
}

Widget::~Widget()
{
	m_audioInput->stop();
	m_device->close();
}
