#pragma once
#ifndef STUDYLABEL_H
#define STUDYLABEL_H
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
#include <QFileInfo.h>
#include <QVector>
#include <QFile>
#include <iostream>
#include <qinputdialog.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qtextedit.h>
#include <QDesktopWidget>
#include <QListWidget>
#include <qsignalmapper.h>
#include "myQListWidget.h"
using namespace std;
class studyLabel : public QLabel { //inherites from QLabel
    Q_OBJECT

public:
    explicit studyLabel(QWidget* parent = Q_NULLPTR, 
        const QString& picPath = "", int w = 0, int h = 0);
    ~studyLabel();

signals:
    void clicked();
    void released();
	void closeEvent();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleasedEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:
    QPixmap* labelPic;
    int wdt, hgt;
	QMenu* studyMenu;
	myQListWidget* deleteOptions;
	bool wantToDeleteURL; //to let deleteOptionSelected slot know which vector to modify if called
	bool wantToDeleteFile; //ibid but for file vector
	QVector<QString> studyOption1LocalFiles;
	QVector<QString> studyOption1URLs;
	QVector<QString> studyOption2LocalFiles;
	QVector<QString> studyOption2URLs;
	QVector<QString> studyOption3LocalFiles;
	QVector<QString> studyOption3URLs;
	QVector<QString> studyOption4LocalFiles;
	QVector<QString> studyOption4URLs;
	QVector<QString> studyOption5LocalFiles;
	QVector<QString> studyOption5URLs;
	QVector<QString> studyOption6LocalFiles;
	QVector<QString> studyOption6URLs;
	QVector<QString> *urlVectorToDelete;
	QVector<QString> *fileVectorToDelete;
	QString classFilenameToDeleteFrom;
	QString classNameToDeleteFrom;
	void createClass(QString filename, int classNumber);
	void addClass(QString classFilename, int classNumber, QString classNumberStr);
	void addToClass(QVector<QString>& urlVector, QVector<QString>& fileVector,
		QString filename, QString className, bool addingURL);
	void deleteFromClass(QVector<QString>& urlVector, QVector<QString>& fileVector,
		QString filename, QString className, bool removingURL);
	void showMessage(QString text, QString iconPath, QString title);
private slots:
	void studyOption1();
	void studyOption2();
	void studyOption3();
	void studyOption4();
	void studyOption5();
	void studyOption6();
	void configureClasses();
	void deleteOptionSelected();
};

#endif // STUDYLABEL_H

