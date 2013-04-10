import QtQuick 2.0

Image {
	id: image
	source: resDir + 'images/gentoo.png'

	property int small

	property int prevx
	property int prevy

	property variant buddy
	property variant buddyPos

	x: 0
	y: 0
	width: small
	height: small

	mirror: state == "" && x < prevx

	Behavior on x      { SmoothedAnimation { velocity: 500 } }
	Behavior on y      { SmoothedAnimation { velocity: 500 } }
	Behavior on width  { SmoothedAnimation { velocity: 500 } }
	Behavior on height { SmoothedAnimation { velocity: 500 } }

	states: [
		State {
			name: "fixed"

			PropertyChanges {
				target: image
				width: small
				height: small
			}

			PropertyChanges {
				target: timer
				running: false
			}
		}
	]

	Timer {
		id: timer

		interval: 100
		running: true
		repeat: true

		onTriggered: {
			image.prevx = image.x
			image.prevy = image.y

			image.x = (Math.random() + 1) * (window.width - image.width) / 2
			image.y = Math.random() * (window.height - image.height)

			image.width = Math.random() * 50 + image.small
			image.height = Math.random() * 50 + image.small
		}
	}
}

// vim: ft=javascript :
