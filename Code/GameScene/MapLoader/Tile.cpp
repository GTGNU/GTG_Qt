#include "Tile.h"
#include "Row.h"
#include "Map.h"
#include "TileType.h"
#include "TileView.h"
#include "TileBehavior.h"

#include <QtGui/QImage>

#include <QtQuick/QSGNode>
#include <QtQuick/QSGTexture>
#include <QtQuick/QQuickWindow>

QDebug& operator<<(QDebug& dbg, gtg::Tile* tile)
{
	dbg
		<< "Tile { parentItem:"
			<< QString(tile->parentItem()->metaObject()->className())
			+ "(" + QString::number((int)tile->parentItem(), 16) + ")"

		<< ", window:"
			<< QString(tile->window()->metaObject()->className())
			+ "(" + QString::number((int)tile->window(), 16) + ")"

		<< ", texture:" << tile->view()->textureFilename()
		<< "}";

	return dbg.space();
}

gtg::Tile::Tile(QQuickItem* parent)
	: QQuickItem(parent)
	, m_view(nullptr)
	, m_behavior(nullptr)
{
	setFlag(QQuickItem::ItemHasContents);
}

gtg::Tile::~Tile()
{
}


QString gtg::Tile::typeName() const
{
	QString sv = viewName().split('.')[0];
	QString sb = behaviorName().split('.')[0];

	return sv == sb? sv : "";
}

void gtg::Tile::setTypeName(const QString& typeName)
{
	setViewName(typeName + ".view");
	setBehaviorName(typeName + ".behavior");
}


gtg::TileView* gtg::Tile::view() const
{
	return m_view;
}

QString gtg::Tile::viewName() const
{
	return m_view->name();
}

void gtg::Tile::setViewName(const QString& viewName)
{
	TileView* prev = m_view;
	m_view = TileView::find(viewName);

	if (prev != m_view) {
		disconnect(m_view, SIGNAL(textureChanged(QString)), this, SLOT(update()));
		connect(m_view, SIGNAL(textureChanged(QString)), this, SLOT(update()));

		update();
		emit viewChanged(prev, m_view);
	}
}


gtg::TileBehavior* gtg::Tile::behavior() const
{
	return m_behavior;
}

QString gtg::Tile::behaviorName() const
{
	return m_behavior->name();
}

void gtg::Tile::setBehaviorName(const QString& behaviorName)
{
	TileBehavior* prev = m_behavior;
	m_behavior = TileBehavior::find(behaviorName);

	if (prev != m_behavior)
		emit behaviorChanged(prev, m_behavior);
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

	QSGSimpleTextureNode* n = static_cast<QSGSimpleTextureNode*>(node);

	if (!n) {
		qDebug() << "Initializing node";

		n = new QSGSimpleTextureNode;

		int tileSize = map()->tileSize();
		setX(mapX() * tileSize);
		setY(0); // relative to row
		setWidth(tileSize);
		setHeight(tileSize);
	}

	n->setRect(boundingRect());

	qDebug() << "Bounding rect: " << boundingRect();

	view()->updateTextureOf(this, n);
	return n;
}

