import gtg.tile 1.4

Class {
	name: 'sand'

	texture: Texture {
		file: 'sand.png'
	}

	behavior: Behavior {
		trespassable: true

		onPlayerEnteredArea: { player.speed /= 2 }
		onPlayerExitedArea: { player.speed *= 2 }
	}
}
