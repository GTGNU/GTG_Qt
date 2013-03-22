import QtQuick 1.0

Image {
	id: window
	source: resDir + 'Artwork/Wallpaper.jpg'

	property string resDir: '../../'

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

	Grid {
		id: textTable
		columns: 1

		property int fontSize: 20

		x: window.width / 20
		y: window.height / 2

		MenuItem {
			text: "PLAY"
			onClicked: window.state = window.state == "play"? "" : "play"
		}

		MenuItem {
			text: "LOAD"
			onClicked: window.state = window.state == "load"? "" : "load"
		}

		MenuItem {
			text: "SETTINGS"
			onClicked: window.state = window.state == ""? "settings" : "play"
		}

		MenuItem {
			text: "QUIT"
			onClicked: Qt.quit()
		}
	}
}
