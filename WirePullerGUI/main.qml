import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import steelph0enix.serialportmanager 1.0
import steelph0enix.settings 1.0

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

                maxSpeed: 100
                minSpeed: -100

                dataModel: xAxisData
            }

            AxisControl {
                id: breakerAxisControl
                name: qsTr("Oś napinacza")
                anchors.topMargin: 35
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.left: xAxisControl.right
                endstopsEnabled: false

                dataModel: breakerAxisData
            }

            AxisControl {
                id: wheelAxisControl
                name: qsTr("Koło")
                anchors.topMargin: 35
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.left: breakerAxisControl.right
                leftEndstopEnabled: false
                rightEndstopName: qsTr("Zakres")

                dataModel: wheelAxisData
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
                id: buttonCallibrate
                height: 40
                text: qsTr("Kalibruj")
                anchors.right: buttonStartStop.left
                anchors.rightMargin: 5
                anchors.bottom: buttonStartStop.bottom
                anchors.bottomMargin: 0

                onClicked: backend.callibrate()
            }
        }

        Item {
            id: settings
            property int ticksXAxis: parseInt(inputXAxisTicksPerMillimeter.text)
            property int ticksWheelAxis: parseInt(inputWheelAxisTicksPerMillimeter.text)
            property int ticksBreakerAxis: parseInt(inputBreakerAxisTicksPerMillimeter.text)
            signal save()
            signal restore()

            RowLayout {
                id: settingsLayout
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.topMargin: 40

                Item {
                    id: encoderSettingsBox
                    Layout.fillHeight: true

                    ColumnLayout {
                        id: encoderSettingsLayout
                        anchors.fill: parent

                        Text {
                            text: qsTr("\"Ticki\" enkodera per milimetr")
                            Layout.fillWidth: true
                            font.bold: true
                            font.pointSize: 14
                        }

                        LabeledInput {
                            id: inputXAxisTicksPerMillimeter
                            inputDescription: qsTr("Oś X:")
                            inputData: programSettings.settingsData["X"]["ticksPerMm"]
                            Layout.fillWidth: true
                        }

                        LabeledInput {
                            id: inputWheelAxisTicksPerMillimeter
                            inputDescription: qsTr("Koło:")
                            inputData: programSettings.settingsData["Wheel"]["ticksPerMm"]
                            Layout.fillWidth: true
                        }

                        LabeledInput {
                            id: inputBreakerAxisTicksPerMillimeter
                            inputDescription: qsTr("Oś napinacza:")
                            inputData: programSettings.settingsData["Breaker"]["ticksPerMm"]
                            Layout.fillWidth: true
                        }

                        Button {
                            id: buttonRestoreEncoderSettings
                            Layout.fillWidth: true
                            text: qsTr("Przywróć z ustawień")
                            onPressed: settings.save()
                            visible: false
                        }

                        Button {
                            id: buttonSaveEncoderSettings
                            Layout.fillWidth: true
                            text: qsTr("Zapisz ustawienia")
                            onPressed: settings.restore()
                            visible: false
                        }
                    }
                }

                Item {
                    id: movementSettingsBox
                    Layout.fillHeight: true

                    ColumnLayout {
                        id: movementSettingsGrid
                        anchors.fill: parent

                        Text {
                            text: qsTr("Stałe szybkości")
                            font.bold: true
                            font.pointSize: 14
                        }
                    }
                }
            }
        }
    }
}
