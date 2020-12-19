#include "musicLabel.h"
#define CLIENT_ID "a14f16defc434d5c9574d98fc2bde945" //Stuff for spotify connect API
#define CLIENT_SEC "ea84844e954348779762db488e4a4da9"
musicLabel::musicLabel(QWidget* parent, const QString& picPath, int w, int h) {
	wdt = w;
	hgt = h;
	labelPic = new QPixmap(picPath);
	spotifyReplyHandler = new QOAuthHttpServerReplyHandler(1337, this);
	albumRefreshTimer = new QTimer(this);
	musicControlMenu = new QMenu();
	albumArtDownloader = nullptr;
	currentPlayingSong = { "", "", "" };
	currentPlaylist = "";
	userName = "";
	isAccessGranted = 0;
	
	//initalize menu options
	musicControlMenu->addAction("Start", this, SLOT(startMusic()));
	musicControlMenu->addAction("Play", this, SLOT(playMusic()));
	musicControlMenu->addAction("Pause", this, SLOT(pauseMusic()));
	musicControlMenu->addAction("Next", this, SLOT(nextMusic()));
	musicControlMenu->addAction("Previous", this, SLOT(prevMusic()));
	musicControlMenu->addAction("Queue Song", this, SLOT(queueMusic()));
	musicControlMenu->addAction("Adjust Volume", this, SLOT(changeVolume()));
	musicControlMenu->addAction("Currently Playing", this, SLOT(currentMusic()));
	
	//initalize spotify API reply handler
	spotifyReplyHandler->setCallbackPath("callback");
	spotify.setNetworkAccessManager(new QNetworkAccessManager(this));
	spotify.setReplyHandler(spotifyReplyHandler);
	spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
	spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
	
	//set permissions
	spotify.setScope("user-modify-playback-state user-read-playback-state user-read-recently-played user-read-private user-top-read playlist-read-private playlist-modify-public playlist-modify-private");
	spotify.setClientIdentifier(CLIENT_ID);
	spotify.setClientIdentifierSharedKey(CLIENT_SEC);

	//using new connect syntax
	connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
		&QDesktopServices::openUrl);

	connect(&spotify, &QOAuth2AuthorizationCodeFlow::statusChanged,
		this, &musicLabel::authenticationStatusChanged);

	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}

musicLabel::~musicLabel() {
	delete labelPic;
	delete musicControlMenu;
	delete spotifyReplyHandler;
	delete albumRefreshTimer;
	delete albumArtDownloader;
	for (int k = 0; k < playlists.size(); k++) {
		delete playlists[k].songs;
	}
}
void musicLabel::startMusic() {
	if (!isAccessGranted) {
		spotify.grant();
	}
	return;
}
void musicLabel::pauseMusic() {
	if (isAccessGranted) {
		spotify.put(QUrl("https://api.spotify.com/v1/me/player/pause"));
	}
	return;
}

void musicLabel::playMusic() {
	if (isAccessGranted) {
		spotify.put(QUrl("https://api.spotify.com/v1/me/player/play"));
	}
	return;
}

void musicLabel::nextMusic() {
	if (isAccessGranted) {
		spotify.post(QUrl("https://api.spotify.com/v1/me/player/next"));
	}
	return;
}
void musicLabel::prevMusic() {
	if (isAccessGranted) {
		spotify.post(QUrl("https://api.spotify.com/v1/me/player/previous"));
	}
	return;
}
void musicLabel::currentMusic() {
	if (currentPlayingSong.artist != "" && isAccessGranted) {
		QMessageBox message;
		message.setText("Playing: '" + currentPlayingSong.name + "'\nby: " + currentPlayingSong.artist);
		message.setWindowIcon(QIcon("img/spotifyWindowIcon"));
		message.setWindowTitle("Current Song Info");
		message.setIconPixmap(*(this->pixmap())); //derefrence that stuff 
		message.exec();
		return;
	}
	showMessage("No song currently playing.", "img/spotifyWindowIcon", "Current Song Info");
	return;
}

