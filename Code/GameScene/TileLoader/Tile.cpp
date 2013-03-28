#include "Tile.h"

#include <QtGui/QImage>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGTexture>
#include <QtQuick/QQuickWindow>

const QString gtg::Tile::texturePath = "assets/";

gtg::Tile::Tile(QQuickItem* parent)
	: QQuickItem(parent)
{
	setFlag(ItemHasContents);

}

gtg::Tile::~Tile()
{
}


QString gtg::Tile::type() const
{
	return m_type;
}

void gtg::Tile::setType(const QString& type)
{
	m_type = type;
}


bool gtg::Tile::isTrespassable() const
{
	return m_trespassable;
}

void gtg::Tile::setTrespassable(bool trespassable)
{
	m_trespassable = trespassable;
}


QString gtg::Tile::textureFilename() const
{
	return m_textureFilename;
}

void gtg::Tile::setTextureFilename(const QString& textureFilename)
{
	m_textureFilename = textureFilename;
	loadTexture();
}


void gtg::Tile::loadTexture()
{
	if (m_texture)
		delete m_texture;

	m_texture = window()->createTextureFromImage(QImage(texturePath + m_textureFilename));
}

void gtg::Tile::setPlayer(Player* player)
{
	if (m_player)
		emit playerExited(m_player);

	m_player = player;

	if (m_player)
		emit playerEntered(m_player);
}
