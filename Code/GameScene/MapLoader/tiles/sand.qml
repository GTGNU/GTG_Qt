import GTG 1.0

TileClass {
	name: 'sand'

	trespassable: true

	texture: 'sand.png'

	onPlayerEnteredArea: { player.speed /= 2 }
	onPlayerExitedArea: { player.speed *= 2 }
}
