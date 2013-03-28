#include <iostream>

#include <QtCore/QObject>

class QObjectTest
	: public QObject
{
	Q_OBJECT
	Q_PROPERTY(int y READ y WRITE setY)

	private:
		int m_x;
		int m_y;

	public:
		QObjectTest(int x_, int y_)
			: m_x(x_), m_y(y_)
		{
		}

		int y() const
		{
			return m_y;
		}

		void setY(int val)
		{
			m_y = val;
		}

		Q_INVOKABLE void printWhatever(QString text) const
		{
			std::cout << text.toUtf8().data() << std::endl;
		}
};
