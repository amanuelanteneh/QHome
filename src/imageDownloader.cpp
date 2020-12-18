#include "imageDownloader.h"

imageDownloader::imageDownloader(QUrl imageUrl, QObject* parent) {
	connect(&webCtrl, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(imageDownloaded(QNetworkReply*)) );

	QNetworkRequest request(imageUrl);
	webCtrl.get(request);
}
imageDownloader::~imageDownloader() { 

}

void imageDownloader::imageDownloaded(QNetworkReply* pReply) {
	downloadedImgData = pReply->readAll();
	//emit signal when downloaded
	pReply->deleteLater();
	emit downloaded();
}

QByteArray imageDownloader::downloadedData() const {

	return(downloadedImgData);

}
