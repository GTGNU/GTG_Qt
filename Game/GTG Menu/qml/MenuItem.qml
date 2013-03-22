import QtQuick 1.0

Item {
	id: container
	signal clicked()

	property alias text: label.text

	width: label.width
	height: label.height

	Text {
		id: label

		font.family: titleScreenFont.name
		font.pointSize: textTable.fontSize
		color: "white"

		MouseArea {
			id: mouseArea
			anchors.fill: parent
			hoverEnabled: true

			onClicked: container.clicked()
		}

		states: State {
			name: "lighted"
			when: mouseArea.containsMouse
			PropertyChanges {
				target: label
				font.pointSize: textTable.fontSize+10
				color: "red"
			}
		}

		transitions: [
			Transition {
				ParallelAnimation {
					NumberAnimation { properties: "font.pointSize"; duration: 100 }
					ColorAnimation { properties: "color"; duration: 100 }
				}
			}
		]
	}
}

