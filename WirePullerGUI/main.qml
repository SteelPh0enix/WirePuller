import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: mainWindow
    visible: true
    width: 620
    height: 530
    maximumHeight: height
    minimumHeight: height
    maximumWidth: width
    minimumWidth: width
    title: qsTr("WirePuller Control Center")

    TabBar {
        id: tabBar
        width: parent.width
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
                name: qsTr("Oś X")
                anchors.topMargin: 35
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.left: parent.left
            }
            AxisControl {
                id: breakerAxisControl
                name: qsTr("Oś pomiaru siły")
                anchors.topMargin: 35
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.left: xAxisControl.right
                endstopsEnabled: false
            }
            AxisControl {
                id: wheelAxisControl
                name: qsTr("Koło")
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.top: xAxisControl.bottom
                anchors.left: parent.left

                leftEndstopEnabled: false
                rightEndstopName: "Zakres"
            }

            ColumnLayout {
                id: serialPortLayout
                anchors.left: wheelAxisControl.right
                anchors.top: breakerAxisControl.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 10
                spacing: 5


                Text {
                    id: labelSerialPort
                    text: "Port"
                    font.pointSize: 14
                    font.bold: true

                    Layout.fillHeight: false
                    Layout.fillWidth: true
                }

                ComboBox {
                    id: comboSerialPort

                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30
                }

                Button {
                    id: buttonRefreshSerialPorts
                    text: "Odśwież listę portów"

                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.preferredHeight: 25
                }

                Button {
                    id: buttonSelectPort
                    text: "Wybierz port"

                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.preferredHeight: 25
                 }

            }

            Button {
                property bool running: false

                id: buttonStartStop
                text: "Start"

                onRunningChanged: {
                    if (running) {
                        text: "Stop"
                    } else {
                        text: "Start"
                    }
                }

                height: 40
                width: serialPortLayout.width
                x: mainWindow.width - width - 10
                y: mainWindow.height - height - 10
            }
        }

        Item {
            id: settingsScreen
        }
    }
}
