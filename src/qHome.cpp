#include <iostream>
using namespace std;
#include "qHome.h"
#define API_ID "762fe51da0e8caa555c7a4f03d4fa84d" //my API ID key for openweather.org
qHome::qHome(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QDesktopWidget desktop;
	screenHeight = desktop.geometry().height();
	screenWidth = desktop.geometry().width();
	bkgdMenu = new QMenu();
	wethInfo = new QLabel("", this);
	wethIcon = new QLabel("", this);
	openWeth = new QNetworkAccessManager(this);
	headPhones = new bluetoothLabel(nullptr, "img/beatsUnconnected", screenHeight / 11, screenHeight / 11);
	classWork = new studyLabel(nullptr, "img/bookImage2", screenHeight / 11, screenHeight / 11);
	toDoList = new todoLabel(nullptr, "img/todoListImage", screenHeight / 11, screenHeight / 11);
	musicPlayer = new musicLabel(nullptr, "img/spotifyImage", screenHeight / 11, screenHeight / 11);

	/* Setup weather stuff */
	wethIcon->setStyleSheet("QLabel { color : white; }");
	ui.wethInfo->setFixedWidth(screenWidth / 6);
	ui.wethInfo->setFixedHeight(screenHeight / 5);	
    ui.wethInfo->setStyleSheet("QLabel { color : white; }");
	QFont font = ui.wethInfo->font();
	font.setPointSize(((int)(screenHeight/82) + 2)); //add 2 so that value is never 0 bc behavior isn't defined for that
	ui.wethInfo->setAlignment(Qt::AlignLeft);
	font.setFamily("century gothic");
	ui.wethInfo->setFont(font);

	/* setting main window background img*/
	QPalette pal; 
	QFile bkgdImgFile("res/bkgdImgPathFile.txt");
	QTextStream bkgdImgStream(&bkgdImgFile);
	if (bkgdImgFile.open(QIODevice::ReadWrite)) {
		
		QString bkgdImgPath = bkgdImgStream.readLine();
		
		//to check if file has been moved/is actually a file.
		QFileInfo checkFile(bkgdImgPath); 
		if (bkgdImgPath != "" && bkgdImgPath != "\n" && checkFile.exists() && checkFile.isFile()) {
			bkgd = QPixmap(bkgdImgPath);
			pal.setBrush(QPalette::Background, bkgd);
			this->setPalette(pal);
		}
		
		else {
			bkgd = QPixmap("img/defaultBkgd");
			pal.setBrush(QPalette::Background, bkgd);
			this->setPalette(pal);
			bkgdImgStream << "img/defaultBkgd\n";
		}
	}
	bkgdImgFile.close();
	
	/* Rest of setup */
	ui.gridCell1->addWidget(headPhones);
	ui.gridCell2->addWidget(toDoList);
	ui.gridCell3->addWidget(classWork);
	ui.gridCell4->addWidget(musicPlayer);
	
	bkgdMenu->addAction("Change Background Image", this, SLOT(changeBackgroundImage()));
	
	this->setWindowTitle("QHome");
	this->setWindowIcon(QIcon("img/image14"));

	QGeoPositionInfoSource* source = QGeoPositionInfoSource::createDefaultSource(this);
	if (source) {
		connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
		source->setUpdateInterval(180000); //update every 180 seconds (3 mins)
		source->startUpdates();
	}
	//If QGeopositioninfosource returns 0 then no location found
	if (!source) {
		QMessageBox msg;
		msg.setText("No location detected!");
		msg.exec();
	}
}
qHome::~qHome() {
	delete wethIcon;
	delete wethInfo;
	delete classWork;
	delete headPhones;
	delete toDoList;
	delete musicPlayer;
	delete bkgdMenu;
}

