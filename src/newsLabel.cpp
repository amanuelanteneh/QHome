#include "newsLabel.h"
#define API_ID_NEWS "ad8f9ad04f6b4a7fa5bbc61226e0d2bb" //my API ID key for newspai.org

newsLabel::newsLabel(QWidget* parent, const QString& picPath, int w, int h) {
	QDesktopWidget desktop; //to get screen dimenstions
	apiReplyHandler = new QNetworkAccessManager(this);
	wdt = w;
	hgt = h;
	labelPic = new QPixmap(picPath);
	screenHeight = desktop.geometry().height();
	screenWidth = desktop.geometry().width();
	

	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}

newsLabel::~newsLabel() {
	delete labelPic;
}

void newsLabel::handleNewsData(QNetworkReply* networkReply) {
	if (!networkReply) {
		QMessageBox message;
		message.setText("No network reply for news!");
		message.setWindowTitle("Error");
		message.setWindowIcon(QIcon("img/warningImage"));
		message.exec();
		return;
	}

	auto newsData = networkReply->readAll();
	auto newsDocument = QJsonDocument::fromJson(newsData);
	auto newsRoot = newsDocument.object();
	auto newsItems = newsRoot["articles"].toArray();
	QString articles = "";
	for (int i = 0; i < newsItems.size(); i++) {
		articles += "<a href='" + newsItems[i].toObject()["url"].toString() + "'>";
		articles += newsItems[i].toObject()["title"].toString() + "</a>" + "<br><br>";
	}

	QMessageBox message;
	message.setText(articles);
	message.setWindowIcon(QIcon("img/newsIcon"));
	message.setWindowTitle("U.S. News");
	message.exec();
}


void newsLabel::mousePressEvent(QMouseEvent* event) {
	
	QUrl url("https://newsapi.org/v2/top-headlines");
	QUrlQuery query;
	query.addQueryItem("country", "us");
	query.addQueryItem("apiKey", API_ID_NEWS);
	query.addQueryItem("pageSize", "5");
	url.setQuery(query);
	QNetworkReply* reply = apiReplyHandler->get(QNetworkRequest(url));
	connect(reply, &QNetworkReply::finished,
		this, [this, reply]() { handleNewsData(reply); });
	emit clicked();
	return;
}


void newsLabel::enterEvent(QEvent* event) {
	//	this->setGraphicsEffect(nullptr);
	this->setPixmap(labelPic->scaled(wdt * 1.1, hgt * 1.1, Qt::KeepAspectRatio));
}
void newsLabel::leaveEvent(QEvent* event) {
	//	this->setGraphicsEffect(new QGraphicsBlurEffect);
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}