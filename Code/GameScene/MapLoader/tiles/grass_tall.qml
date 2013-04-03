import GTG 1.0

TileType {
	name: 'grass_tall'

	view: TileView {
		texture: 'grass_tall.png'
	}

	behavior: TileBehavior {
		trespassable: true

		onPlayerEnteredArea: { player.speed /= 3 }
		onPlayerExitedArea:  { player.speed *= 3 }
	}
}
