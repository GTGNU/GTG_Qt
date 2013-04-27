#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <QtCore/QString>
#include <QtCore/QSharedPointer>

class QQmlEngine;

namespace gtg
{
	namespace qmlengine
	{
		//! \brief Get the QQmlEngine used by GTG
		QQmlEngine* engine();

		/*! \brief Load a GTG QML definition (tiles, textures, players, etc)
		 *
		 * This function doesn't modify the QML global namespace,
		 * to access any loaded element, see the Registry class.
		 *
		 * \param relativePath Relative path to assets/definitions
		 */
		void loadDefinition(const QString& relativePath);

		/*! \brief Initializes the QML engine with GTG extensions
		 *
		 * \param versionMajor Major version of the GTG QML API
		 * \param versionMinor Minor version of the GTG QML API
		 * \return The initialized QQmlEngine to be used by the game
		 */
		QSharedPointer<QQmlEngine> init(int versionMajor, int versionMinor);
	}
}

#endif
