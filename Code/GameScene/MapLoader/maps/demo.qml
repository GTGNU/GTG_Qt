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
		Tile { type: 'sand' }
		Tile { type: 'concrete' }
		Tile { type: 'grass_tall' }
		Tile { type: 'water' }
	}

	Row {
		Tile { type: 'water' }
		Tile { type: 'sand' }
		Tile { type: 'concrete' }
		Tile { type: 'grass_tall' }
	}

	Row {
		Tile { type: 'grass_tall' }
		Tile { type: 'water' }
		Tile { type: 'sand' }
		Tile { type: 'concrete' }
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
