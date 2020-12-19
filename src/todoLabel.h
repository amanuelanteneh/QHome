#pragma once
#ifndef TODOLABEL_H
#define TODOLABEL_H
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QPixmap>
#include <QGraphicsBlurEffect>
#include <QProcess>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <qnetworkaccessmanager.h>
#include <qpushbutton.h>
#include <QPainter>
#include <qmessagebox.h>
#include <qmenu.h>
#include <QFile>
#include <iostream>
#include <qinputdialog.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qtextedit.h>
#include <QDesktopWidget>
using namespace std;
class todoLabel : public QLabel { //inherites from QLabel
    Q_OBJECT

public:
    explicit todoLabel(QWidget* parent = Q_NULLPTR, const QString& picPath = "", int w = 0, int h = 0);
    ~todoLabel();

signals:
    void clicked();
    void released();
	void textChanged();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleasedEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:
    QPixmap* labelPic;
    int wdt, hgt, screenWidth, screenHeight;
	QTextEdit* theTodoList;
private slots:
	void toDoListChanged();
};

#endif // TODOLABEL_H