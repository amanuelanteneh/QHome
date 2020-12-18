#include "myQListWidget.h"
void myQListWidget::closeEvent(QCloseEvent* event) {
    emit closedOut();
    event->accept();
}
