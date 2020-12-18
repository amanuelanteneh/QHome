#pragma once
#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

/* This class was made for downlading the album art of the song the user is listening to and setting the
    musicLabel icon pixmap to it. */

class imageDownloader : public QObject {
   Q_OBJECT

public:
    explicit imageDownloader(QUrl imageUrl, QObject* parent = Q_NULLPTR);
    ~imageDownloader();
    QByteArray downloadedData() const;

signals:
    void downloaded();

private slots:
    void imageDownloaded(QNetworkReply* pReply);

private:
    QNetworkAccessManager webCtrl;
    QByteArray downloadedImgData;

};
#endif // !IMAGEDOWNLOADER_H

