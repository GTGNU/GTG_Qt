import gtg.map 1.5 as M
import gtg.gfx 1.5 as G

M.Class {
	name: 'sand'

	texture: G.Texture {
		file: 'sand.png'
	}

	behavior: M.Behavior {
		trespassable: true
	}
}
