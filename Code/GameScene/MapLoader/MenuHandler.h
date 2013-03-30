#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <QtCore/QObject>

class QQuickView;

namespace gtg
{
	class MenuHandler
			: public QObject {
		Q_OBJECT

		private:
			QQuickView* m_view;
			QString m_mapSource;

		public:
			MenuHandler(QQuickView* view,
					QString mapSource,
					QObject* parent = nullptr);

		public slots:
			void play();
			void quit();
	};
}

#endif
