#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore/QString>

#include <QtQuick/QQuickItem>

namespace gtg
{
	class Map;
	class Tile;

	class Player
	: public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(Map* map READ map)
		Q_PROPERTY(double speed READ speed WRITE setSpeed)
		Q_PROPERTY(Tile* currentTile READ currentTile WRITE moveTo)
		Q_ENUMS(Direction)

		public:
			enum Direction { LEFT, RIGHT, UP, DOWN };

		private:
			QString m_name;
			double m_speed;
			Direction m_direction;

			Tile* m_currentTile;

		public:

			Player(QQuickItem* parent);
			~Player();

			QString name() const;
			void setName(const QString& name);

			double speed() const;
			void setSpeed(double speed);

			Tile* currentTile() const;

			Q_INVOKABLE void moveBy(int dx, int dy);
			void moveTo(Tile* target);

			Map* map() const;

		signals:
			void moved(int, int);
	};
}

QML_DECLARE_TYPE(gtg::Player)

#endif
