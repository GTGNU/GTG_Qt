#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include <vector>

#include "TileButton.h"
#include "TileChooser.h"

class MapDisplay : public QWidget
{
	Q_OBJECT

public:
	MapDisplay(const TileChooser* chooser);
	~MapDisplay();

	void setGridSize(const int width, const int height);

protected:
	int gridWidth;
	int gridHeight;

	std::vector< std::vector<TileButton*> > grid;

	QGridLayout* layout;
	const TileChooser* tileChooser;

public slots:
	void gridSizeChangedHandler(const int width, const int height);
};