void musicLabel::queueMusic() {
	if (!playlists.isEmpty()) {
		QStringList optionList;
		optionList << "";
		for (int h = 0; h < playlists.size(); h++) {
			optionList << playlists[h].name;
		}
		QString playlistName = QInputDialog::getItem(this, "Choose playlist to queue song from",
			"Playlists:\t\t\t\t\t\t\t", optionList, 0, false); //set editable to false
		bool playlistPicked = 0;
		int index = -1;
		for (int i = 0; i < playlists.size(); i++) {
			if (playlists[i].name == playlistName) {
				playlistPicked = 1;
				index = i;
			}
		}
		if (!playlistPicked) return; // if user didn't pick a playlist exit
		if (!playlists[index].songs->isEmpty()) {
			QMapIterator<QString, Song> iter(*(playlists[index].songs));
			QStringList optionList;
			optionList << "";
			while (iter.hasNext()) {
				iter.next();
				optionList << iter.key();
			}
			QString songToQueue = "";
			while (1) {
				songToQueue = QInputDialog::getItem(this, "Choose song to queue",
					"Songs:\t\t\t\t\t\t", optionList, 0, false); //set editable to false
				if (songToQueue != "") {
					spotify.post("https://api.spotify.com/v1/me/player/queue?uri=" + (*playlists[index].songs)[songToQueue].uri);
				}
				else {
					break;
				}
			}
		}
		else {
			showMessage("No songs in playlist.", "img/spotifyWindowIcon", "Music Info");
		}
	}
	else {
		showMessage("User has no playlists to get songs from.", "img/spotifyWindowIcon", "Music Info");
	}
	return;
}

void musicLabel::changeVolume() {
	if (isAccessGranted) {
		auto reply = spotify.get(QUrl("https://api.spotify.com/v1/me/player"));
		connect(reply, &QNetworkReply::finished, [=]() {
			if (reply->error() != QNetworkReply::NoError) {
				showMessage(reply->errorString(), "img/warningImage", "Music Info");
				return;
			}
			auto data = reply->readAll();
			auto document = QJsonDocument::fromJson(data);
			auto root = document.object();
			int currentVolume = root["device"].toObject()["volume_percent"].toInt();

			bool valid;
			int newVolume = QInputDialog::getInt(this, "Volume Input",
				"Current volume: " + QString::number(currentVolume) + "%\t", currentVolume, 0, 100, 5, &valid);
			if (valid) {
				spotify.put(QUrl("https://api.spotify.com/v1/me/player/volume?volume_percent=" + QString::number(newVolume)));
			}
			}
		);
	}
	return;
}

