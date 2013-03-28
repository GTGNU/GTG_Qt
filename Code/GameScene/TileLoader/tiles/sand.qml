
TileDef {
	type: 'sand'

	trespassable: true

	texture: 'sand.png'

	onPlayerEntered: { player.speed /= 2 }
	onPlayerExited: { player.speed *= 2 }
}
