#include "MenuHandler.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickWindow>

gtg::MenuHandler::MenuHandler(QQuickView* view,
		QString mapSource, QObject* parent)
	: QObject(parent)
	, m_view(view)
	, m_mapSource(mapSource)
{
}

void gtg::MenuHandler::play()
{
	qDebug() << "play() chosen";
	m_view->setSource(QUrl::fromLocalFile(m_mapSource));
	qDebug() << "view replaced";
}

void gtg::MenuHandler::quit()
{
	m_view->close();
}


