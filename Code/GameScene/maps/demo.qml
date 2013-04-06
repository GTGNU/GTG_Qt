import QtQuick 2.0
import GTG 1.0

Map {
	tileSize: 64

	Row {
		Tile {
			views: [
				V{ view: sand.view },
				V{ view: water.view; region: V.TOP }
			]
			behavior: sand.behavior
		}

		Tile {
			views: [
				V{ view: concrete.view },
				V{ view: water.view; region: V.TOPRIGHT }
			]
			behavior: concrete.behavior
		}

		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; region: V.LEFT }
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
				V{ view: water.view; region: V.RIGHT },
				V{ view: water.view; region: V.TOP }
			]
			behavior: sand.behavior
		}

		Tile {
			views: [
				V{ view: concrete.view },
				V{ view: water.view; region: V.TOPRIGHT },
				V{ view: water.view; region: V.BOTLEFT }
			]
			behavior: concrete.behavior
		}

		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; region: V.BOTTOM }
			]
			behavior: grass_tall.behavior
		}
	}

	Row {
		Tile {
			views: [
				V{ view: grass_tall.view },
				V{ view: water.view; region: V.BOTTOM },
				V{ view: water.view; region: V.LEFT }
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
				V{ view: water.view; region: V.RIGHT }
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
