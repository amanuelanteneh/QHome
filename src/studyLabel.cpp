#include "studyLabel.h"
studyLabel::studyLabel(QWidget* parent, const QString& picPath, int w, int h) {
	wdt = w;
	hgt = h;
	studyMenu = new QMenu();
	deleteOptions = new myQListWidget();
	labelPic = new QPixmap(picPath);
	wantToDeleteFile = 0;
	wantToDeleteURL = 0;
	classFilenameToDeleteFrom = "";
	classNameToDeleteFrom = "";
	
	deleteOptions->setWindowIcon(QIcon("img/image14"));
	deleteOptions->setWindowTitle("Deletion Options");
	deleteOptions->setFont(QFont("Courier"));	addClass("res/studyOption1.txt", 1, "1");
	studyMenu->addAction("Configure Classes", this, SLOT(configureClasses()));

	connect(deleteOptions, SIGNAL(closedOut()), this, 
		SLOT(deleteOptionSelected())); //to let program know user has selected what they want to delete from class

	addClass("res/studyOption2.txt", 2, "2");
	addClass("res/studyOption3.txt", 3, "3");
	addClass("res/studyOption4.txt", 4, "4");
	addClass("res/studyOption5.txt", 5, "5");
	addClass("res/studyOption6.txt", 6, "6");
	
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));

}
studyLabel::~studyLabel() {
	delete studyMenu;
	delete deleteOptions;
	delete labelPic;
}
void studyLabel::addClass(QString classFilename, int classNumber, QString classNumberStr) {
	QFile studyOptionFile(classFilename);

	if (studyOptionFile.open(QIODevice::ReadWrite)) {
		QTextStream studyOptionStream(&studyOptionFile);
		QString line;
		line = studyOptionStream.readLine();
		
		if (line == "Valid") { //if class is being used
			line = studyOptionStream.readLine();
			QString className = line;
			switch (classNumber) { //swiches used to determine which slot to connect to class
			case 1: studyMenu->addAction(className, this, SLOT(studyOption1())); break;
			case 2: studyMenu->addAction(className, this, SLOT(studyOption2())); break;
			case 3: studyMenu->addAction(className, this, SLOT(studyOption3())); break;
			case 4: studyMenu->addAction(className, this, SLOT(studyOption4())); break;
			case 5: studyMenu->addAction(className, this, SLOT(studyOption5())); break;
			case 6: studyMenu->addAction(className, this, SLOT(studyOption6())); break;
			}
			
			while (1) { // separator
				line = studyOptionStream.readLine();
				if (line == "---------------------------------") {
					break;
				}
				switch (classNumber) {
				case 1: studyOption1LocalFiles.append(line); break;
				case 2: studyOption2LocalFiles.append(line); break;
				case 3: studyOption3LocalFiles.append(line); break;
				case 4: studyOption4LocalFiles.append(line); break;
				case 5: studyOption5LocalFiles.append(line); break;
				case 6: studyOption6LocalFiles.append(line); break;
				}
			}
			
			while (!studyOptionStream.atEnd()) {
				line = studyOptionStream.readLine();
				switch (classNumber) {
				case 1: studyOption1URLs.append(line); break;
				case 2: studyOption2URLs.append(line); break;
				case 3: studyOption3URLs.append(line); break;
				case 4: studyOption4URLs.append(line); break;
				case 5: studyOption5URLs.append(line); break;
				case 6: studyOption6URLs.append(line); break;
				}
			}
			studyOptionFile.close();
		}
	}
	return;
}
void studyLabel::configureClasses() {
	bool valid;
	QMessageBox configChoice;
	configChoice.setWindowIcon(QIcon("img/image14"));
	configChoice.setText("Select configuration option");
	configChoice.setWindowTitle("Configuration Menu");
	
	QAbstractButton* createButton = configChoice.addButton(tr("Create"), QMessageBox::ActionRole);
	QAbstractButton* modifyExistingButton = configChoice.addButton(tr("Modify Existing Class"), QMessageBox::ActionRole);
	QAbstractButton* deleteButton = configChoice.addButton(tr("Delete"), QMessageBox::ActionRole);
	QAbstractButton* cancelButton = configChoice.addButton(tr("Cancel"), QMessageBox::ActionRole);
	
	configChoice.exec();

	if (configChoice.clickedButton() == modifyExistingButton) { // to modify existing class
		QString classChoice = QInputDialog::getText(this, tr("Class Number Input"),
			tr("Enter what class number to modify (1, 2, 3, 4, 5 or 6): "), QLineEdit::Normal);
		int classNum = classChoice.toInt(&valid);
		
		if (valid && classNum < 7 && classNum > 0) {
			QString modifyFilename = "res/studyOption" + QString::number(classNum) + ".txt";
			QFile studyOptionFile(modifyFilename);
			
			if (studyOptionFile.open(QIODevice::ReadWrite)) {
				QTextStream studyOptionStream(&studyOptionFile);
				QString line;
				line = studyOptionStream.readLine();
				
				if (line == "Valid") {
					line = studyOptionStream.readLine(); //get past class name
					QMessageBox modifyChoice;
					modifyChoice.setWindowIcon(QIcon("img/image14"));
					modifyChoice.setText("Select modification option for" + line.split(".").last() + ".");
					modifyChoice.setWindowTitle("Modification Menu");
					
					QAbstractButton* addFileButton = modifyChoice.addButton(tr("Add File"), QMessageBox::ActionRole);
					QAbstractButton* deleteFileButton = modifyChoice.addButton(tr("Delete File"), QMessageBox::ActionRole);
					QAbstractButton* addURLButton = modifyChoice.addButton(tr("Add URL"), QMessageBox::ActionRole);
					QAbstractButton* deleteURLButton = modifyChoice.addButton(tr("Delete URL"), QMessageBox::ActionRole);
					
					modifyChoice.exec();
					
					if (modifyChoice.clickedButton() == addFileButton) {
						
						switch (classNum) {
						case 1: addToClass(studyOption1URLs, studyOption1LocalFiles, modifyFilename, line, 0); break;
						case 2:	addToClass(studyOption2URLs, studyOption2LocalFiles, modifyFilename, line, 0); break;
						case 3: addToClass(studyOption3URLs, studyOption3LocalFiles, modifyFilename, line, 0); break;
						case 4: addToClass(studyOption4URLs, studyOption4LocalFiles, modifyFilename, line, 0); break;
						case 5: addToClass(studyOption5URLs, studyOption5LocalFiles, modifyFilename, line, 0); break;
						case 6: addToClass(studyOption6URLs, studyOption6LocalFiles, modifyFilename, line, 0); break;
						}
					}
					else if (modifyChoice.clickedButton() == addURLButton) {
						
						switch (classNum) {
						case 1: addToClass(studyOption1URLs, studyOption1LocalFiles, modifyFilename, line, 1); break;
						case 2: addToClass(studyOption2URLs, studyOption2LocalFiles, modifyFilename, line, 1); break;
						case 3: addToClass(studyOption3URLs, studyOption3LocalFiles, modifyFilename, line, 1); break;
						case 4: addToClass(studyOption4URLs, studyOption4LocalFiles, modifyFilename, line, 1); break;
						case 5: addToClass(studyOption5URLs, studyOption5LocalFiles, modifyFilename, line, 1); break;
						case 6:	addToClass(studyOption6URLs, studyOption6LocalFiles, modifyFilename, line, 1); break;
						}
					}
					else if (modifyChoice.clickedButton() == deleteFileButton) {
						
						switch (classNum) {
						case 1: deleteFromClass(studyOption1URLs, studyOption1LocalFiles, modifyFilename, line, 0); break;
						case 2: deleteFromClass(studyOption2URLs, studyOption2LocalFiles, modifyFilename, line, 0); break;
						case 3: deleteFromClass(studyOption3URLs, studyOption3LocalFiles, modifyFilename, line, 0); break;
						case 4: deleteFromClass(studyOption4URLs, studyOption4LocalFiles, modifyFilename, line, 0); break;
						case 5: deleteFromClass(studyOption5URLs, studyOption5LocalFiles, modifyFilename, line, 0); break;
						case 6: deleteFromClass(studyOption6URLs, studyOption6LocalFiles, modifyFilename, line, 0); break;
						}
					}
					else if (modifyChoice.clickedButton() == deleteURLButton) {
						
						switch (classNum) {
						case 1: deleteFromClass(studyOption1URLs, studyOption1LocalFiles, modifyFilename, line, 1); break;
						case 2: deleteFromClass(studyOption2URLs, studyOption2LocalFiles, modifyFilename, line, 1); break;
						case 3: deleteFromClass(studyOption3URLs, studyOption3LocalFiles, modifyFilename, line, 1); break;
						case 4: deleteFromClass(studyOption4URLs, studyOption4LocalFiles, modifyFilename, line, 1); break;
						case 5: deleteFromClass(studyOption5URLs, studyOption5LocalFiles, modifyFilename, line, 1); break;
						case 6: deleteFromClass(studyOption6URLs, studyOption6LocalFiles, modifyFilename, line, 1); break;
						}
					}
					return;
				}
			}
			showMessage("This class does not exist. Please create it before modifying it.", "img/warningImage",
				"Invalid Action");
		}
		else {
			
			if (classChoice != "") {
				showMessage("Please enter a valid choice.", "img/warningImage", "Invalid Action");
			}
		}
	}
	else if (configChoice.clickedButton() == deleteButton) { //to delete a class
		QString classChoice = QInputDialog::getText(this, tr("Class Number Input"),
			tr("Enter what class number to delete (1, 2, 3, 4, 5 or 6):\t"), QLineEdit::Normal);
		int classNum = classChoice.toInt(&valid);
		
		if (valid && classNum < 7 && classNum > 0) {
			QString deleteFilename = "res/studyOption" + QString::number(classNum) + ".txt";
			
			QFile studyOptionFile(deleteFilename);
			studyOptionFile.open(QIODevice::ReadWrite);
			QTextStream studyOptionStream(&studyOptionFile);
			QString className = studyOptionStream.readLine(); //to skip "Valid" line
			className = studyOptionStream.readLine();
			studyOptionFile.close();

			studyOptionFile.open(QIODevice::WriteOnly);//switch to WriteOnly mode to clear file
			QTextStream studyOptionStreamWrite(&studyOptionFile);
			studyOptionStreamWrite << "\n"; // clears file
			studyOptionFile.close();
			QList<QAction*> actionsList = studyMenu->actions();
			int indexOfDeleteAction = -1;

			for (int i = 0; i < actionsList.length(); i++) {
				if (actionsList[i]->text().left(1).toInt() == classNum) {
					indexOfDeleteAction = i;
				}
			}
			
			if (indexOfDeleteAction != -1) {
				
				switch (classNum) { 
				case 1: studyMenu->removeAction(actionsList[indexOfDeleteAction]); studyOption1LocalFiles.clear(); studyOption1URLs.clear(); break;
				case 2: studyMenu->removeAction(actionsList[indexOfDeleteAction]); studyOption2LocalFiles.clear(); studyOption2URLs.clear(); break;
				case 3: studyMenu->removeAction(actionsList[indexOfDeleteAction]); studyOption3LocalFiles.clear(); studyOption3URLs.clear(); break;
				case 4: studyMenu->removeAction(actionsList[indexOfDeleteAction]); studyOption4LocalFiles.clear(); studyOption4URLs.clear(); break;
				case 5: studyMenu->removeAction(actionsList[indexOfDeleteAction]); studyOption5LocalFiles.clear(); studyOption5URLs.clear(); break;
				case 6: studyMenu->removeAction(actionsList[indexOfDeleteAction]); studyOption6LocalFiles.clear(); studyOption6URLs.clear(); break;
				}
				
				showMessage("Class deleted.", "img/image14", "Deletion Success");
				return;
			}
			
			else {
				showMessage("Class does not exist.", "img/image14", "Deletion Failure");
				return;
			}
		}
	
		else {
			
			if (classChoice != "") { //if statement is just so the dialog box doesn't pop up if you hit cancel or the x
				showMessage("Please enter a valid choice.", "img/warningImage", "Invalid Action\t\t");
			}
		}
	}

	else if (configChoice.clickedButton() == createButton) { //to create a class
		QString classChoice = QInputDialog::getText(this, tr("Class Creation Input"),
			tr("Enter what class number to override (1,2,3,4,5 or 6):\t"), QLineEdit::Normal);
		int classNum = classChoice.toInt(&valid);
	
		if (valid && classNum < 7 && classNum > 0) {
			createClass("res/studyOption" + QString::number(classNum) + ".txt", classNum);
		}
	
		else {
		
			if (classChoice != "") {
				showMessage("Please enter a valid choice.\t", "img/warningImage", "Invalid Action");
			}
		}
	}
	return;
}

