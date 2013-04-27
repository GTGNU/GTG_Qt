#include "TileChooser.h"

using namespace gtgeditor;

TileChooser::TileChooser(const QString& path) : m_currentTileIndex(0)
{
	QDir directory(path);

	for(	const QString& i
		: directory.entryList(QStringList("*.qml"), QDir::Files) ) {

		m_tileList.push_back(new Tile(path+"/"+i));
	}

	this->setIcon(*(m_tileList[m_currentTileIndex]->getIcon()));
	this->setIconSize(QSize(TILE_WIDTH, TILE_HEIGHT));

	this->connect(this, SIGNAL(released()), SLOT(releasedHandler()));
}

const QVector<const Tile*>& TileChooser::getTileList() const
{
	return m_tileList;
}

const Tile* TileChooser::getCurrentTile() const
{
	return m_tileList[m_currentTileIndex];
}

const Tile* TileChooser::getTileByName(const QString& name) const
{
	const Tile* result = NULL;

	for(int i = 0; i < m_tileList.size() && result == NULL; i++) {
		if(m_tileList[i]->getName() == name)
			result = m_tileList[i];
	}

	return result;
}

void TileChooser::wheelEvent(QWheelEvent* event)
{
	if(event->delta() < 0) {
		m_currentTileIndex
			= (m_currentTileIndex+1)%m_tileList.size();
	}
	else {
		if(m_currentTileIndex <= 0)
			m_currentTileIndex = m_tileList.size();

		m_currentTileIndex
			= m_currentTileIndex-1;
	}

	this->setIcon(*(m_tileList[m_currentTileIndex]->getIcon()));
}

void TileChooser::releasedHandler()
{
	m_currentTileIndex
		= (m_currentTileIndex+1)%m_tileList.size();

	this->setIcon(*(m_tileList[m_currentTileIndex]->getIcon()));
}
