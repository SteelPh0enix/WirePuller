import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import steelph0enix.serialportmanager 1.0

Window {
    id: mainWindow
    visible: true
    width: 920
    height: 500
    maximumHeight: height
    minimumHeight: height
    maximumWidth: width
    minimumWidth: width
    title: qsTr("WirePuller Control Center")

    SerialPortManager {
        id: portManager
    }


    Item {
        id: mainScreen

        AxisControl {
            id: xAxisControl
            name: qsTr("Oś X")
            anchors.topMargin: 5
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.left: parent.left

            dataModel: xAxisData
            resetDistanceButton.onClicked: backend.resetEncoders("X");
        }

        AxisControl {
            id: breakerAxisControl
            name: qsTr("Oś napinacza")
            anchors.topMargin: 5
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.left: xAxisControl.right
            endstopsEnabled: false

            dataModel: breakerAxisData
            resetDistanceButton.onClicked: backend.resetEncoders("Breaker");
        }

        AxisControl {
            id: wheelAxisControl
            name: qsTr("Koło")
            anchors.topMargin: 5
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.left: breakerAxisControl.right
            leftEndstopVisible: false
            rightEndstopName: qsTr("Zakres")

            dataModel: wheelAxisData
            resetDistanceButton.onClicked: backend.resetEncoders("Wheel");
        }

        ColumnLayout {
            id: serialPortLayout
            width: 200
            height: 120
            anchors.leftMargin: 10
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.top: xAxisControl.bottom
            anchors.margins: 10
            spacing: 5


            Text {
                id: labelSerialPort
                text: qsTr("Port")
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


                model: portManager.serialPortList
                Component.onCompleted: portManager.refreshPortList()
            }

            Button {
                id: buttonRefreshSerialPorts
                text: qsTr("Odśwież listę portów")

                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.preferredHeight: 25

                onClicked: portManager.refreshPortList()
            }

            Button {
                id: buttonSelectPort
                text: qsTr("Wybierz port")

                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.preferredHeight: 25

                onClicked: backend.setSerialPortName(comboSerialPort.currentText)
            }
        }

        Button {
            property bool running: backend.running

            id: buttonStartStop
            text: {
                if (running) {
                    return qsTr("Stop")
                } else {
                    return qsTr("Start")
                }
            }

            height: 40
            x: mainWindow.width - width - 10
            y: mainWindow.height - height - 10

            onClicked: backend.setRunning(!running)
        }

        Button {
            id: buttonReloadSettings
            height: 40
            text: qsTr("Przeładuj ustawienia")
            anchors.right: buttonStartStop.left
            anchors.rightMargin: 5
            anchors.bottom: buttonStartStop.bottom
            anchors.bottomMargin: 0

            onClicked: backend.reloadSettings()
        }
    }

}
