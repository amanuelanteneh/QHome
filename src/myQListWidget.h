#pragma once
#ifndef MYQLISTWIDGET_H
#define MYQLISTWIDGET_H
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QListWidget>
#include <QCloseEvent>
class myQListWidget : public QListWidget { //inherties from QListWidget
	Q_OBJECT
		/* This class was purely made so that I could override the closeEvent function of the
		standard QListWidget class to make it emit the closedOut() signal so that my studyLabel class
		will know when the user has finished selecting the items they want to delete from the class */

signals:
	void closedOut();
protected:
	void closeEvent(QCloseEvent* event);

};
#endif // MYQLISTWIDGET_H