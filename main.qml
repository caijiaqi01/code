import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import an.qt.Calculate 1.0

Window {
	id: root
    width: 1000
    height: 480
    visible: true
    title: qsTr("Hello World")

	QtObject {
		id: internal
		readonly property var calculate: an.qt.Calculate
	}

	Rectangle {
        anchors.fill: parent
        color: "#54565c"
    }
/*
	Calculate {
        id: calculate
        color: "green"
    }
*/
	RowLayout {
		anchors.fill: parent
		ColumnLayout {
			id: portCom
			spacing: 5

			CButton {
				id: drop
				implicitHeight: root.height * 0.1 
				implicitWidth:  root.width * 0.2
				name: internal.calculate.getStr("drop")

				onClick: {
					mdrop.visible = true
				}
			}

			CButton {
				id: path
				implicitHeight: root.height * 0.1 
				implicitWidth:  root.width * 0.2
				name: internal.calculate.getStr("path")

				onClick: {
					internal.calculate.createPath();
				}
			}

			CButton {
				id: mysql
				implicitHeight: root.height * 0.1 
				implicitWidth:  root.width * 0.2
				name: internal.calculate.getStr("database")

				onClick: {
					internal.calculate.connectMysql();
				}
			}

			CCustom {
				id: b1
				visible: true
				implicitHeight: root.height * 0.5 
				implicitWidth:  implicitHeight
			}

			RowLayout {
				id: portRep
				visible: true
				spacing: 5

				CButton {
					id: a1
					implicitHeight: root.height * 0.1 
					implicitWidth:  root.width * 0.2
					nameColor: (formDevice.text !== "" && toDevice.text !== "") ? "white" : "#5E5E5E"
					name: internal.calculate.getStr("copy device")

					onClick: {
						if (formDevice.text !== "" && toDevice.text !== ""){
							internal.calculate.copyMasterPlusDevice(formDevice.text, toDevice.text);
						}
					}
				}

				Text {
					text: internal.calculate.getStr("form Device")
					font.pointSize: 16
					color: "white"
				}
			
				Rectangle {
					//anchors.top: parent.top
					implicitWidth: formDevice.contentWidth<100 ? 100 : formDevice.contentWidth + 10
					implicitHeight: a1.height
					color: "#1E1E1E"
					border.color: "white"
				
					TextInput {
						id: formDevice
						anchors.centerIn: parent
						anchors.margins: 2
						font.pointSize: 16
						color: "white"
						activeFocusOnPress: true//鼠标单击激活
						focus: true
						validator: RegExpValidator{regExp: /^[4-9]|1[0-9]|2[0-9]|3[0-9]|4[0-8]$/}

						onEditingFinished: {
							if ( !focus ) return
							focus = false
							toDevice.focus = true
							b1.num = formDevice.text
						}				
					}
				}

				Text {
					text: internal.calculate.getStr("to Device")
					font.pointSize: 16
					color: "white"
				}
		
				Rectangle {
					//anchors.top: parent.top
					implicitWidth: toDevice.contentWidth<100 ? 100 : toDevice.contentWidth + 10
					implicitHeight: a1.height
					color: "#1E1E1E"
					border.color: "white"

					TextInput {
						id: toDevice
						anchors.centerIn: parent
						anchors.margins: 2
						font.pointSize: 16
						activeFocusOnPress: true//鼠标单击激活
						color: "white"
						focus: true

						onEditingFinished: {
							if ( !focus ) return
							focus = false
							formDevice.focus = true
							b1.num = toDevice.text
						}
					}
				}
			}
		}

		Output {
			width: root.width / 2
			height: root.height
			output: internal.calculate.output
		}
	}
	DropList {
		id: mdrop
	    width: 360
		height: 520
	    visible: false
	}
}
