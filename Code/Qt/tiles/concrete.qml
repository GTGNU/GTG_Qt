import gtg.map 1.5 as M
import gtg.gfx 1.5 as G

M.Class {
	name: 'concrete'

	texture: G.Texture {
		file: 'concrete.png'
	}

	behavior: M.Behavior {
		trespassable: true
	}
}
