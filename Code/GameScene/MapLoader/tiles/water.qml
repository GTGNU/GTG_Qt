import QtQuick 2.0
import GTG 1.0

TileClass {
	id: tile

	type: 'water'

	trespassable: false

	texture: 'water' + currentFrame + '.png'

	property int currentFrame: 0
	property int numFrames: 2

	Timer {
		interval: 100
		running: true

		onTriggered: {
			tile.currentFrame = (tile.currentFrame + 1) % numFrames
		}
	}
}
