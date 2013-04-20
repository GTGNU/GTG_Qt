#ifndef TOPPANEL_H
#define TOPPANEL_H

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "config.h"
#include "TileChooser.h"

class TopPanel : public QWidget
{
	Q_OBJECT

public:
	TopPanel();
	~TopPanel();

	void setShowWarning(bool value);
	const TileChooser* getTileChooser() const;

protected:
	QHBoxLayout* m_layout;
	QFormLayout* m_formLayout;
	QFormLayout* m_buttonLayout;

	TileChooser* m_tileChooser;
	QPushButton* m_openButton;
	QPushButton* m_saveButton;
	QLineEdit* m_widthLineEdit;
	QLineEdit* m_heightLineEdit;

	bool m_showWarning;

signals:
	void gridSizeChanged(const int width, const int height);
	void open();
	void save();

public slots:
	void editingFinishedHandler();
	void openHandler();
	void saveHandler();
	void mapLoadHandler(const int width, const int height);
	void mapEditedHandler();
};

#endif
