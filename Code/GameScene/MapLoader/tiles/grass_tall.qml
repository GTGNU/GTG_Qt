import GTG 1.0

TileClass {
	name: 'grass_tall'

	trespassable: true
	texture: 'grass_tall.png'

	onPlayerEnteredArea: { player.speed /= 3 }
	onPlayerExitedArea:  { player.speed *= 3 }
}
