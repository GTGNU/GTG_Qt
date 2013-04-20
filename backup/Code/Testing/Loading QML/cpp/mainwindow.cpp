#include "mainwindow.h"

#include <QtCore/QUrl>

MainWindow::MainWindow(QString qmlPath, QWidget* parent)
	: QQuickView(QUrl::fromLocalFile(qmlPath + "main_menu.qml"))
{
	connect(engine(), SIGNAL(quit()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
}

