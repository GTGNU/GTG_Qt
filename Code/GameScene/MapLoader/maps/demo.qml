import QtQuick 2.0
import GTG 1.0

/*
Rectangle {
	width: map.width
	height: map.height

	Map {
		id: map
		tileSize: 192

		Row {
			Tile {
				id: tile
				texture: 'water'+currentFrame+'.png'

				property int currentFrame: 0
			}
			Tile { texture: 'concrete.png' }
		}

		Row {
			Tile { texture: 'grass-tall.png' }
			Tile { texture: 'sand.png' }
		}
	}

	Timer {
		interval: 100
		running: true
		repeat: true

		onTriggered: {
			tile.currentFrame = (tile.currentFrame+1) % 2
			console.log("currentFrame changed to " + tile.currentFrame)
		}
	}
}
*/

Map {
	tileSize: 192

	Row {
		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; area: TileView.TOP }
			]
			behavior: sand.behavior
		}

		Tile {
			views: [
				V{ view: concrete.view },
				V{ view: water.view; area: TileView.TOPRIGHT }
			]
			behavior: concrete.behavior
		}

		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; area: TileView.LEFT }
			]
			behavior: grass_tall.behavior
		}

		Tile {
			views: V{ view: water.view }
			behavior: water.behavior
		}
	}

	Row {
		Tile {
			views: V{ view: water.view }
			behavior: water.behavior
		}

		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; area: TileView.RIGHT },
				V{ view: water.view; area: TileView.TOP }
			]
			behavior: sand.behavior
		}

		Tile {
			views: [
				V{ view: concrete.view },
				V{ view: water.view; area: TileView.TOPRIGHT },
				V{ view: water.view; area: TileView.BOTLEFT }
			]
			behavior: concrete.behavior
		}

		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; area: TileView.BOTTOM }
			]
			behavior: grass_tall.behavior
		}
	}

	Row {
		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; area: TileView.BOTTOM },
				V{ view: water.view; area: TileView.LEFT }
			]
			behavior: grass_tall.behavior
		}

		Tile {
			views: V{ view: water.view }
			behavior: water.behavior
		}

		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; area: TileView.RIGHT }
			]
			behavior: sand.behavior
		}

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
