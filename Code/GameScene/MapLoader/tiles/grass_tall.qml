import GTG 1.0

TileType {
	name: 'grass_tall'

	view: TileView {
		name: 'grass_tall.view'
		texture: 'grass_tall.png'
	}

	behavior: TileBehavior {
		name: 'grass_tall.behavior'

		trespassable: true

		onPlayerEnteredArea: { player.speed /= 3 }
		onPlayerExitedArea:  { player.speed *= 3 }
	}
}
