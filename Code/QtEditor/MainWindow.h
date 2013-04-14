#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>

#include "TopPanel.h"
#include "MapDisplay.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow();
	~MainWindow();

protected:
	QVBoxLayout* layout;

	TopPanel* topPanel;
	MapDisplay* mapDisplay;
	QScrollArea* mapArea;
};

#endif
