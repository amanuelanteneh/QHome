#pragma once
#ifndef NEWSLABEL_H
#define NEWSLABEL_H
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
#include <qurl.h>
#include <qurlquery.h>
#include <qnetworkreply.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
using namespace std;
class newsLabel : public QLabel { //inherites from QLabel
    Q_OBJECT

public:
    explicit newsLabel(QWidget* parent = Q_NULLPTR, const QString& picPath = "", int w = 0, int h = 0);
    ~newsLabel();

signals:
    void clicked();
    void released();
protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:
    QPixmap* labelPic;
    int wdt, hgt, screenWidth, screenHeight;
	QNetworkAccessManager *apiReplyHandler;
	void handleNewsData(QNetworkReply* networkReply);
};

#endif // NEWSLABEL_H