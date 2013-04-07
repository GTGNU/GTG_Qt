import QtQuick 2.0
import GTG 1.0

Map {
	id: map
	tileSize: 64

	// 0
	Row {
		// 0
		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; region: V.TOP }
			]
			behavior: sand.behavior
		}

		// 1
		Tile {
			views: [
				V{ view: concrete.view },
				V{ view: water.view; region: V.TOPRIGHT }
			]
			behavior: concrete.behavior
		}

		// 2
		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; region: V.LEFT }
			]
			behavior: grass_tall.behavior
		}

		// 3
		Tile {
			views: V{ view: water.view }
			behavior: water.behavior
		}
	}

	// 1
	Row {
		// 0
		Tile {
			views: V{ view: water.view }
			behavior: water.behavior

			property var timer: Timer {
				interval: 100
				repeat: true
				running: true
				onTriggered: {
					var v = map.tileAt(0,1).views[0]
					v.rotation = (v.rotation + 1) % 360
				}
			}
		}

		// 1
		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; region: V.RIGHT },
				V{ view: water.view; region: V.TOP }
			]
			behavior: sand.behavior
		}

		// 2
		Tile {
			views: [
				V{ view: concrete.view },
				V{ view: water.view; region: V.TOPRIGHT },
				V{ view: water.view; region: V.BOTLEFT }
			]
			behavior: concrete.behavior
		}

		// 3
		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; region: V.BOTTOM }
			]
			behavior: grass_tall.behavior
		}
	}

	// 2
	Row {
		// 0
		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; region: V.BOTTOM },
				V{ view: water.view; region: V.LEFT }
			]
			behavior: grass_tall.behavior
		}

		// 1
		Tile {
			views: V{ view: water.view }
			behavior: water.behavior
		}

		// 2
		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; region: V.RIGHT }
			]
			behavior: sand.behavior
		}

		// 3
		Tile {
			views: V{ view: concrete.view }
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
