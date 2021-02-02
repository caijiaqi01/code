import QtQuick 2.12
import QtQuick.Window 2.12
 
Rectangle {
	id: root
	radius: 10
	color: "#1E1E1E"
	property string name: "button"
	property color nameColor: "white"

	signal click()

	Text {
		anchors.centerIn: parent
		text: root.name
		font.pointSize: 16
		color: root.nameColor
	}

	MouseArea {
		anchors.fill: parent
		onClicked: {
			root.click()
		}
	}
}