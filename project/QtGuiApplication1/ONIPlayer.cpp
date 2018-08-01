#include "ONIPlayer.h"

ONIPlayer::ONIPlayer(QString fileName)
{
	if (OpenNI::initialize() != STATUS_OK)
		throw OpenNI::getExtendedError();

	QByteArray fileONI = fileName.toLocal8Bit();
	if (device.open(fileONI.constData()) != STATUS_OK)
		throw OpenNI::getExtendedError();

	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
		if (depth.create(device, SENSOR_DEPTH) != STATUS_OK)
			throw OpenNI::getExtendedError();

	if (device.getSensorInfo(SENSOR_COLOR) != NULL)
		if (color.create(device, SENSOR_COLOR) != STATUS_OK)
			throw OpenNI::getExtendedError();

	playbackControl = device.getPlaybackControl();
	numberOfFrames = playbackControl->getNumberOfFrames(color);
	currentFramesId = 0;
}


ONIPlayer::~ONIPlayer()
{
	depth.stop();
	color.stop();
	depth.destroy();
	color.destroy();
	device.close();
	OpenNI::shutdown();
}


QImage ONIPlayer::getNewColorFrame()
{
	VideoFrameRef frameColor;

	color.start();
	color.readFrame(&frameColor);
	color.stop();

	uchar *pixelsColor = (uchar*)frameColor.getData();
	QImage imageColor = QImage(pixelsColor, frameColor.getWidth(), frameColor.getHeight(), QImage::Format_RGB888);

	currentFramesId = frameColor.getFrameIndex();
	return imageColor;
}

QImage ONIPlayer::getNewDepthFrame()
{
	VideoFrameRef frameDepth;

	depth.start();
	depth.readFrame(&frameDepth);
	depth.stop();

	VideoMode mode = frameDepth.getVideoMode();
	cv::Mat m_imageDepth = cv::Mat(mode.getResolutionY(), mode.getResolutionX(), CV_16U, (char*)frameDepth.getData());
	HistogramNormalizer::run(m_imageDepth);
	m_imageDepth.convertTo(m_imageDepth, CV_8UC1);

	QImage imageDepth = QImage(m_imageDepth.data,
		frameDepth.getWidth(), frameDepth.getHeight(),
		QImage::Format_Indexed8);
	imageDepth = imageDepth.convertToFormat(QImage::Format_RGB32);

	return imageDepth;
}

int ONIPlayer::getNumberOfFrames()
{
	return numberOfFrames;
}

int ONIPlayer::getCurrentFramesId()
{
	return currentFramesId;
}

void ONIPlayer::seekFrame(int frameId)
{
	color.start();
	depth.start();
	if (playbackControl->seek(color, frameId) != openni::STATUS_OK || playbackControl->seek(depth, frameId) != openni::STATUS_OK)
		throw "Something went wrong while reading frame";
	depth.stop();
	color.stop();
}

int ONIPlayer::checkPositionShift(int shift)
{
	if (shift >= numberOfFrames || shift <= 0)
		return 1;
	return shift;
}