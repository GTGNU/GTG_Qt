import QtQuick 2.0
import gtg.tile 1.4

Class {
	id: tile
	name: 'water'

	texture: Texture {
		file: 'water' + timer.currentFrame + '.png'

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

	behavior: Behavior {
		trespassable: false
	}
}
