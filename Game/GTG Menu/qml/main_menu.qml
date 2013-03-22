import QtQuick 1.1

Image {
	id: window
	source: resDir + 'Artwork/Wallpaper.jpg'

	property string resDir: '../../../Info/'

	width: 1300
	height: 700

	FontLoader {
		id: cutSceneFont
		source: resDir + 'Fonts/Cutscene Font/PixelCarnageMonoCodeTall.fon'
	}

	FontLoader {
		id: titleScreenFont
		source: resDir + 'Fonts/Title Screen Font/mizufalp.ttf'
	}

	Image {
		id: gentoo
		source: resDir + 'Artwork/gentoo.png'

		width: textTable.minRowHeight
		height: textTable.minRowHeight
		mirror: true

		Behavior on x      { SmoothedAnimation { velocity: 500 } }
		Behavior on y      { SmoothedAnimation { velocity: 500 } }
		Behavior on width  { SmoothedAnimation { velocity: 500 } }
		Behavior on height { SmoothedAnimation { velocity: 500 } }

		Timer {
			id: gentooTimer

			interval: 100
			running: true
			repeat: true

			onTriggered: {
				var nextX = (Math.random() + 1) * (window.width - gentoo.width) / 2
				var nextY = Math.random() * (window.height - gentoo.height)

				gentoo.mirror = gentoo.x > nextX

				gentoo.x = nextX
				gentoo.y = nextY

				gentoo.width = Math.random() * 50 + textTable.minRowHeight
				gentoo.height = Math.random() * 50 + textTable.minRowHeight
			}
		}

		function resetSize() {
			width = textTable.minRowHeight
			height = textTable.minRowHeight
		}
	}

	Grid {
		id: textTable
		columns: 1

		property int fontSize: 20

		property int minRowHeight: Math.min(itemPlay.height, itemLoad.height)
		property variant focusedItem: null

		x: window.width / 20 + 2*minRowHeight
		y: window.height / 2

		MenuItem {
			id: itemPlay
			text: "PLAY"
			onClicked: window.state = window.state == "play"? "" : "play"
		}

		MenuItem {
			id: itemLoad
			text: "LOAD"
			onClicked: window.state = window.state == "load"? "" : "load"
		}

		MenuItem {
			id: itemSettings
			text: "SETTINGS"
			onClicked: window.state = window.state == ""? "settings" : "play"
		}

		MenuItem {
			id: itemQuit
			text: "QUIT"
			onClicked: Qt.quit()
		}
	}
}
