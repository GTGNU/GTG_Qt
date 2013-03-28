#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include <QtQuick/QQuickView>

class MainWindow
	: public QQuickView
{
	Q_OBJECT

	public:
		MainWindow(QString qmlPath, QWidget* parent=nullptr);
		~MainWindow();

	private:
		QString m_qmlPath;
};

#endif
