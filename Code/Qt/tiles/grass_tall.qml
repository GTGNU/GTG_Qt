import gtg.map 1.5 as M
import gtg.gfx 1.5 as G

M.Class {
	name: 'grass_tall'

	texture: G.Texture {
		file: 'grass_tall.png'
	}

	behavior: M.Behavior {
		trespassable: true
	}
}
