import GTG 1.0

Tile {
	type: 'grass_tall'

	trespassable: true

	texture: 'grass_tall.png'

	onPlayerEntered: { player.speed /= 3 }
	onPlayerExited:  { player.speed *= 3 }
}
