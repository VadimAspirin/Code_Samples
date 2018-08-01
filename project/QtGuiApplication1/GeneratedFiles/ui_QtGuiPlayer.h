/********************************************************************************
** Form generated from reading UI file 'QtGuiPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIPLAYER_H
#define UI_QTGUIPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication1Class
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_2;
    QLabel *labelFrameDepth;
    QLabel *labelFrameColor;
    QPushButton *pushButtonPause;
    QSlider *horizontalSliderCurrentFrame;
    QPushButton *pushButtonBackward1Frame;
    QPushButton *pushButtonBackward10Frame;
    QPushButton *pushButtonForward1Frame;
    QPushButton *pushButtonForward10Frame;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *labelCurrentFramesId;
    QLabel *label_3;
    QLabel *labelNumberOfFrames;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication1Class)
    {
        if (QtGuiApplication1Class->objectName().isEmpty())
            QtGuiApplication1Class->setObjectName(QStringLiteral("QtGuiApplication1Class"));
        QtGuiApplication1Class->resize(1431, 799);
        centralWidget = new QWidget(QtGuiApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(630, 20, 201, 51));
        labelFrameDepth = new QLabel(centralWidget);
        labelFrameDepth->setObjectName(QStringLiteral("labelFrameDepth"));
        labelFrameDepth->setGeometry(QRect(10, 220, 591, 431));
        labelFrameColor = new QLabel(centralWidget);
        labelFrameColor->setObjectName(QStringLiteral("labelFrameColor"));
        labelFrameColor->setGeometry(QRect(750, 220, 591, 431));
        pushButtonPause = new QPushButton(centralWidget);
        pushButtonPause->setObjectName(QStringLiteral("pushButtonPause"));
        pushButtonPause->setGeometry(QRect(570, 100, 111, 51));
        horizontalSliderCurrentFrame = new QSlider(centralWidget);
        horizontalSliderCurrentFrame->setObjectName(QStringLiteral("horizontalSliderCurrentFrame"));
        horizontalSliderCurrentFrame->setGeometry(QRect(370, 170, 711, 19));
        horizontalSliderCurrentFrame->setOrientation(Qt::Horizontal);
        pushButtonBackward1Frame = new QPushButton(centralWidget);
        pushButtonBackward1Frame->setObjectName(QStringLiteral("pushButtonBackward1Frame"));
        pushButtonBackward1Frame->setGeometry(QRect(260, 160, 75, 23));
        pushButtonBackward10Frame = new QPushButton(centralWidget);
        pushButtonBackward10Frame->setObjectName(QStringLiteral("pushButtonBackward10Frame"));
        pushButtonBackward10Frame->setGeometry(QRect(160, 160, 75, 23));
        pushButtonForward1Frame = new QPushButton(centralWidget);
        pushButtonForward1Frame->setObjectName(QStringLiteral("pushButtonForward1Frame"));
        pushButtonForward1Frame->setGeometry(QRect(1110, 160, 75, 23));
        pushButtonForward10Frame = new QPushButton(centralWidget);
        pushButtonForward10Frame->setObjectName(QStringLiteral("pushButtonForward10Frame"));
        pushButtonForward10Frame->setGeometry(QRect(1210, 160, 71, 23));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(700, 100, 171, 51));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        labelCurrentFramesId = new QLabel(widget);
        labelCurrentFramesId->setObjectName(QStringLiteral("labelCurrentFramesId"));

        horizontalLayout->addWidget(labelCurrentFramesId);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setWordWrap(false);
        label_3->setMargin(0);

        horizontalLayout->addWidget(label_3);

        labelNumberOfFrames = new QLabel(widget);
        labelNumberOfFrames->setObjectName(QStringLiteral("labelNumberOfFrames"));

        horizontalLayout->addWidget(labelNumberOfFrames);

        QtGuiApplication1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiApplication1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1431, 21));
        QtGuiApplication1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiApplication1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setBaseSize(QSize(100, 20));
        QtGuiApplication1Class->setStatusBar(statusBar);

        retranslateUi(QtGuiApplication1Class);

        QMetaObject::connectSlotsByName(QtGuiApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication1Class)
    {
        QtGuiApplication1Class->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "QtGuiApplication1", nullptr));
        pushButton_2->setText(QApplication::translate("QtGuiApplication1Class", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273 (*.oni)", nullptr));
        labelFrameDepth->setText(QString());
        labelFrameColor->setText(QString());
        pushButtonPause->setText(QApplication::translate("QtGuiApplication1Class", "\320\237\320\260\321\203\320\267\320\260/\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214", nullptr));
        pushButtonBackward1Frame->setText(QApplication::translate("QtGuiApplication1Class", "<", nullptr));
        pushButtonBackward10Frame->setText(QApplication::translate("QtGuiApplication1Class", "<<", nullptr));
        pushButtonForward1Frame->setText(QApplication::translate("QtGuiApplication1Class", ">", nullptr));
        pushButtonForward10Frame->setText(QApplication::translate("QtGuiApplication1Class", ">>", nullptr));
        label->setText(QApplication::translate("QtGuiApplication1Class", "Current frame:    ", nullptr));
        labelCurrentFramesId->setText(QString());
        label_3->setText(QApplication::translate("QtGuiApplication1Class", "/", nullptr));
        labelNumberOfFrames->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication1Class: public Ui_QtGuiApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIPLAYER_H
