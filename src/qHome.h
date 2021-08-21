#include <QtWidgets/QMainWindow>
#include <qgeopositioninfosource.h>
#include <qgeopositioninfo.h>
#include <qdebug.h>
#include <QtPositioning/qgeopositioninfo.h>
#include <QtPositioning/qgeopositioninfosource.h>
#include <qurl.h>
#include <qurlquery.h>
#include <qnetworkreply.h>
#include <qlabel.h>
#include "ui_qHome.h"
#include "studyLabel.h"
#include "todoLabel.h"
#include "musicLabel.h"
#include "bluetoothLabel.h"
#include "newsLabel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QDesktopWidget>
#include <qtimer.h>

class qHome : public QMainWindow {
	Q_OBJECT

public:
   	qHome(QWidget* parent = Q_NULLPTR);
	~qHome();

private slots:
	void positionUpdated(const QGeoPositionInfo& info);
	void changeBackgroundImage();
	void refreshNews();
protected:
	void resizeEvent(QResizeEvent* evt);
    void mousePressEvent(QMouseEvent* event);
private:
	bluetoothLabel* headPhones;
	int screenHeight;
	int screenWidth;
	QMenu* bkgdMenu;
	studyLabel* classWork;
	todoLabel* toDoList;
	musicLabel* musicPlayer;
	newsLabel* newsApp;
	QPixmap bkgd; 
	QGeoCoordinate coord;
	void handleGeoData(QNetworkReply* networkReply);
	void handleGeoWeatherData(QNetworkReply* networkReply);
	void refreshWeather();
	QLabel* wethInfo;
	QLabel* wethIcon;
	QLabel* newsInfo;
	QString userCity;
	QNetworkAccessManager *apiReplyHandler;
	Ui::qHomeClass ui;
};


