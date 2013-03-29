#include "Tile.h"
#include "Row.h"

#include <QtGui/QImage>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGTexture>
#include <QtQuick/QQuickWindow>

const QString gtg::Tile::texturePath = "assets/";

gtg::Tile::Tile(QQuickItem* parent)
	: QQuickItem(parent)
{
	setFlag(QQuickItem::ItemHasContents);
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


int gtg::Tile::mapX() const
{
	return qobject_cast<const Row*>(parentItem())->indexOf(this);
}

int gtg::Tile::mapY() const
{
	return qobject_cast<const Row*>(parentItem())->mapY();
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
}


QSGNode* gtg::Tile::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	QSGSimpleTextureNode* n = static_cast<QSGSimpleTextureNode*>(node);

	if (!n) n = new QSGSimpleTextureNode;

	n->setTexture(window()->createTextureFromImage(QImage(texturePath + m_textureFilename)));
	n->setRect(boundingRect());

	qDebug() << "bounding rect: " << boundingRect();

	return n;
}

void gtg::Tile::setPlayer(Player* player)
{
	if (m_player)
		emit playerExited(m_player);

	m_player = player;

	if (m_player)
		emit playerEntered(m_player);
}
