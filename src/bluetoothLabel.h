#pragma once
#ifndef BLUETOOTHLABEL_H
#define BLUETOOTHLABEL_H
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QPixmap>
#include <QGraphicsBlurEffect>
#include <QBluetoothDeviceInfo>
#include <qpushbutton.h>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QPainter>
#include <qmessagebox.h>
#include <qmenu.h>
#include <QFile>
#include <qlowenergycontroller.h>
#include "myQListWidget.h"
#include <qradiobutton.h>
#include <qinputdialog.h>
#include <WinSock2.h>
#include <ws2bth.h>
class bluetoothLabel : public QLabel {
	Q_OBJECT
public:
	explicit bluetoothLabel(QWidget* parent = Q_NULLPTR, const QString& picPath = "", int w = 0, int h = 0);
	~bluetoothLabel();

signals:
	void clicked();
	void released();
	void connected();
	void disconnected();
protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleasedEvent(QMouseEvent* event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
private:
	QPixmap* labelPic;
	int wdt, hgt;
	QBluetoothDeviceDiscoveryAgent* btDiscoveryAgent;
	QBluetoothSocket* device;
	QVector<QString> device1Info; //index 0 is device name, 1 is device address
	QVector<QString> device2Info;
	QVector<QString> device3Info;
	QVector<QString> foundDeviceNames;
	QVector<QString> foundDeviceIds;
	myQListWidget* foundDeviceOptions;
	bool connectedToDevice;
	int connectedDeviceIndex;
	QMenu* bluetoothMenu;
	QMenu* devicesMenu;
	void refreshDevices();
	void showMessage(QString text, QString iconPath, QString title);
private slots:
	void deviceDiscovered(const QBluetoothDeviceInfo& device);
	void finishedScan();
	void deviceAdditionSelected();
	void deviceConnected();
	void deviceDisconnected();
	void addDevice();
	void deviceOptions();
	void removeDevice();
	void bluetoothDevice1();
	void bluetoothDevice2();
	void bluetoothDevice3();
};
#endif // !BLUETOOTHLABEL_H