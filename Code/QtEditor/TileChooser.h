#pragma once

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtCore/QDir>
#include <QtWidgets/QPushButton>

#include <vector>

class TileChooser : public QPushButton
{
	Q_OBJECT

public:
	TileChooser(const QString& path);

	const QIcon* getCurrentTile() const;

protected:
	int currentTileIndex;

	std::vector<const QIcon*> tileList;

public slots:
	void releasedHandler();
};
