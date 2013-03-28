import QtQuick 2.0

Image {
	id: window
	source: resDir + 'Artwork/Wallpaper.jpg'

	property string resDir: '../'

	width: 1300
	height: 700

	FontLoader {
		id: titleScreenFont
		source: resDir + 'Fonts/Title Screen Font/mizufalp.ttf'
	}

	Gentoo {
		id: gentoo
		small: menu.minRowHeight
	}

	Grid {
		id: menu
		columns: 1

		property variant focusedItem: null

		property int fontSize: 20

		property variant gentooSpacing: gentoo.small / 2

		property int minRowHeight: Math.min(
				itemPlay.height,
				itemLoad.height,
				itemSettings.height,
				itemQuit.height)

		x: window.width / 20 + gentoo.small + gentooSpacing
		y: window.height / 2

		MenuItem {
			id: itemPlay
			text: "PLAY"
			onChosen: console.log(text) // placeholder
		}

		MenuItem {
			id: itemLoad
			text: "LOAD"
			onChosen: console.log(text) // placeholder
		}

		MenuItem {
			id: itemSettings
			text: "SETTINGS"
			onChosen: console.log(text) // placeholder
		}

		MenuItem {
			id: itemQuit
			text: "QUIT"
			onChosen: Qt.quit()
		}
	}

	Text {
		id: versionNumber

		anchors.bottom: window.bottom
		anchors.bottomMargin: 10
		anchors.right: window.right
		anchors.rightMargin: 10

		text: "v 0.1.2 pre-alpha"
		font.family: titleScreenFont.name
		font.pointSize: 15
		color: "white"
	}
}

// vim: ft=javascript :
