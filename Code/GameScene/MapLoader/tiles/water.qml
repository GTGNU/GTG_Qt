import QtQuick 2.0
import GTG 1.0

TileType {
	id: tile
	name: 'water'

	view: TileView {
		texture: 'water' + timer.currentFrame + '.png'

		property var timer: Timer {
			interval: 100
			running: true
			repeat: true

			property int currentFrame: 0
			property int numFrames: 2

			onTriggered: {
				currentFrame = (currentFrame + 1) % numFrames
			}
		}
	}

	behavior: TileBehavior {
		trespassable: false
	}
}