void studyLabel::createClass(QString filename, int classNumber) {
	QFile studyOptionFile(filename);
	studyOptionFile.open(QIODevice::ReadOnly);
	QTextStream studyOptionStream(&studyOptionFile);
	QString firstLine = studyOptionStream.readLine();

	if (firstLine != "") { //check if class file is empty
		showMessage("Class already exists. Please delete it before creating.", "img/warningImage", "Invalid Action");
		return;
	}

	studyOptionFile.close();
	studyOptionFile.open(QIODevice::WriteOnly);
	QTextStream studyOptionStreamWrite(&studyOptionFile);	
	studyOptionStreamWrite << "Valid\n";
	QString className = QInputDialog::getText(this, "Class name entry",
		tr("Enter class name:\t\t"), QLineEdit::Normal);
	className = QString::number(classNumber) + ". " + className;
	studyOptionStreamWrite << className << "\n";

	QString localFilepath = "";
	QString URL = "";
	showMessage("Select which files you want to open upon clicking this class. Once all files are selected click cancel.",
		"img/image14", "File Addition Info");

	while (1) {
		localFilepath = QFileDialog::getOpenFileName(this,
			"Pick file you want opened when you click the class button. Hit cancel when done!", QDir::homePath());
		if (localFilepath == "") {
			break;
		}
		else {
			studyOptionStreamWrite << localFilepath << "\n";
		}
	}
	studyOptionStreamWrite << "---------------------------------\n";

	while (1) {
		URL = QInputDialog::getText(this, tr("Webpage selection"),
			tr("Enter URL you want opened when clicking this class. Hit cancel when done!"), QLineEdit::Normal);
		if (URL == "") {
			break;
		}
		else {
			studyOptionStreamWrite << URL << "\n";
		}
	}

	studyOptionFile.close();
	studyOptionFile.open(QIODevice::ReadOnly);
	QTextStream studyOptionStreamRead(&studyOptionFile);

	switch (classNumber) { //to determine which slot to connect to class
	case 1: studyMenu->addAction(className, this, SLOT(studyOption1())); break;
	case 2: studyMenu->addAction(className, this, SLOT(studyOption2())); break;
	case 3: studyMenu->addAction(className, this, SLOT(studyOption3())); break;
	case 4: studyMenu->addAction(className, this, SLOT(studyOption4())); break;
	case 5: studyMenu->addAction(className, this, SLOT(studyOption5())); break;
	case 6: studyMenu->addAction(className, this, SLOT(studyOption6())); break;
	}

	QString line;
	line = studyOptionStreamRead.readLine(); //skip valid check line
	line = studyOptionStreamRead.readLine(); //skip class name line

	while (1) { // separator
		line = studyOptionStreamRead.readLine();
		if (line == "---------------------------------") {
			break;
		}
		switch (classNumber) {
		case 1: studyOption1LocalFiles.append(line); break;
		case 2: studyOption2LocalFiles.append(line); break;
		case 3: studyOption3LocalFiles.append(line); break;
		case 4: studyOption4LocalFiles.append(line); break;
		case 5: studyOption5LocalFiles.append(line); break;
		case 6: studyOption6LocalFiles.append(line); break;
		}
	}

	while (!studyOptionStreamRead.atEnd()) {
		line = studyOptionStreamRead.readLine();
		switch (classNumber) {
		case 1: studyOption1URLs.append(line); break;
		case 2: studyOption2URLs.append(line); break;
		case 3: studyOption3URLs.append(line); break;
		case 4: studyOption4URLs.append(line); break;
		case 5: studyOption5URLs.append(line); break;
		case 6: studyOption6URLs.append(line); break;
		}
	}
	studyOptionFile.close();
	showMessage("Class created.\t\t\t\t", "img/image14", "Creation Success");
	return;
}

