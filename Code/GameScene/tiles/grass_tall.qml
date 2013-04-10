import gtg.tile 1.4

Class {
	name: 'grass_tall'

	texture: Texture {
		file: 'grass_tall.png'
	}

	behavior: Behavior {
		trespassable: true

		onPlayerEnteredArea: { player.speed /= 3 }
		onPlayerExitedArea:  { player.speed *= 3 }
	}
}
