import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 620
    height: 530
    title: qsTr("WirePuller Control Center")

    TabBar {
        id: tabBar
        width: parent.width
        position: TabBar.Header
        contentHeight: 30
        contentWidth: width
        currentIndex: -1
        anchors.fill: parent

        TabButton {
            text: qsTr("Główne")
        }
        TabButton {
            text: qsTr("Ustawienia")
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: tabBar.currentIndex
        Item {
            id: mainScreen

            AxisControl {
                id: xAxisControl
                anchors.topMargin: 35
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.left: parent.left
            }
            AxisControl {
                id: breakerAxisControl
                anchors.topMargin: 35
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.left: xAxisControl.right
            }
            AxisControl {
                id: wheelAxisControl
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.top: xAxisControl.bottom
                anchors.left: parent.left
            }
        }
        Item {
            id: settingsScreen
        }
    }
}



















































/*##^## Designer {
    D{i:1;anchors_height:119;anchors_width:240;anchors_x:68;anchors_y:47}
}
 ##^##*/
