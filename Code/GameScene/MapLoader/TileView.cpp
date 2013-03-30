#include "TileView.h"

#include <QtQuick/QQuickWindow>

const QString gtg::TileView::texturePath = "assets/";

QSet<gtg::TileView*> gtg::TileView::m_toUpdate;

gtg::TileView::TileView(QObject* parent)
	: TileDef<TileView>(parent)

	, m_textureFilename()
	, m_textureImage()

	, m_texture(nullptr)
	, m_textureUpdated(false)

	, m_misc(nullptr)
{
}

gtg::TileView::~TileView()
{
}


QImage gtg::TileView::textureImage() const
{
	return m_textureImage;
}

QString gtg::TileView::textureFilename() const
{
	return m_textureFilename;
}

void gtg::TileView::setTextureFilename(const QString& textureFilename)
{
	if (m_textureFilename != textureFilename) {
		m_textureFilename = textureFilename;

		m_textureImage.load(texturePath + m_textureFilename);
		m_textureUpdated = false;

		emit textureChanged(textureFilename);
	}
}


QQuickItem* gtg::TileView::misc() const
{
	return m_misc;
}

void gtg::TileView::setMisc(QQuickItem* misc)
{
	m_misc = misc;
	emit miscChanged(misc);
}


void gtg::TileView::forceUpdate()
{
	m_toUpdate = m_defs.values().toSet();
}

void gtg::TileView::update(QQuickWindow* window)
{
	auto it = m_toUpdate.find(this);
	if (it != m_toUpdate.end()) {
		updateTexture(window);

		if (m_misc)
			m_misc->update();

		m_toUpdate.erase(it);
	}
}


void gtg::TileView::updateTexture(QQuickWindow* window)
{
	if (!m_textureUpdated) {
		m_texture = window->createTextureFromImage(m_textureImage);
		m_textureUpdated = true;
	}
}

void gtg::TileView::updateTextureOf(QQuickItem* target, QSGSimpleTextureNode* n)
{
	update(target->window());

	qDebug() << target << "texture updated";
	n->setTexture(m_texture);
}

