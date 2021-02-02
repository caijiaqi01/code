import QtQuick 2.12
import QtQuick.Window 2.12
 
Rectangle {
	id: b1
	radius: 10
	color: "#1E1E1E"

	property int num: 48
	property var angle: 360 / b1.num
	property var btnHeight: b1.implicitHeight / 20 //b1.num < 13 ? b1.implicitHeight / 20 / (12 / 48) : b1.implicitHeight / 20 / (b1.num / 48)

	Repeater {
		model: b1.num
		Rectangle {
			id: led
			height: b1.btnHeight
			width: height
			radius: height / 2
			color: "#FFFF0000"
			opacity: 1.0
			x: Math.cos(b1.angle * index * Math.PI/180) * (b1.implicitHeight * 0.40 ) + parent.implicitHeight / 2 - height / 2
			y: Math.sin(b1.angle * index * Math.PI/180) * (b1.implicitHeight * 0.40 ) + parent.implicitHeight / 2 - height / 2

			Text {
				anchors.centerIn: parent
				text: ""//index
				font.pointSize: 8
				color: "black"
			}

			MouseArea {
				id: mousearea
				hoverEnabled: true
				anchors.fill: parent
				onEntered: {
					//led.opacity = 0.6
				}

				onExited: {
					//led.opacity = 1.0
				}

				onClicked: {
					//led.opacity = 1.0;
					if (led.color == "red"){
						led.color = "white"
					}
					else{
						led.color = "red"
					}
				}

			}
		}
	}
}