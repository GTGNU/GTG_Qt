#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include <vector>

class MapDisplay : public QWidget
{
public:
	MapDisplay();
	~MapDisplay();

	void setGridSize(const int width, const int height);

protected:
	int gridWidth;
	int gridHeight;

	std::vector< std::vector<QPushButton*> > grid;

	QGridLayout* layout;
};
