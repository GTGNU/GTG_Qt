#include "TileButton.h"

using namespace gtgeditor;

TileButton::TileButton(const TileChooser* chooser) : m_tileChooser(chooser)
{
	m_tile = m_tileChooser->getCurrentTile();

	this->setIcon(*(m_tile->getIcon()));
	this->setIconSize(QSize(TILE_WIDTH, TILE_HEIGHT));
	this->setFixedSize(TILE_WIDTH, TILE_HEIGHT);

}

void TileButton::setTile(const Tile* tile)
{
	m_tile = tile;

	this->setIcon(*(m_tile->getIcon()));
}

const Tile* TileButton::getTile() const
{
	return m_tile;
}

void TileButton::enterEvent(QEvent* event)
{
	event->accept();

	if(QApplication::keyboardModifiers() == Qt::ControlModifier)
		emit pressed();
}
