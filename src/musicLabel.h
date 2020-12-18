#pragma once
#ifndef MUSICLABEL_H
#define MUSICLABEL_H
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
#include "imageDownloader.h"
#include <qradiobutton.h>
#include <qinputdialog.h>
#include <qprocess.h>
#include <qoauth2authorizationcodeflow.h>
#include <qoauthhttpserverreplyhandler.h>
#include <qdesktopservices.h>
#include <QtNetworkAuth>
#include <qnetworkaccessmanager.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <qtimer.h>
#include <qdesktopwidget.h>
#include <qmap.h>
struct Song {
	QString name;
	QString artist;
	QString uri;
};
struct Playlist {
	QString name;
	QString id;
	QMap<QString, Song>* songs; //using map since values are sorted by key
};

class musicLabel : public QLabel {
	Q_OBJECT

public:
	explicit musicLabel(QWidget* parent = Q_NULLPTR, const QString& picPath = "", int w = 0, int h = 0);
	~musicLabel();

private:
	int wdt, hgt;
	QPixmap* labelPic;
	QMenu* musicControlMenu;
	QOAuth2AuthorizationCodeFlow spotify;
	QOAuthHttpServerReplyHandler* spotifyReplyHandler;
	QString userName;
	QString currentPlaylist;
	Song currentPlayingSong;
	QVector<Playlist> playlists;
	imageDownloader* albumArtDownloader;
	QString spotifyWebPlayerURL;
	QString spotifyAppPath;
	QTimer* albumRefreshTimer;
	bool isAccessGranted;
	void showMessage(QString text, QString iconPath, QString title);
	void getPlaylists();

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleasedEvent(QMouseEvent* event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

private slots:
	void pauseMusic();
	void playMusic();
	void startMusic();
	void nextMusic();
	void prevMusic();
	void queueMusic();
	void currentMusic();
	void changeVolume();
	void authenticationStatusChanged(QAbstractOAuth::Status status);
	void changeToAlbumArt();
	void refreshAlbumArt();
	void checkForPlaybackChange();

};
#endif // !MUSICLABEL_H