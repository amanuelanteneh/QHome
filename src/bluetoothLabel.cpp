#include "bluetoothLabel.h"
bluetoothLabel::bluetoothLabel(QWidget* parent, const QString& picPath, int w, int h) {
	wdt = w;
	hgt = h;
	connectedDeviceIndex = -1;
	connectedToDevice = 0;
	bluetoothMenu = new QMenu();
	devicesMenu = new QMenu();
	labelPic = new QPixmap(picPath);
	foundDeviceOptions = new myQListWidget();
	device = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
	btDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);


	foundDeviceOptions->setWindowIcon(QIcon("img/bluetoothImage"));
	foundDeviceOptions->setWindowTitle("Discovered Bluetooth Devices");
	bluetoothMenu->addAction("Add device", this, SLOT(addDevice()));
	bluetoothMenu->addAction("Connect to device", this, SLOT(deviceOptions()));
	bluetoothMenu->addAction("Remove a device", this, SLOT(removeDevice()));
	btDiscoveryAgent->setLowEnergyDiscoveryTimeout(6000);

	connect(foundDeviceOptions, SIGNAL(closedOut()), this, 
		SLOT(deviceAdditionSelected()));

	connect(btDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
		this, &bluetoothLabel::deviceDiscovered);

	connect(btDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, 
		this, &bluetoothLabel::finishedScan);

	connect(btDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, 
		this, &bluetoothLabel::finishedScan);

	connect(device, SIGNAL(connected()), this, SLOT(deviceConnected()));

	connect(device, SIGNAL(disconnected()), this, SLOT(deviceDisconnected()));

	refreshDevices();

	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}
