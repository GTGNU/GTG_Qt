import GTG 1.0

TileType {
	name: 'sand'

	view: TileView {
		name: 'sand.view'
		texture: 'sand.png'
	}

	behavior: TileBehavior {
		name: 'sand.behavior'
		trespassable: true

		onPlayerEnteredArea: { player.speed /= 2 }
		onPlayerExitedArea: { player.speed *= 2 }
	}
}
