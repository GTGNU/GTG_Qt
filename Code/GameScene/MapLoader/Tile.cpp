#include "Tile.h"
#include "Row.h"
#include "Map.h"

#include <QtGui/QImage>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGTexture>
#include <QtQuick/QQuickWindow>

const QString gtg::Tile::texturePath = "assets/";

QDebug& operator<<(QDebug& dbg, gtg::Tile* tile)
{
	dbg
		<< "Tile { parentItem:"
			<< QString(tile->parentItem()->metaObject()->className())
			+ "(" + QString::number((uint)tile->parentItem(), 16) + ")"

		<< ", window:"
			<< QString(tile->window()->metaObject()->className())
			+ "(" + QString::number((uint)tile->window(), 16) + ")"

		<< ", texture:" << tile->textureFilename()
		<< "}";

	return dbg.space();
}

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
	m_texture = QImage(texturePath + m_textureFilename);
	update();
}


int gtg::Tile::mapX() const
{
	return qobject_cast<const Row*>(parentItem())->indexOf(this);
}

int gtg::Tile::mapY() const
{
	return qobject_cast<const Row*>(parentItem())->mapY();
}


gtg::Row* gtg::Tile::row() const
{
	return qobject_cast<Row*>(parentItem());
}

gtg::Map* gtg::Tile::map() const
{
	return row()->map();
}


void gtg::Tile::setPlayer(Player* player)
{
	if (m_player)
		emit playerExited(m_player);

	m_player = player;

	if (m_player)
		emit playerEntered(m_player);
}

QSGNode* gtg::Tile::updatePaintNode(QSGNode* node,
		QQuickItem::UpdatePaintNodeData* updatePaintNodeData)
{
	qDebug() << "----------------------------------------";
	qDebug() << "Drawing " << this;
	qDebug() << "Bounding rect: " << boundingRect();

	QSGSimpleTextureNode* n = static_cast<QSGSimpleTextureNode*>(node);

	if (!n)
		n = new QSGSimpleTextureNode;

	int tileSize = map()->tileSize();
	setX(mapX() * tileSize);
	setY(mapY() * tileSize);
	setWidth(tileSize);
	setHeight(tileSize);

	n->setRect(boundingRect());
	n->setTexture(window()->createTextureFromImage(m_texture));

	return n;
}

