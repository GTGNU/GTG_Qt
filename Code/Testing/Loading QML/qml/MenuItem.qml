import QtQuick 2.0

Item {
	id: container
	signal chosen()

	property alias text: label.text

	width: label.width
	height: label.height

	property variant gentooPos: label.mapToItem(
			null,
			-(gentoo.width + menu.gentooSpacing),
			(container.height - gentoo.height) / 2)

	Text {
		id: label

		font.family: titleScreenFont.name
		font.pointSize: menu.fontSize
		color: "white"

		Behavior on color { ColorAnimation  { duration: 100 } }

		states: [
			State {
				name: "hovered"
				when: mouseArea.containsMouse && menu.focusedItem == null

				PropertyChanges {
					target: label
					font.pointSize: menu.fontSize+10
					color: "red"
				}

				PropertyChanges {
					target: gentoo
					state: "fixed"
					x: gentooPos.x
					y: gentooPos.y
				}
			},
			State {
				name: "focused"
				when: menu.focusedItem == label

				PropertyChanges {
					target: label
					font.pointSize: menu.fontSize+10
					color: "blue"
				}

				PropertyChanges {
					restoreEntryValues: false
					target: gentoo
					x: gentooPos.x
					y: gentooPos.y
				}

				StateChangeScript {
					script: container.chosen()
				}
			}
		]

		MouseArea {
			id: mouseArea
			anchors.fill: parent
			hoverEnabled: true

			onClicked: {
				if (label.state == "focused") {
					gentoo.state = ""
					menu.focusedItem = null
				} else {
					menu.focusedItem = label
					gentoo.state = "fixed"
				}
			}
		}
	}
}

// vim: ft=javascript :