void musicLabel::authenticationStatusChanged(QAbstractOAuth::Status status) {

	if (status == QAbstractOAuth::Status::Granted) {

		if (userName == "" && playlists.isEmpty()) {
			//first get username 
			auto reply = spotify.get(QUrl("https://api.spotify.com/v1/me"));
			connect(reply, &QNetworkReply::finished, [=]() {
				if (reply->error() != QNetworkReply::NoError) { //check for network reply error
					showMessage(reply->errorString(), "img/warningImage", "Music Info");
					return;
				}
				
				//parse JSON reply
				auto data = reply->readAll(); 
				auto document = QJsonDocument::fromJson(data);
				auto root = document.object();
				userName = root["id"].toString();

				connect(albumRefreshTimer, SIGNAL(timeout()), this, SLOT(checkForPlaybackChange())); //start timer only when access granted
				albumRefreshTimer->start(1000); //check if current song changed every 1 seconds
				reply->deleteLater();
				});

			getPlaylists();

			isAccessGranted = 1; //do at end
		}
	}
	else if (status == QAbstractOAuth::Status::RefreshingToken) {
		showMessage("Refreshing Token", "img/spotifyWindowIcon", "Music Info");
	}
	else if (status == QAbstractOAuth::Status::NotAuthenticated) {
		isAccessGranted = 0;
		showMessage("Not authenticated please restart application", "img/spotifyWindowIcon", "Music Info");
	}
	else if (status == QAbstractOAuth::Status::TemporaryCredentialsReceived) {
		return;
	}
	return;
}
void musicLabel::getPlaylists() {

	auto playlistReply = spotify.get(QUrl("https://api.spotify.com/v1/me/playlists"));

	connect(playlistReply, &QNetworkReply::finished, [=]() {
		if (playlistReply->error() != QNetworkReply::NoError) {
			showMessage(playlistReply->errorString(), "img/warningImage", "Music Info");
			return;
		}

		auto playlistData = playlistReply->readAll();
		auto playlistDocument = QJsonDocument::fromJson(playlistData);
		auto playlistRoot = playlistDocument.object();
		auto playlistItems = playlistRoot["items"].toArray();

		int numPlaylists = playlistItems.size();
		for (int i = 0; i < numPlaylists; i++) { //for each playlist
		
			Playlist tempPlaylist = { playlistItems[i].toObject()["name"].toString(),
				playlistItems[i].toObject()["id"].toString(), new QMap<QString, Song> };
			QString offset = "0";
			auto contentsReply = spotify.get(QUrl("https://api.spotify.com/v1/playlists/" + tempPlaylist.id + "/tracks?offset=" + offset));

			connect(contentsReply, &QNetworkReply::finished, [=]() {
				if (contentsReply->error() != QNetworkReply::NoError) {
					showMessage(contentsReply->errorString(), "img/warningImage", "Music Info");
					return;
				}

				auto contentsData = contentsReply->readAll();
				auto contentsDocument = QJsonDocument::fromJson(contentsData);
				auto contentsRoot = contentsDocument.object();
				auto contentsItems = contentsRoot["items"].toArray();
				int numSongs = contentsItems.size();

				for (int j = 0; j < numSongs; j++) {
					Song tempSong = { contentsItems[j].toObject()["track"].toObject()["name"].toString(),
									contentsItems[j].toObject()["track"].toObject()["album"].toObject()["artists"].toArray()[0].toObject()["name"].toString(),
									contentsItems[j].toObject()["track"].toObject()["uri"].toString() };
					tempPlaylist.songs->insert(tempSong.name + " by: " + tempSong.artist, tempSong);
				}
				//allows app to get at most 200 songs from playlist since API only returns at most 100 songs per call
				if (numSongs == 100) { 
					auto contentsReply2 = spotify.get(QUrl("https://api.spotify.com/v1/playlists/" + tempPlaylist.id + "/tracks?offset=100"));
					connect(contentsReply2, &QNetworkReply::finished, [=]() {
						if (contentsReply2->error() != QNetworkReply::NoError) {
							showMessage(contentsReply2->errorString(), "img/warningImage", "Music Info");
							return;
						}

						auto contentsData2 = contentsReply2->readAll();
						auto contentsDocument2 = QJsonDocument::fromJson(contentsData2);
						auto contentsRoot2 = contentsDocument2.object();
						auto contentsItems2 = contentsRoot2["items"].toArray();

						int numSongs2 = contentsItems2.size();
						for (int f = 0; f < numSongs2; f++) {
							Song tempSong2 = { contentsItems2[f].toObject()["track"].toObject()["name"].toString(),
											contentsItems2[f].toObject()["track"].toObject()["album"].toObject()["artists"].toArray()[0].toObject()["name"].toString(),
											contentsItems2[f].toObject()["track"].toObject()["uri"].toString() };
							tempPlaylist.songs->insert(tempSong2.name, tempSong2);
						}
						});
				}
				});
			playlists.append(tempPlaylist);
		}
		});
}

