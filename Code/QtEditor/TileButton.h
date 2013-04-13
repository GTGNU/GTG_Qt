#include <QtWidgets/QPushButton>
#include <QtGui/QIcon>

#include "TileChooser.h"

class TileButton : public QPushButton
{
	Q_OBJECT

public:
	TileButton(const TileChooser* chooser);

protected:
	const TileChooser* tileChooser;

public slots:
	void releasedHandler();
};
