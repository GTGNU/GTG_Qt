import QtQuick 1.1

Item {
	id: container
	signal clicked()

	property alias text: label.text

	width: label.width
	height: label.height

	Text {
		id: label

		x: 0
		y: 0

		font.family: titleScreenFont.name
		font.pointSize: textTable.fontSize
		color: "white"

		states: [
			State {
				name: "hovered"
				when: mouseArea.containsMouse && textTable.focusedItem == null

				PropertyChanges {
					target: label
					font.pointSize: textTable.fontSize+10
					color: "red"
				}
			},
			State {
				name: "focused"

				PropertyChanges {
					target: label
					font.pointSize: textTable.fontSize+10
					color: "blue"
				}

				PropertyChanges {
					target: textTable
					focusedItem: label
				}
			}
		]

		MouseArea {
			id: mouseArea
			anchors.fill: parent
			hoverEnabled: true

			onClicked: {
				var prevFocusedItem = textTable.focusedItem

				if (textTable.focusedItem != null) {
					textTable.focusedItem.state = ""
					textTable.focusedItem = null
				}

				positionChanged(mouseX, mouseY)

				if (prevFocusedItem != label) {
					textTable.focusedItem = label
					textTable.focusedItem.state = "focused"
				}

				container.clicked()
			}

			onEntered: {
				if (textTable.focusedItem == null) {
					gentooTimer.running = false
					gentoo.resetSize()
				}
			}
			onExited: {
				if (textTable.focusedItem == null) {
					gentooTimer.running = true
				}
			}

			onPositionChanged: {
				if (textTable.focusedItem == null) {
					var obj = label.mapToItem(
							null,
							-(gentoo.height + 10),
							(label.height-gentoo.height) / 2)

					gentoo.x = obj.x
					gentoo.y = obj.y
				}
			}
		}

		transitions: Transition {
			from: ""
			to: "hovered"

			ParallelAnimation {
				NumberAnimation { properties: "font.pointSize"; duration: 100 }
				ColorAnimation { properties: "color"; duration: 100 }

				SequentialAnimation {
					PauseAnimation { duration: 800 }
					PropertyAction { target: gentoo; property: "mirror"; value: false }
				}
			}
		}
	}
}