void studyLabel::addToClass(QVector<QString>& urlVector, QVector<QString>& fileVector,
	QString filename, QString className, bool addingURL) { //pass vector by refrence to modify it fr

	if (addingURL) {
		while (1) {
			QString url = QInputDialog::getText(this, tr("Webpage addition\t\t"),
				tr("Enter URL you want add. Hit cancel when done!"), QLineEdit::Normal);
			if (url == "") {
				break;
			}
			else {
				urlVector.append(url);
			}
		}
		QFile studyOptionFile(filename);
		studyOptionFile.open(QIODevice::WriteOnly);
		QTextStream studyOptionStream(&studyOptionFile);
		studyOptionStream << "Valid\n";
		studyOptionStream << className << "\n";
		for (int i = 0; i < fileVector.size(); i++) {
			studyOptionStream << fileVector[i] << "\n";
		}
		studyOptionStream << "---------------------------------\n";
		for (int i = 0; i < urlVector.size(); i++) {
			studyOptionStream << urlVector[i] << "\n";
		}
		studyOptionFile.close();
	}

	else {
		while (1) {
			QString localFilepath = QFileDialog::getOpenFileName(this,
				"Pick file you want to add. Hit cancel when done!", QDir::homePath());
			if (localFilepath == "") {
				break;
			}
			else {
				fileVector.append(localFilepath);
			}
		}
		QFile studyOptionFile(filename);
		studyOptionFile.open(QIODevice::WriteOnly);
		QTextStream studyOptionStream(&studyOptionFile);
		studyOptionStream << "Valid\n";
		studyOptionStream << className << "\n";
		for (int i = 0; i < fileVector.size(); i++) {
			studyOptionStream << fileVector[i] << "\n";
		}
		studyOptionStream << "---------------------------------\n";
		for (int i = 0; i < urlVector.size(); i++) {
			studyOptionStream << urlVector[i] << "\n";
		}
		studyOptionFile.close();
	}
	return;
}
/* Two lines in the below function make the ToDelete vectors point to address of the vectors you want it to delete contents
* of. A signal mapper could have been used instead but this seemed like somehthing cool to try to get more 
* experinces working  with refrences and pointers. This won't cause null pointer errors since urlVector and
* fileVector have to be non-NULL to reach this point.
*/
void studyLabel::deleteFromClass(QVector<QString>& urlVector, QVector<QString>& fileVector,
	QString filename, QString className, bool removingURL) {
	deleteOptions->clear();
	QStringList optionList;
	classFilenameToDeleteFrom = filename; //for deleteOptionSelected slot 
	classNameToDeleteFrom = className;

	if (removingURL) {
		wantToDeleteURL = 1; // ibid
		urlVectorToDelete = &urlVector;
		fileVectorToDelete = &fileVector;
		for (int i = 0; i < urlVector.size(); i++) {
			optionList << urlVector[i];
		}
		deleteOptions->addItems(optionList);
		QListWidgetItem* item;
		for (int i = 0; i < deleteOptions->count(); i++) {
			item = deleteOptions->item(i);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
		}
		showMessage("Select items you want to delete then close the window.", "img/image14", "Deletion Info");
		deleteOptions->show();
	}

	else {
		wantToDeleteFile = 1; //for deleteOptionSelected slot
		fileVectorToDelete = &fileVector; //ibid, see larger comment
		urlVectorToDelete = &urlVector;
		for (int i = 0; i < fileVector.size(); i++) {
			optionList << fileVector[i];
		}
		deleteOptions->addItems(optionList);
		QListWidgetItem* item;
		for (int i = 0; i < deleteOptions->count(); i++) {
			item = deleteOptions->item(i);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
		}
		showMessage("Select items you want to delete then close the window.", "img/image14", "Deletion Info");
		deleteOptions->show();
	}
	return;
}
void studyLabel::deleteOptionSelected() {
	QListWidgetItem* item;

	if (wantToDeleteFile) {
		fileVectorToDelete->clear();
		for (int i = 0; i < deleteOptions->count(); i++) { //add unchecked items to new fileVector
			item = deleteOptions->item(i);
			if (item->checkState() == Qt::Unchecked) {
				fileVectorToDelete->append(item->text());
			}
		}
		wantToDeleteFile = 0;
	}

	else if (wantToDeleteURL) {
		urlVectorToDelete->clear();
		for (int i = 0; i < deleteOptions->count(); i++) {
			item = deleteOptions->item(i);
			if (item->checkState() == Qt::Unchecked) {
				urlVectorToDelete->append(item->text());
			}
		}
		wantToDeleteURL = 0;
	}
	QFile studyOptionFile(classFilenameToDeleteFrom);  //change class file before exiting
	studyOptionFile.open(QIODevice::WriteOnly);
	QTextStream studyOptionStream(&studyOptionFile);
	studyOptionStream << "Valid\n";
	studyOptionStream << classNameToDeleteFrom << "\n";

	for (int i = 0; i < fileVectorToDelete->size(); i++) {
		studyOptionStream << (*fileVectorToDelete)[i] << "\n"; //derefrence pointer to vectors
	}
	studyOptionStream << "---------------------------------\n";

	for (int i = 0; i < urlVectorToDelete->size(); i++) {
		studyOptionStream << (*urlVectorToDelete)[i] << "\n";
	}

	studyOptionFile.close();
	classFilenameToDeleteFrom = "";
	classNameToDeleteFrom = "";
	return;
}
void studyLabel::studyOption1() {
	int localFileVecSize = studyOption1LocalFiles.size();
	int urlVecSize = studyOption1URLs.size();

	for (int i = 0; i < localFileVecSize; i++) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(studyOption1LocalFiles[i]));
	}
	for (int j = 0; j < urlVecSize; j++) {
		QDesktopServices::openUrl(QUrl(studyOption1URLs[j]));
	}
	return;
}
void studyLabel::studyOption2() {
	int localFileVecSize = studyOption2LocalFiles.size();
	int urlVecSize = studyOption2URLs.size();

	for (int i = 0; i < localFileVecSize; i++) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(studyOption2LocalFiles[i]));
	}
	for (int j = 0; j < urlVecSize; j++) {
		QDesktopServices::openUrl(QUrl(studyOption2URLs[j]));
	}
	return;
}
void studyLabel::studyOption3() {
	int localFileVecSize = studyOption3LocalFiles.size();
	int urlVecSize = studyOption3URLs.size();

	for (int i = 0; i < localFileVecSize; i++) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(studyOption3LocalFiles[i]));
	}
	for (int j = 0; j < urlVecSize; j++) {
		QDesktopServices::openUrl(QUrl(studyOption3URLs[j]));
	}
	return;
}
void studyLabel::studyOption4() {
	int localFileVecSize = studyOption4LocalFiles.size();
	int urlVecSize = studyOption4URLs.size();

	for (int i = 0; i < localFileVecSize; i++) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(studyOption4LocalFiles[i]));
	}
	for (int j = 0; j < urlVecSize; j++) {
		QDesktopServices::openUrl(QUrl(studyOption4URLs[j]));
	}
	return;
}
void studyLabel::studyOption5() {
	int localFileVecSize = studyOption5LocalFiles.size();
	int urlVecSize = studyOption5URLs.size();
	for (int i = 0; i < localFileVecSize; i++) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(studyOption5LocalFiles[i]));
	}
	for (int j = 0; j < urlVecSize; j++) {
		QDesktopServices::openUrl(QUrl(studyOption5URLs[j]));
	}
	return;
}
void studyLabel::studyOption6() {
	int localFileVecSize = studyOption6LocalFiles.size();
	int urlVecSize = studyOption6URLs.size();
	for (int i = 0; i < localFileVecSize; i++) {
		QDesktopServices::openUrl(QUrl::fromLocalFile(studyOption6LocalFiles[i]));
	}
	for (int j = 0; j < urlVecSize; j++) {
		QDesktopServices::openUrl(QUrl(studyOption6URLs[j]));
	}
	return;
}
void studyLabel::mousePressEvent(QMouseEvent* event) {
	studyMenu->exec(QCursor::pos());
	emit clicked();
}
void studyLabel::mouseReleasedEvent(QMouseEvent* event) {
}
void studyLabel::enterEvent(QEvent* event) {
	this->setPixmap(labelPic->scaled(wdt * 1.1, hgt * 1.1, Qt::KeepAspectRatio));
}
void studyLabel::leaveEvent(QEvent* event) {
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}
void studyLabel::showMessage(QString text, QString iconPath, QString title) {
	QMessageBox message;
	message.setText(text);
	message.setWindowIcon(QIcon(iconPath));
	message.setWindowTitle(title);
	message.exec();
	return;
}