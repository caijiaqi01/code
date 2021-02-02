import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Templates 2.2 as Templates
 
//��ʾListView����ק�ƶ�
Templates.Dialog {
    width: 360
    height: 520
    visible: true
    title: qsTr("ListView Move")
 
    ListModel{
        id: list_model
        Component.onCompleted: {
            for(var i=0;i<50;i++)
                list_model.append({"value": i});
        }
    }
 
    ListView{
        id: list_view
        anchors.fill: parent
        anchors.margins: 20
        model: list_model
        
        //interactive:false
        //��ǰ��
        move: Transition {
            NumberAnimation { property: "y"; duration: 200 }
        }
        //����������
        moveDisplaced: Transition {
            NumberAnimation { property: "y"; duration: 200 }
        }
        delegate: Rectangle{
            id: list_item
            width: ListView.view.width
            height: 40
            border.color: "white"
            color: mouse_area.pressed?"black":"gray"
            z: mouse_area.pressed?10:1
            Text {
                anchors.centerIn: parent
                text: "row:"+index+" value:"+value
                color: "white"
                font.pixelSize: 20
            }
            MouseArea {
                id: mouse_area
                anchors.fill: parent
                //��ֹ��view��ȡ�¼�
                preventStealing: true
                onPositionChanged: {
                    //item��viewλ��+�����item��λ�ã��ж��Ƿ��϶���������item�ϣ��ǵĻ��ͽ�������
                    var other_index = list_view.indexAt(mouse_area.mouseX + list_item.x, mouse_area.mouseY + list_item.y);
                    if (other_index !== -1 && pressed) {
                        if (index !== other_index) {
                            list_model.move(index, other_index, 1);
                        }
                    }
                }
            }
        }
    }
}