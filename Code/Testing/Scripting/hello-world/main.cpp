#include <chrono>
#include <iostream>

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>

#include <QtQml/QJSEngine>

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptProgram>

#include "qobject_test.h"

using namespace std::chrono;


constexpr unsigned short int N = 10;


void testJsEngine(const QString& script)
{
	steady_clock::time_point start, stop;

	QJSEngine engine;
	QJSValue qobjectTestObject = engine.newQObject(new QObjectTest(0,1));

	engine.globalObject().setProperty("qobjectTestObject", qobjectTestObject);

	std::cout << "QJSEngine::evaluate(QString)" << std::endl;

	for (int i = 0; i < N; i++) {
		start = steady_clock::now();
		QJSValue ret = engine.evaluate(script);
		stop = steady_clock::now();

		std::cout
			<< duration_cast<microseconds>(stop-start).count()
			<< " µs"
			<< std::endl;

		if (ret.isError()) {
			qDebug()
				<< "An error ocurred: "
				<< ret.toString();

		}
	}
}

void testScriptEngine(const QString& script)
{
	steady_clock::time_point start, stop;

	QScriptEngine engine;
	QScriptValue qobjectTestObject = engine.newQObject(new QObjectTest(0,1));

	engine.globalObject().setProperty("qobjectTestObject", qobjectTestObject);

	std::cout << "QScriptEngine::evaluate(QString)" << std::endl;

	for (int i = 0; i < N; i++) {
		start = steady_clock::now();
		engine.evaluate(script);
		stop = steady_clock::now();

		std::cout
			<< duration_cast<microseconds>(stop-start).count()
			<< " µs"
			<< std::endl;

		if (engine.hasUncaughtException()) {
			qDebug()
				<< "Exception "
				<< engine.uncaughtException().toString();

			qDebug()
				<< "At line "
				<< engine.uncaughtExceptionLineNumber();

			qDebug()
				<< "Backtrace: "
				<< engine.uncaughtExceptionBacktrace();
		}
	}
}

void testScriptEngineProgram(const QString& script)
{
	steady_clock::time_point start, stop;

	QScriptEngine engine;
	QScriptValue qobjectTestObject = engine.newQObject(new QObjectTest(0,1));

	engine.globalObject().setProperty("qobjectTestObject", qobjectTestObject);

	QScriptProgram program {script};

	std::cout << "QScriptEngine::evaluate(QScriptProgram)" << std::endl;

	for (int i = 0; i < N; i++) {
		start = steady_clock::now();
		engine.evaluate(program);
		stop = steady_clock::now();

		std::cout
			<< duration_cast<microseconds>(stop-start).count()
			<< " µs"
			<< std::endl;

		if (engine.hasUncaughtException()) {
			qDebug()
				<< "Exception "
				<< engine.uncaughtException().toString();

			qDebug()
				<< "At line "
				<< engine.uncaughtExceptionLineNumber();

			qDebug()
				<< "Backtrace: "
				<< engine.uncaughtExceptionBacktrace();
		}
	}
}

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	QFile scriptFile {"js/test.js"};

	if (!scriptFile.exists()) {
		qDebug()
			<< scriptFile.fileName() << " does not exist in "
			<< QDir::currentPath();
	}

	scriptFile.open(QIODevice::ReadOnly);

	if (!scriptFile.isOpen()) {
		qDebug()
			<< "Could not open"
			<< scriptFile.fileName();
	}

	QString script {scriptFile.readAll()};

	qDebug() << "Script: " << script;

	testJsEngine(script);
	testScriptEngine(script);
	testScriptEngineProgram(script);
}
