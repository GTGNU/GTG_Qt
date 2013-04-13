#pragma once

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtCore/QDir>
#include <QtCore/QVector>
#include <QtWidgets/QPushButton>

class TileChooser : public QPushButton
{
	Q_OBJECT

public:
	TileChooser(const QString& path);

	const QIcon* getCurrentTile() const;

protected:
	int currentTileIndex;

	QVector<const QIcon*> tileList;

public slots:
	void releasedHandler();
};
