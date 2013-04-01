#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

int main(int argc, char* argv[])
{
	QCoreApplication app{argc, argv};

	qDebug() << "Hello, World!";

	return 0;
}
