import GTG 1.0

TileType {
	name: 'sand'

	view: TileView {
		texture: 'sand.png'
	}

	behavior: TileBehavior {
		trespassable: true

		onPlayerEnteredArea: { player.speed /= 2 }
		onPlayerExitedArea: { player.speed *= 2 }
	}
}
