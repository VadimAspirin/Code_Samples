#include "QtGuiPlayer.h"

using namespace openni;

QtGuiPlayer::QtGuiPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.labelCurrentFramesId->setText("--");
	ui.labelNumberOfFrames->setText("--");
	ui.horizontalSliderCurrentFrame->setDisabled(true);
	ui.pushButtonPause->setDisabled(true);
	ui.pushButtonForward1Frame->setDisabled(true);
	ui.pushButtonForward10Frame->setDisabled(true);
	ui.pushButtonBackward1Frame->setDisabled(true);
	ui.pushButtonBackward10Frame->setDisabled(true);
}

QtGuiPlayer::~QtGuiPlayer()
{
	delete player;
	delete timer;
}

void QtGuiPlayer::on_pushButton_2_clicked()
{
	QString str = QFileDialog::getOpenFileName(this, "Выберите файл", "", "*.oni");
	if (str.isEmpty())
		return;

	try
	{
		player = new ONIPlayer(str);
	}
	catch (char* str)
	{
		QMessageBox::critical(this, "Ошибка", str);
		QtGuiPlayer::~QtGuiPlayer();
		exit(1);
	}

	ui.horizontalSliderCurrentFrame->setRange(0, player->getNumberOfFrames());
	ui.horizontalSliderCurrentFrame->setEnabled(true);
	ui.pushButtonPause->setEnabled(true);
	ui.pushButton_2->setDisabled(true);
	ui.labelNumberOfFrames->setNum(player->getNumberOfFrames());

	connect(ui.horizontalSliderCurrentFrame, SIGNAL(valueChanged(int)), ui.labelCurrentFramesId, SLOT(setNum(int)));

	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
	timer->start();
}

void QtGuiPlayer::on_pushButtonPause_clicked()
{
	if (timer->isActive())
	{
		timer->stop();
		ui.pushButtonForward1Frame->setEnabled(true);
		ui.pushButtonForward10Frame->setEnabled(true);
		ui.pushButtonBackward1Frame->setEnabled(true);
		ui.pushButtonBackward10Frame->setEnabled(true);
	}
	else
	{
		timer->start();
		ui.pushButtonForward1Frame->setDisabled(true);
		ui.pushButtonForward10Frame->setDisabled(true);
		ui.pushButtonBackward1Frame->setDisabled(true);
		ui.pushButtonBackward10Frame->setDisabled(true);
	}

}

void QtGuiPlayer::slotTimerAlarm()
{
	ui.labelFrameColor->setPixmap(QPixmap::fromImage(player->getNewColorFrame()));
	ui.labelFrameDepth->setPixmap(QPixmap::fromImage(player->getNewDepthFrame()));
	ui.horizontalSliderCurrentFrame->setValue(player->getCurrentFramesId());
}

void QtGuiPlayer::on_horizontalSliderCurrentFrame_sliderPressed()
{
	timer->stop();
	ui.pushButtonForward1Frame->setEnabled(true);
	ui.pushButtonForward10Frame->setEnabled(true);
	ui.pushButtonBackward1Frame->setEnabled(true);
	ui.pushButtonBackward10Frame->setEnabled(true);
}

void QtGuiPlayer::on_horizontalSliderCurrentFrame_sliderReleased()
{
	try
	{
		player->seekFrame(ui.horizontalSliderCurrentFrame->value());
	}
	catch (char* str)
	{
		QMessageBox::critical(this, "Ошибка", str);
		QtGuiPlayer::~QtGuiPlayer();
		exit(1);
	}
	timer->start();
	ui.pushButtonForward1Frame->setDisabled(true);
	ui.pushButtonForward10Frame->setDisabled(true);
	ui.pushButtonBackward1Frame->setDisabled(true);
	ui.pushButtonBackward10Frame->setDisabled(true);
}

void QtGuiPlayer::on_pushButtonForward1Frame_clicked()
{
	try
	{
		player->seekFrame(player->checkPositionShift(player->getCurrentFramesId() + 2));
	}
	catch (char* str)
	{
		QMessageBox::critical(this, "Ошибка", str);
		QtGuiPlayer::~QtGuiPlayer();
		exit(1);
	}
	slotTimerAlarm();
}

void QtGuiPlayer::on_pushButtonForward10Frame_clicked()
{
	try
	{
		player->seekFrame(player->checkPositionShift(player->getCurrentFramesId() + 11));
	}
	catch (char* str)
	{
		QMessageBox::critical(this, "Ошибка", str);
		QtGuiPlayer::~QtGuiPlayer();
		exit(1);
	}
	slotTimerAlarm();
}

void QtGuiPlayer::on_pushButtonBackward1Frame_clicked()
{
	try
	{
		player->seekFrame(player->checkPositionShift(player->getCurrentFramesId() - 2));
	}
	catch (char* str)
	{
		QMessageBox::critical(this, "Ошибка", str);
		QtGuiPlayer::~QtGuiPlayer();
		exit(1);
	}
	slotTimerAlarm();
}

void QtGuiPlayer::on_pushButtonBackward10Frame_clicked()
{
	try
	{
		player->seekFrame(player->checkPositionShift(player->getCurrentFramesId() - 11));
	}
	catch (char* str)
	{
		QMessageBox::critical(this, "Ошибка", str);
		exit(1);
	}
	slotTimerAlarm();
}