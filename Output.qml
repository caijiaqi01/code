import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
 
//ÑÝÊ¾ListViewµÄÍÏ×§ÒÆ¶¯
Item {
    id: root
    width: 360
    height: 520
    visible: true
    property var output: []

    ColumnLayout {
        Repeater {
		    model: root.output
            Rectangle{
                id: list_item
                width: root.width
                height: 20
                color: "black"

                Text {
                    anchors.centerIn: parent
                    text: root.output[index]
                    color: "white"
                    font.pixelSize: 20
                }
            }
        }
    }
}