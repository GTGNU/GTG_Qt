#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

class MapDisplay : public QWidget
{
public:
	MapDisplay();
	~MapDisplay();

protected:
	QHBoxLayout* layout;

	QScrollArea* scrollArea;
};