bluetoothLabel::~bluetoothLabel() {
	if (device->state() == QBluetoothSocket::ConnectedState) {
		device->disconnectFromService();
	}
	delete device;
	delete labelPic;
	delete bluetoothMenu;
	delete foundDeviceOptions;
}
void bluetoothLabel::addDevice() {
	btDiscoveryAgent->start();
	return;
}
void bluetoothLabel::deviceDiscovered(const QBluetoothDeviceInfo& device) {
	//check if headphones or speaker
	if (device.minorDeviceClass() == QBluetoothDeviceInfo::Headphones || device.minorDeviceClass() == QBluetoothDeviceInfo::Loudspeaker) {
		foundDeviceNames.append(device.name());
		foundDeviceIds.append(device.address().toString());
	}
	return;
}
void bluetoothLabel::finishedScan() {

	foundDeviceOptions->clear();
	QStringList optionList;
	
	for (int i = 0; i < foundDeviceNames.size(); i++) {
		optionList << foundDeviceNames[i];
	}
	
	foundDeviceOptions->addItems(optionList); 
	foundDeviceOptions->setSelectionMode(QAbstractItemView::SingleSelection);
	showMessage("Select the device you want to add then close the window.", "img/bluetoothImage", "Add BT Device Info");
	foundDeviceOptions->show();
	return;
}
void bluetoothLabel::deviceAdditionSelected() {
	QList<QListWidgetItem*> selected = foundDeviceOptions->selectedItems();

	if (selected.length() == 1) {
		bool valid;
		int deviceIndex = foundDeviceOptions->row(selected[0]);

		QString deviceNumChoice = QInputDialog::getText(this, tr("Device Number Input"),
			tr("Enter what device number to override (1,2, or 3): "), QLineEdit::Normal);
		int deviceNum = deviceNumChoice.toInt(&valid);

		if (valid && deviceNum < 4 && deviceNum > 0) {
		QFile btFile("res/btDevice" + QString::number(deviceNum) + "Info.txt");
		btFile.open(QIODevice::WriteOnly);
		QTextStream btFileStream(&btFile);
		btFileStream << "Valid\n";
		btFileStream << foundDeviceNames[deviceIndex] << "\n";
		btFileStream << foundDeviceIds[deviceIndex] << "\n";
		btFile.close();
		refreshDevices();
		}

		else {
			showMessage("Please enter a valid device number.", "img/warningImage", "Invalid Action");
		}
	}

	else {
		showMessage("No device selected.", "img/bluetoothImage", "Info");
	}
	foundDeviceIds.clear();
	foundDeviceNames.clear();
	return;
}
void bluetoothLabel::deviceConnected() {
	labelPic = new QPixmap("img/beatsConnected");
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}
void bluetoothLabel::deviceDisconnected() {
	labelPic = new QPixmap("img/beatsUnconnected");
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));	
	
	//this is in case user disconnects manually like from settings or by turning off headphones	
	device->disconnectFromService(); 
	disconnect(device, SIGNAL(connected()), this, SLOT(deviceConnected()));
	disconnect(device, SIGNAL(disconnected()), this, SLOT(deviceDisconnected()));
	device = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
	connect(device, SIGNAL(connected()), this, SLOT(deviceConnected()));
	connect(device, SIGNAL(disconnected()), this, SLOT(deviceDisconnected()));
}
void bluetoothLabel::refreshDevices() {

	for (int i = 1; i < 4; i++) {
		QFile btFile("res/btDevice" + QString::number(i) + "Info.txt");
		btFile.open(QIODevice::ReadOnly);
		QTextStream btFileStream(&btFile);
		QString line = btFileStream.readLine();

		if (line == "Valid") {
			switch (i) {
			case 1: device1Info.clear(); device1Info.append(btFileStream.readLine()); device1Info.append(btFileStream.readLine()); break;
			case 2: device2Info.clear(); device2Info.append(btFileStream.readLine()); device2Info.append(btFileStream.readLine()); break;
			case 3: device3Info.clear(); device3Info.append(btFileStream.readLine()); device3Info.append(btFileStream.readLine()); break;;
			}
		}

		else {
			switch (i) {
			case 1: device1Info.clear(); break;
			case 2: device2Info.clear(); break;
			case 3: device3Info.clear(); break;
			}
		}
		btFile.close();
	}
	return;
}
void bluetoothLabel::deviceOptions() {
	devicesMenu->clear();

	if (device1Info.isEmpty() && device2Info.isEmpty() && device3Info.isEmpty()) { //if all 3 devices don't exist
		return;
	}

	if (!device1Info.isEmpty()) {
		devicesMenu->addAction("1. " + device1Info[0], this, SLOT(bluetoothDevice1()));
	}

	if (!device2Info.isEmpty()) {
		devicesMenu->addAction("2. " + device2Info[0], this, SLOT(bluetoothDevice2()));
	}

	if (!device3Info.isEmpty()) {
		devicesMenu->addAction("3. " + device3Info[0], this, SLOT(bluetoothDevice3()));
	}

	devicesMenu->exec(QCursor::pos());
	return;
}
void bluetoothLabel::removeDevice() {

	bool valid;
	QString deviceNumChoice = QInputDialog::getText(this, tr("Device Number Input"),
		tr("Enter what device number to remove (1,2, or 3): "), QLineEdit::Normal);
	int deviceNum = deviceNumChoice.toInt(&valid);

	if (valid && deviceNum < 4 && deviceNum > 0) {
		QFile btFile("res/btDevice" + QString::number(deviceNum) + "Info.txt");
		btFile.open(QIODevice::ReadOnly);
		QTextStream btFileIsValidStream(&btFile);

		if (btFileIsValidStream.readLine() != "Valid") {
			btFile.close();
			showMessage("Device does not exist.", "img/warningImage", "Invalid Action");
		}

		btFile.close();
		btFile.open(QIODevice::WriteOnly);
		QTextStream btFileStream(&btFile);
		btFileStream << "\n"; //clear file "delete" device
		btFile.close();
		refreshDevices();
	}

	else {
		showMessage("Please enter a valid device number.", "img/warningImage", "Invalid Action");
	}

}
void bluetoothLabel::bluetoothDevice1() {

	if (device->state() == QBluetoothSocket::ConnectedState) {
		device->disconnectFromService();
	}

	if (device1Info.size() == 2) {
		device->connectToService(QBluetoothAddress(device1Info[1]), QBluetoothUuid(QBluetoothUuid::SerialPort));
	}

}
void bluetoothLabel::bluetoothDevice2() {

	if (device->state() == QBluetoothSocket::ConnectedState) {
		device->disconnectFromService();
	}

	if (device2Info.size() == 2) {
		device->connectToService(QBluetoothAddress(device2Info[1]), QBluetoothUuid(QBluetoothUuid::SerialPort));
	}
}
void bluetoothLabel::bluetoothDevice3() {

	if (device->state() == QBluetoothSocket::ConnectedState) {
		device->disconnectFromService();
	}

	if (device3Info.size() == 2) {
		device->connectToService(QBluetoothAddress(device3Info[1]), QBluetoothUuid(QBluetoothUuid::SerialPort));
	}
}
void bluetoothLabel::mousePressEvent(QMouseEvent* event) {
	bluetoothMenu->exec(QCursor::pos());
	return;
}
void bluetoothLabel::mouseReleasedEvent(QMouseEvent* event) {
	return;
}
void bluetoothLabel::enterEvent(QEvent* event) {
	this->setPixmap(labelPic->scaled(wdt * 1.1, hgt * 1.1, Qt::KeepAspectRatio));
}
void bluetoothLabel::leaveEvent(QEvent* event) {
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}
void bluetoothLabel::showMessage(QString text, QString iconPath, QString title) {
	QMessageBox message;
	message.setText(text);
	message.setWindowIcon(QIcon(iconPath));
	message.setWindowTitle(title);
	message.exec();
	return;
}
