#include "qmlengine.h"

#include <QtCore/QDebug>
#include <QtCore/QString>

#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include "Registry.h"

#include "gfx/Texture.h"
#include "gfx/Layer.h"

#include "map/Behavior.h"
#include "map/Class.h"
#include "map/Tile.h"
#include "map/Row.h"
#include "map/Map.h"


using namespace gtg;


QQmlEngine* g_engine;


QQmlEngine* qmlengine::engine()
{
	return g_engine;
}


void registerTypes(int versionMajor, int versionMinor)
{
	qDebug() << "Registering GTG QML types";

	qmlRegisterUncreatableType<Registry>("gtg.core", versionMajor, versionMinor, "Registry_t",
			"Registry is not meant to be instantiated from QML");


	qmlRegisterType<gfx::Texture> ("gtg.gfx",  versionMajor, versionMinor, "Texture"   );
	qmlRegisterType<gfx::Layer>   ("gtg.gfx",  versionMajor, versionMinor, "Layer"     );

	qmlRegisterUncreatableType<gfx::LayerStack>("gtg.gfx", versionMajor, versionMinor, "LayerStack",
			"LayerStack is a set of accessors and modifiers, not an instantiable type");


	qmlRegisterType<map::Behavior>("gtg.map",  versionMajor, versionMinor, "Behavior"  );
	qmlRegisterType<map::Class>   ("gtg.map",  versionMajor, versionMinor, "Class"     );

	qmlRegisterType<map::Tile>    ("gtg.map",  versionMajor, versionMinor, "Tile"      );
	qmlRegisterType<map::Row>     ("gtg.map",  versionMajor, versionMinor, "Row"       );
	qmlRegisterType<map::Map>     ("gtg.map",  versionMajor, versionMinor, "Map"       );

}

void registerGlobals()
{
	g_engine->rootContext()->setContextProperty("Registry", Registry::global());
}

QSharedPointer<QQmlEngine> qmlengine::init(int versionMajor, int versionMinor)
{
	registerTypes(versionMajor, versionMinor);

	QSharedPointer<QQmlEngine> engine(new QQmlEngine);
	g_engine = engine.data();

	registerGlobals();

	return engine;
}


void qmlengine::loadDefinition(const QString& relativePath)
{
	qDebug() << "Loading definition in" << relativePath;

	QQmlComponent component(g_engine, "assets/definitions/" + relativePath);
	QObject* object = component.create();

	if (object)
		object->setParent(g_engine);
	else
		qCritical() << "Error loading definition in" << relativePath << ":";

	for (auto& error : component.errors())
		qWarning() << "\tError:" << error;
}
