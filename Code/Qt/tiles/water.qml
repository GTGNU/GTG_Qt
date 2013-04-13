import QtQuick 2.0
import gtg.map 1.5 as M
import gtg.gfx 1.5 as G

M.Class {
	id: tile
	name: 'water'

	texture: G.Texture {
		file: 'water-atlas.png'
		offset: timer.currentFrame

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

	behavior: M.Behavior {
		trespassable: false
	}
}
