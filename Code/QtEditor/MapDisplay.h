#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include <QtCore/QVector>
#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include "config.h"
#include "TileButton.h"
#include "TileChooser.h"

class MapDisplay : public QWidget
{
	Q_OBJECT

public:
	MapDisplay(const TileChooser* chooser);
	~MapDisplay();

	void setGridSize(const int width, const int height);
	QString serialize() const;

protected:
	int gridWidth;
	int gridHeight;

	QVector< QVector<TileButton*> > grid;

	QGridLayout* layout;
	const TileChooser* tileChooser;

public slots:
	void gridSizeChangedHandler(const int width, const int height);
	void resetHandler();
	void saveHandler();
};

#endif
