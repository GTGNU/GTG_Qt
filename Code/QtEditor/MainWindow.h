#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QCloseEvent>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>

#include "config.h"
#include "TopPanel.h"
#include "MapDisplay.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

protected:
	QVBoxLayout* layout;

	TopPanel* topPanel;
	MapDisplay* mapDisplay;
	QScrollArea* mapArea;

	bool mapEdited;

	virtual void closeEvent(QCloseEvent* event);

public slots:
	void mapEditedHandler();
	void mapResetHandler();
};

#endif