//called when program thinks song has changed
void musicLabel::refreshAlbumArt() {

	auto reply = spotify.get(QUrl("https://api.spotify.com/v1/me/player/currently-playing"));

	connect(reply, &QNetworkReply::finished, [=]() {
		if (reply->error() != QNetworkReply::NoError) {
			showMessage(reply->errorString(), "img/warningImage", "Music Info");
			return;
		}

		auto data = reply->readAll();
		auto document = QJsonDocument::fromJson(data);
		auto root = document.object();
		auto images = root["item"].toObject()["album"].toObject()["images"].toArray();

		QString imageURL = images[1].toObject()["url"].toString();
		QUrl imageUrl(imageURL);
		delete albumArtDownloader;
		albumArtDownloader = new imageDownloader(imageUrl, this);
		connect(albumArtDownloader, SIGNAL(downloaded()), this, SLOT(changeToAlbumArt()));
		reply->deleteLater();
		});

	return;
}

void musicLabel::mousePressEvent(QMouseEvent* event) {
	musicControlMenu->exec(QCursor::pos());
	return;
}
void musicLabel::mouseReleasedEvent(QMouseEvent* event) {
	return;
}
void musicLabel::enterEvent(QEvent* event) {
	this->setPixmap(labelPic->scaled(wdt * 1.1, hgt * 1.1, Qt::KeepAspectRatio));
	return;
}
void musicLabel::leaveEvent(QEvent* event) {
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
	return;
}
void musicLabel::changeToAlbumArt() {
	labelPic->loadFromData(albumArtDownloader->downloadedData());
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
	disconnect(albumArtDownloader, SIGNAL(downloaded()), this, SLOT(changeToAlbumArt()));
	return;
}
void musicLabel::checkForPlaybackChange() {

	if (isAccessGranted && userName != "") {
		auto reply = spotify.get(QUrl("https://api.spotify.com/v1/me/player/devices"));
		connect(reply, &QNetworkReply::finished, [=]() { //check for active device first
			if (reply->error() != QNetworkReply::NoError) {
				showMessage(reply->errorString(), "img/warningImage", "Music Info");
				return;
			}
			auto data = reply->readAll();
			auto document = QJsonDocument::fromJson(data);
			auto root = document.object();
			auto devices = root["devices"].toArray();
			if (devices.isEmpty()) {
				isAccessGranted = 0; //so next message doesn't pop up every 3 seconds	
				disconnect(albumRefreshTimer, SIGNAL(timeout()), this, SLOT(checkForPlaybackChange()));
				showMessage("No active devices found. Please click the 'Start' option again after opening the spotify desktop app or web player.", "img/spotifyWindowIcon", "Music Info");
			}
			else if (devices[0].toObject()["is_active"].toBool() == false) { //just check first device
				isAccessGranted = 0;
				disconnect(albumRefreshTimer, SIGNAL(timeout()), this, SLOT(checkForPlaybackChange()));
				showMessage("Device found but player inactive. Please start playing song before connecting.", "img/spotifyWindowIcon", "Music Info");
			}
			reply->deleteLater();
			});
		auto replyCurrentSong = spotify.get(QUrl("https://api.spotify.com/v1/me/player/currently-playing"));
		connect(replyCurrentSong, &QNetworkReply::finished, [=]() { // now check if song is different
			if (replyCurrentSong->error() != QNetworkReply::NoError) {
				showMessage(replyCurrentSong->errorString(), "img/warningImage", "Music Info");
				return;
			}
			//to catch if user doesn't have an active session playing
			if (isAccessGranted) { 
				auto data = replyCurrentSong->readAll();
				auto document = QJsonDocument::fromJson(data);
				auto root = document.object();

				auto artist = root["item"].toObject()["album"].toObject()["artists"].toArray();

				if (currentPlayingSong.uri != artist[0].toObject()["uri"].toString()) {
					refreshAlbumArt();
				}
				currentPlayingSong.artist = artist[0].toObject()["name"].toString();
				auto uri = root["item"].toObject()["uri"];
				currentPlayingSong.uri = uri.toString();
				auto name = root["item"].toObject()["name"];
				currentPlayingSong.name = name.toString();
			}
			replyCurrentSong->deleteLater();
			});
	}
	return;
}

void musicLabel::showMessage(QString text, QString iconPath, QString title) {
	QMessageBox message;
	message.setText(text);
	message.setWindowIcon(QIcon(iconPath));
	message.setWindowTitle(title);
	message.exec();
	return;
}

