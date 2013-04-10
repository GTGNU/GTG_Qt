import QtQuick 2.0
import gtg.map 1.4
import gtg.tile 1.4 as T

Map {
	id: map
	tileSize: 64

	// 0
	Row {
		// 0
		Tile {
			T.Layer { texture: sand.texture }
			T.Layer { texture: water.texture; region: Qt.point(1,0) }

			behavior: sand.behavior
		}

		// 1
		Tile {
			T.Layer { texture: concrete.texture }
			T.Layer { texture: water.texture; region: Qt.point(2,0) }

			behavior: concrete.behavior
		}

		// 2
		Tile {
			T.Layer { texture: grass_tall.texture }
			T.Layer { texture: water.texture; region: Qt.point(0,1) }

			behavior: grass_tall.behavior
		}

		// 3
		Tile {
			T.Layer { texture: water.texture }

			behavior: water.behavior
		}
	}

	// 1
	Row {
		// 0
		Tile {
			layers: T.Layer { texture: water.texture }

			behavior: water.behavior

			property var timer: Timer {
				interval: 100
				repeat: true
				running: true
				onTriggered: {
					var l = map.tileAt(0,1).layers[0]
					l.rotation = (l.rotation + 1) % 360
				}
			}
		}

		// 1
		Tile {
			T.Layer { texture: sand.texture }
			T.Layer { texture: water.texture; region: Qt.point(2,1) }
			T.Layer { texture: water.texture; region: Qt.point(1,0) }

			behavior: sand.behavior
		}

		// 2
		Tile {
			T.Layer { texture: concrete.texture }
			T.Layer { texture: water.texture; region: Qt.point(2,0) }
			T.Layer { texture: water.texture; region: Qt.point(0,2) }

			behavior: concrete.behavior
		}

		// 3
		Tile {
			T.Layer { texture: grass_tall.texture }
			T.Layer { texture: water.texture; region: Qt.point(1,2) }

			behavior: grass_tall.behavior
		}
	}

	// 2
	Row {
		// 0
		Tile {
			T.Layer { texture: grass_tall.texture }
			T.Layer { texture: water.texture; region: Qt.point(1,2) }
			T.Layer { texture: water.texture; region: Qt.point(0,1) }

			behavior: grass_tall.behavior
		}

		// 1
		Tile {
			T.Layer { texture: water.texture }

			behavior: water.behavior
		}

		// 2
		Tile {
			T.Layer { texture: sand.texture }
			T.Layer { texture: water.texture; region: Qt.point(2,1) }

			behavior: sand.behavior
		}

		// 3
		Tile {
			T.Layer { texture: concrete.texture }

			behavior: concrete.behavior
		}
	}
}

/*
This is more or less how the final version should actually be defined
scheme:

	WWWW|G|C
	WWW/GG|C
	--'GGG|C
	GGGGGG|C
*/
/*
Map {
	Row {
			Tile    { type: 'water'        }
			Tile    { type: 'water'        }
			Tile    { type: 'water'        }
			Tile    { type: 'water'        }
			Overlap { behavior: 'sand'     }
			Tile    { type: 'sand'         }
			Overlap { behavior: 'concrete' }
			Tile    { type: 'concrete'     }
	}
	Row {
			Tile    { type: 'water'        }
			Tile    { type: 'water'        }
			Tile    { type: 'water'        }
			Overlap { behavior: 'sand'     }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Overlap { behavior: 'concrete' }
			Tile    { type: 'concrete'     }
	}
	Row {
			Overlap { behavior: 'sand'     }
			Overlap { behavior: 'sand'     }
			Overlap { behavior: 'sand'     }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Overlap { behavior: 'concrete' }
			Tile    { type: 'concrete'     }
	}
	Row {
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Tile    { type: 'sand'         }
			Overlap { behavior: 'concrete' }
			Tile    { type: 'concrete'     }
	}
}
*/
// vim: ft=javascript :
