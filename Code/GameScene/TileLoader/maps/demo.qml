import GTG 1.0

/*
scheme:

	WWWW|G|C
	WWW/GG|C
	--'GGG|C
	GGGGGG|C
*/


Row {
	id: lel
	width: 500
	height: 500

	Tile {
		width: lel.width
		height: lel.height
		texture: 'water.png'
	}
}

/*
Map {
	Row {
			Tile { texture: 'water.png'; width: 50; height: 60; type: 'water'                         }
			Tile { texture: 'water.png'; type: 'water'                         }
			Tile { texture: 'water.png'; type: 'water'                         }
			Tile { texture: 'water.png'; type: 'water'                         }
			Tile { texture: 'water.png'; type: 'overlap'; behavior: 'sand'     }
			Tile { texture: 'water.png'; type: 'sand'                          }
			Tile { texture: 'water.png'; type: 'overlap'; behavior: 'concrete' }
			Tile { texture: 'water.png'; type: 'concrete'                      }
	}
	Row {
			Tile { type: 'water'                         }
			Tile { type: 'water'                         }
			Tile { type: 'water'                         }
			Tile { type: 'overlap'; behavior: 'sand'     }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'overlap'; behavior: 'concrete' }
			Tile { type: 'concrete'                      }
	}
	Row {
			Tile { type: 'overlap'; behavior: 'sand'     }
			Tile { type: 'overlap'; behavior: 'sand'     }
			Tile { type: 'overlap'; behavior: 'sand'     }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'overlap'; behavior: 'concrete' }
			Tile { type: 'concrete'                      }
	}
	Row {
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'sand'                          }
			Tile { type: 'overlap'; behavior: 'concrete' }
			Tile { type: 'concrete'                      }
	}
}
*/

// vim: ft=javascript :
