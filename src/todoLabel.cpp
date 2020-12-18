#include "todoLabel.h"
todoLabel::todoLabel(QWidget* parent, const QString& picPath, int w, int h) {
	wdt = w;
	hgt = h;
	theTodoList = new QTextEdit();
	QDesktopWidget desktop; //to get screen dimenstions
	int screenHeight = desktop.geometry().height();
	int screenWidth = desktop.geometry().width();
	theTodoList->setWindowIcon(QIcon("img/image14"));
	theTodoList->setWindowTitle("To-Do List");
	theTodoList->setFontPointSize((int)((screenHeight / 82) + 2));
	theTodoList->setFixedWidth(screenWidth / 5);
	theTodoList->setFixedHeight(screenWidth / 5);
	theTodoList->setFont(QFont("Courier"));
	connect(theTodoList, SIGNAL(textChanged()), this, //textChanged emitted when...text changes
		SLOT(toDoListChanged())); // connect textChanged signal to toDoListChanged slot	

	labelPic = new QPixmap(picPath);
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
	//this->setGraphicsEffect(new QGraphicsBlurEffect);
}

todoLabel::~todoLabel() {
	delete theTodoList;
	delete labelPic;
}

void todoLabel::mousePressEvent(QMouseEvent* event) {
	QFile todoListFile("res/todoList.txt");
	QString todoList = "";
	if (todoListFile.open(QIODevice::ReadWrite)) {
		QTextStream todoListStream(&todoListFile);
		QString line;
		while (!todoListStream.atEnd()) {
			line = todoListStream.readLine();	
			todoList += line;
			todoList += "\n";
		}
		todoListFile.close();
		theTodoList->clear();
		QDesktopWidget desktop; //to get screen dimenstions
		int screenHeight = desktop.geometry().height();
		int screenWidth = desktop.geometry().width();
		theTodoList->setFontPointSize(((int)(screenHeight / 82) + 2));
		theTodoList->append(todoList);
		theTodoList->show();
	}
	emit clicked();
}
void todoLabel::mouseReleasedEvent(QMouseEvent* event) {
	emit released();
}
void todoLabel::enterEvent(QEvent* event) {
	//	this->setGraphicsEffect(nullptr);
	this->setPixmap(labelPic->scaled(wdt * 1.1, hgt * 1.1, Qt::KeepAspectRatio));
}
void todoLabel::leaveEvent(QEvent* event) {
	//	this->setGraphicsEffect(new QGraphicsBlurEffect);
	this->setPixmap(labelPic->scaled(wdt, hgt, Qt::KeepAspectRatio));
}
void todoLabel::toDoListChanged() { // if text changes in todo list
	QString newTodoList = theTodoList->toPlainText();
	QFile todoListFile("res/todoList.txt");  //change class file before exiting
	todoListFile.open(QIODevice::WriteOnly);
	QTextStream todoListStream(&todoListFile);
	todoListStream << newTodoList;
	todoListFile.close();
}