import QtQuick 2.0
import gtg.map 1.5 as M
import gtg.gfx 1.5 as G

M.Map {
	id: map
	tileSize: 64

	requires: [ 'tiles/sand.qml', 'tiles/concrete.qml', 'tiles/grass_tall.qml', 'tiles/water.qml' ]

	property var tiles: Registry.find("Class")
	property var sand: tiles.find("sand")
	property var concrete: tiles.find("concrete")
	property var grass_tall: tiles.find("grass_tall")
	property var water: tiles.find("water")

	Component.onCompleted: {
		var registryNames = Registry.names()

		var registry, objectNames

		function toStr(obj) {
			return registry.name + "." + obj.name + " = (" + typeof(obj) + ") " + obj
		}

		console.log("Registry content:")

		for (var i = 0; i < registryNames.length; i++) {
			registry = Registry.find(registryNames[i])
			objectNames = registry.names()

			for (var j = 0; j < objectNames.length; j++) {
				var object = registry.find(objectNames[j])
				console.log(toStr(object))
			}
		}
	}

	// 0
	M.Row {
		// 0
		M.Tile {
			G.Layer { texture: sand.texture }
			G.Layer { texture: water.texture; region: Qt.point(1,0) }

			behavior: sand.behavior
		}

		// 1
		M.Tile {
			G.Layer { texture: concrete.texture }
			G.Layer { texture: water.texture; region: Qt.point(2,0) }

			behavior: concrete.behavior
		}

		// 2
		M.Tile {
			G.Layer { texture: grass_tall.texture }
			G.Layer { texture: water.texture; region: Qt.point(0,1) }

			behavior: grass_tall.behavior
		}

		// 3
		M.Tile {
			G.Layer { texture: water.texture }

			behavior: water.behavior
		}
	}

	// 1
	M.Row {
		// 0
		M.Tile {
			id: tile01
			G.Layer { texture: water.texture }

			behavior: water.behavior

			property var rotationTimer: Timer {
				interval: 100
				repeat: true
				running: true
				onTriggered: tile01.layers.at(0).rotation++
			}

			property var mutationTimer: Timer {
				interval: 5000
				repeat: false
				running: true
				onTriggered: tile01.layers.at(0).texture = sand.texture
			}
		}

		// 1
		M.Tile {
			G.Layer { texture: sand.texture }
			G.Layer { texture: water.texture; region: Qt.point(2,1) }
			G.Layer { texture: water.texture; region: Qt.point(1,0) }

			behavior: sand.behavior
		}

		// 2
		M.Tile {
			G.Layer { texture: concrete.texture }
			G.Layer { texture: water.texture; region: Qt.point(2,0) }
			G.Layer { texture: water.texture; region: Qt.point(0,2) }

			behavior: concrete.behavior
		}

		// 3
		M.Tile {
			G.Layer { texture: grass_tall.texture }
			G.Layer { texture: water.texture; region: Qt.point(1,2) }

			behavior: grass_tall.behavior
		}
	}

	// 2
	M.Row {
		// 0
		M.Tile {
			G.Layer { texture: grass_tall.texture }
			G.Layer { texture: water.texture; region: Qt.point(1,2) }
			G.Layer { texture: water.texture; region: Qt.point(0,1) }

			behavior: grass_tall.behavior
		}

		// 1
		M.Tile {
			G.Layer { texture: water.texture }

			behavior: water.behavior
		}

		// 2
		M.Tile {
			G.Layer { texture: sand.texture }
			G.Layer { texture: water.texture; region: Qt.point(2,1) }

			behavior: sand.behavior
		}

		// 3
		M.Tile {
			G.Layer { texture: concrete.texture }

			behavior: concrete.behavior
		}
	}
}

// vim: ft=javascript :
