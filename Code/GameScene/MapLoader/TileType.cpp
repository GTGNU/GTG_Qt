#include "TileType.h"

gtg::TileType::TileType(QObject* parent)
	: TileDef<TileType>(parent)

	, m_view(nullptr)
	, m_behavior(nullptr)
{
}

gtg::TileType::~TileType()
{
}


gtg::TileView* gtg::TileType::view() const
{
	return m_view;
}

void gtg::TileType::setView(gtg::TileView* view)
{
	m_view = view;
}


gtg::TileBehavior* gtg::TileType::behavior() const
{
	return m_behavior;
}

void gtg::TileType::setBehavior(gtg::TileBehavior* behavior)
{
	m_behavior = behavior;
}
