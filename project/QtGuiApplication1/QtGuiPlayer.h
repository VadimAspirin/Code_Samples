#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include "HistogramNormalizer.h"
#include "ONIPlayer.h"
#include <OpenNI.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>

using namespace openni;

class QtGuiPlayer : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiPlayer(QWidget *parent = Q_NULLPTR);
	~QtGuiPlayer();

private slots:
	void on_pushButton_2_clicked();
	void on_pushButtonPause_clicked();
	void slotTimerAlarm();
	void on_horizontalSliderCurrentFrame_sliderPressed();
	void on_horizontalSliderCurrentFrame_sliderReleased();
	void on_pushButtonForward1Frame_clicked();
	void on_pushButtonForward10Frame_clicked();
	void on_pushButtonBackward1Frame_clicked();
	void on_pushButtonBackward10Frame_clicked();

private:
	Ui::QtGuiApplication1Class ui;
	ONIPlayer *player;
	QTimer *timer;
};
