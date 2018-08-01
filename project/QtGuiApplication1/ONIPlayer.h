#pragma once

#include "HistogramNormalizer.h"
#include <OpenNI.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <OpenNI.h>
#include <opencv2/opencv.hpp>

using namespace openni;

class ONIPlayer
{
private:
	Device device;
	VideoStream depth;
	VideoStream color;
	PlaybackControl* playbackControl;
	int numberOfFrames;
	int currentFramesId;

public:
	ONIPlayer(QString fileName);
	~ONIPlayer();
	QImage getNewColorFrame();
	QImage getNewDepthFrame();
	int getNumberOfFrames();
	int getCurrentFramesId();
	void seekFrame(int frameId);
	int checkPositionShift(int shift);
};