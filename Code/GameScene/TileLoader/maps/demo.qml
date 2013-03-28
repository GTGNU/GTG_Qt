/*
scheme:

	WWWW|G|C
	WWW/GG|C
	--'GGG|C
	GGGGGG|C
*/

Map {
	Row {
			Tile { type: 'water'                         },
			Tile { type: 'water'                         },
			Tile { type: 'water'                         },
			Tile { type: 'water'                         },
			Tile { type: 'overlap'; behavior: 'sand'     },
			Tile { type: 'sand'                          },
			Tile { type: 'overlap'; behavior: 'concrete' },
			Tile { type: 'concrete'                      }
	},
	Row {
			Tile { type: 'water'                         },
			Tile { type: 'water'                         },
			Tile { type: 'water'                         },
			Tile { type: 'overlap'; behavior: 'sand'     },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'overlap'; behavior: 'concrete' },
			Tile { type: 'concrete'                      }
	},
	Row {
			Tile { type: 'overlap'; behavior: 'sand'     },
			Tile { type: 'overlap'; behavior: 'sand'     },
			Tile { type: 'overlap'; behavior: 'sand'     },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'overlap'; behavior: 'concrete' },
			Tile { type: 'concrete'                      }
	},
	Row {
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'sand'                          },
			Tile { type: 'overlap'; behavior: 'concrete' },
			Tile { type: 'concrete'                      }
	},
}