void qHome::positionUpdated(const QGeoPositionInfo& info) {
	QString lat, lon = "";
	lat.setNum(info.coordinate().latitude());
	lon.setNum(info.coordinate().longitude());
	QString gInfo = "Latitude: " + lat + "\n" + "Longitude: " + lon;
	QUrl url("http://api.openweathermap.org/data/2.5/weather");
	QUrlQuery query;
	query.addQueryItem("lat", lat);
	query.addQueryItem("lon", lon);
	query.addQueryItem("mode", "json");
	query.addQueryItem("APPID", API_ID);
	url.setQuery(query);
	QNetworkReply* reply = openWeth->get(QNetworkRequest(url));
	connect(reply, &QNetworkReply::finished,
		this, [this, reply]() { handleGeoData(reply); });
	return;
}
void qHome::handleGeoData(QNetworkReply* networkReply) {
	if (!networkReply) {
		QMessageBox message;
		message.setText("No network reply for weather");
		message.setWindowTitle("Error");
		message.setWindowIcon(QIcon("img/warningImage"));
		message.exec();
		return;
	}
	QJsonDocument document = QJsonDocument::fromJson(networkReply->readAll());
	QJsonObject jo = document.object();
	QJsonValue jv = jo.value(QStringLiteral("name"));
	const QString city = jv.toString();
	userCity = city;
	refreshWeather();
}
void qHome::refreshWeather() {
	QUrl url("http://api.openweathermap.org/data/2.5/weather");
	QUrlQuery query;
	query.addQueryItem("q", userCity);
	query.addQueryItem("mode", "json");
	query.addQueryItem("APPID", API_ID);
	url.setQuery(query);
	QNetworkReply* reply = openWeth->get(QNetworkRequest(url));
	connect(reply, &QNetworkReply::finished,
		this, [this, reply]() { handleGeoWeatherData(reply); });
}
void qHome::handleGeoWeatherData(QNetworkReply* networkReply) { //where weather data is proccessed
	if (!networkReply) {
		QMessageBox message;
		message.setText("No network reply for weather");
		message.setWindowTitle("Error");
		message.setWindowIcon(QIcon("img/warningImage"));
		message.exec();
		return;
	}
	//parse JSON reply from open weather API
	QJsonDocument document = QJsonDocument::fromJson(networkReply->readAll());
	string tempWeatherDesc = "";
	QString temprature, humidity, nightDay = "";
	int wethID = 0;
	QJsonObject tempObject;
	QJsonValue val;
	QJsonObject obj = document.object();
	QJsonObject jo = document.object();
	val = obj.value(QStringLiteral("weather"));
	QJsonArray weatherArray = val.toArray();
	val = weatherArray.at(0);
	tempObject = val.toObject();
	tempWeatherDesc = tempObject.value(QStringLiteral("description")).toString().toStdString();
	wethID = tempObject.value(QStringLiteral("id")).toInt();
	nightDay = tempObject.value(QStringLiteral("icon")).toString();
	val = obj.value(QStringLiteral("main"));
	tempObject = val.toObject();
	val = tempObject.value(QStringLiteral("temp")); //get temp in kelvin
	double tempCel = val.toDouble() - 273.15;
	double tempFar = tempCel;
	tempFar *= (9.0 / 5.0);
	tempFar += 32.0;
	temprature.setNum((int)tempFar);
	temprature += 176;
	temprature += "F / ";
	temprature += QString::number((int)tempCel);
	temprature += 176;
	temprature += "C";
	tempWeatherDesc[0] -= 32;
	for (int i = 0; i < tempWeatherDesc.length(); i++) { // fixes capitalization 
		if (tempWeatherDesc[i] == ' ' && !isupper(tempWeatherDesc[i + 1])) {
			tempWeatherDesc[i + 1] -= 32;
		}
	}
	QString weatherDesc = QString::fromStdString(tempWeatherDesc);
	QString wInfo = userCity + "\n" + weatherDesc + "\n" + temprature + "\n";
	ui.wethInfo->setText(wInfo);
	if (wethID > 800 && wethID < 805) { //cloudy
		QPixmap pic("img/cloudy");
		wethIcon->setPixmap(pic.scaled(screenHeight / 13, screenHeight / 13));
	}
	else if (wethID > 499 && wethID < 532) { //rain
		QPixmap pic("img/rainy");
		wethIcon->setPixmap(pic.scaled(screenHeight / 11, screenHeight / 11));
	}
	else if (wethID > 199 && wethID < 233) { //thunderstorm
		QPixmap pic("img/thunderstorm");
		wethIcon->setPixmap(pic.scaled(screenHeight / 11, screenHeight / 11));
	}
	else if (wethID > 299 && wethID < 322) { //drizzle
		QPixmap pic("img/drizzle");
		wethIcon->setPixmap(pic.scaled(screenHeight / 12, screenHeight / 12));
	}
	else if (wethID > 599 && wethID < 623) { //snow
		QPixmap pic("img/snow");
		wethIcon->setPixmap(pic.scaled(screenHeight / 10, screenHeight / 10));
	}
	else if (wethID == 741) { // foggy
		QPixmap pic("img/foggy");
		wethIcon->setPixmap(pic.scaled(screenHeight / 10, screenHeight / 10));
	}
	else { //clear sky
		if (nightDay[2] != 'n') { // check to see if day or night
			QPixmap pic("img/clearDay");
			wethIcon->setPixmap(pic.scaled(screenHeight / 13, screenHeight / 13));
		}
		else {
			QPixmap pic("img/clearNight");
			wethIcon->setPixmap(pic.scaled(screenHeight / 10, screenHeight / 10));
		}
	}
	ui.wethIcon->addWidget(wethIcon);
	return;
}
/*Used to resize bkgd image to size of window cuz it varies with device*/
void qHome::resizeEvent(QResizeEvent* evt) {
	bkgd = bkgd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	QPalette pal; //setting window background img
	pal.setBrush(QPalette::Background, bkgd);
	this->setPalette(pal);
	QMainWindow::resizeEvent(evt);
}
void qHome::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		bkgdMenu->exec(QCursor::pos());
	}
	return;
}
/*Is called when user wants to change background image*/
void qHome::changeBackgroundImage() {
	QString newImgFilepath = QFileDialog::getOpenFileName(this,
		"Pick new background image", QDir::homePath());
	if (newImgFilepath != "") {

		if (newImgFilepath.right(4) != ".png" && newImgFilepath.right(4) != ".jpg") { //very important check
			QMessageBox message;
			message.setWindowTitle("Invalid Action");
			message.setText("Please select file with .png or .jpg extension");
			message.setWindowIcon(QIcon("img/warningImage"));
			message.exec();
			return;
		}

		QPalette pal; //setting new window background img
		bkgd = QPixmap(newImgFilepath);
		bkgd = bkgd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		pal.setBrush(QPalette::Background, bkgd);
		this->setPalette(pal);

		QFile bkgdImgFile("res/bkgdImgPathFile.txt");
		if (bkgdImgFile.open(QIODevice::WriteOnly)) {
			QTextStream bkgdImgStream(&bkgdImgFile);
			bkgdImgStream << newImgFilepath << "\n";
		}
		bkgdImgFile.close();
	}
}


