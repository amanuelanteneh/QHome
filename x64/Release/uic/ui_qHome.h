/********************************************************************************
** Form generated from reading UI file 'qHome.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHOME_H
#define UI_QHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qHomeClass
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridCell1;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridCell2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridCell3;
    QLabel *wethInfo;
    QWidget *gridLayoutWidget_5;
    QGridLayout *wethIcon;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridCell4;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridCell5;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qHomeClass)
    {
        if (qHomeClass->objectName().isEmpty())
            qHomeClass->setObjectName(QString::fromUtf8("qHomeClass"));
        qHomeClass->resize(763, 873);
        qHomeClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(qHomeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 0, 191, 191));
        gridCell1 = new QGridLayout(gridLayoutWidget);
        gridCell1->setSpacing(6);
        gridCell1->setContentsMargins(11, 11, 11, 11);
        gridCell1->setObjectName(QString::fromUtf8("gridCell1"));
        gridCell1->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(20, 380, 191, 171));
        gridCell2 = new QGridLayout(gridLayoutWidget_2);
        gridCell2->setSpacing(6);
        gridCell2->setContentsMargins(11, 11, 11, 11);
        gridCell2->setObjectName(QString::fromUtf8("gridCell2"));
        gridCell2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(20, 190, 191, 191));
        gridCell3 = new QGridLayout(gridLayoutWidget_3);
        gridCell3->setSpacing(6);
        gridCell3->setContentsMargins(11, 11, 11, 11);
        gridCell3->setObjectName(QString::fromUtf8("gridCell3"));
        gridCell3->setContentsMargins(0, 0, 0, 0);
        wethInfo = new QLabel(centralWidget);
        wethInfo->setObjectName(QString::fromUtf8("wethInfo"));
        wethInfo->setGeometry(QRect(400, 10, 271, 171));
        gridLayoutWidget_5 = new QWidget(centralWidget);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(210, 0, 191, 191));
        wethIcon = new QGridLayout(gridLayoutWidget_5);
        wethIcon->setSpacing(6);
        wethIcon->setContentsMargins(11, 11, 11, 11);
        wethIcon->setObjectName(QString::fromUtf8("wethIcon"));
        wethIcon->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_4 = new QWidget(centralWidget);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(20, 550, 191, 181));
        gridCell4 = new QGridLayout(gridLayoutWidget_4);
        gridCell4->setSpacing(6);
        gridCell4->setContentsMargins(11, 11, 11, 11);
        gridCell4->setObjectName(QString::fromUtf8("gridCell4"));
        gridCell4->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_6 = new QWidget(centralWidget);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(210, 190, 191, 191));
        gridCell5 = new QGridLayout(gridLayoutWidget_6);
        gridCell5->setSpacing(6);
        gridCell5->setContentsMargins(11, 11, 11, 11);
        gridCell5->setObjectName(QString::fromUtf8("gridCell5"));
        gridCell5->setContentsMargins(0, 0, 0, 0);
        qHomeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qHomeClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 763, 22));
        qHomeClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(qHomeClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qHomeClass->setStatusBar(statusBar);

        retranslateUi(qHomeClass);

        QMetaObject::connectSlotsByName(qHomeClass);
    } // setupUi

    void retranslateUi(QMainWindow *qHomeClass)
    {
        qHomeClass->setWindowTitle(QCoreApplication::translate("qHomeClass", "qHome", nullptr));
        wethInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class qHomeClass: public Ui_qHomeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHOME_H
