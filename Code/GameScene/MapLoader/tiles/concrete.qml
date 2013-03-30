import GTG 1.0

TileType {
	name: 'concrete'

	view: TileView {
		name: 'concrete.view'
		texture: 'concrete.png'
	}

	behavior: TileBehavior {
		name: 'concrete.behavior'
		trespassable: true
	}
}
