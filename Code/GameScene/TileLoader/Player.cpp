#include "Player.h"
#include "Tile.h"
#include "Row.h"
#include "Map.h"

gtg::Player::Player(QQuickItem* parent)
	: QQuickItem(parent)
	, m_currentTile(nullptr)
{
}

gtg::Player::~Player()
{
}


QString gtg::Player::name() const
{
	return m_name;
}

void gtg::Player::setName(const QString& name)
{
	m_name = name;
}


double gtg::Player::speed() const
{
	return m_speed;
}

void gtg::Player::setSpeed(double speed)
{
	m_speed = speed;
}


gtg::Tile* gtg::Player::currentTile() const
{
	return m_currentTile;
}

void gtg::Player::moveBy(int dx, int dy)
{
	moveTo(map()->tileAt(currentTile()->mapX() + dx, currentTile()->mapY() + dy));
}

void gtg::Player::moveTo(Tile* tile)
{
	m_currentTile->setPlayer(nullptr);
	m_currentTile = tile;
	m_currentTile->setPlayer(this);
}


gtg::Map* gtg::Player::map() const
{
	return qobject_cast<Map*>(qobject_cast<Row*>(parent())->parent());
}
