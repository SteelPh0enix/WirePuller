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
                name: qsTr("Oś napinacza")
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
                rightEndstopName: qsTr("Zakres")
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
                }

                Button {
                    id: buttonRefreshSerialPorts
                    text: qsTr("Odśwież listę portów")

                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.preferredHeight: 25
                }

                Button {
                    id: buttonSelectPort
                    text: qsTr("Wybierz port")

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
                        text: qsTr("Stop")
                    } else {
                        text: qsTr("Start")
                    }
                }

                height: 40
                width: serialPortLayout.width
                x: mainWindow.width - width - 10
                y: mainWindow.height - height - 10
            }
        }

        Item {
            id: settings
            property int ticksXAxis: parseInt(inputXAxisTicksPerMillimeter.text)
            property int ticksWheelAxis: parseInt(inputWheelAxisTicksPerMillimeter.text)
            property int ticksBreakerAxis: parseInt(inputBreakerAxisTicksPerMillimeter.text)
            signal save()
            signal restore()

            ColumnLayout {
                id: settingsLayout
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.topMargin: 40

                Item {
                    id: encoderSettingsBox

                    GridLayout {
                        id: encoderSettingsGrid
                        columns: 2
                        anchors.fill: parent

                        Text {
                            id: labelEncoderSettingsBoxDescription
                            Layout.columnSpan: 2
                            text: qsTr("\"Ticki\" enkodera per milimetr")
                            font.bold: true
                            font.pointSize: 14
                        }

                        Text {
                            id: labelEncoderSettingsXAxis
                            text: qsTr("Oś X:")
                            font.pointSize: 10
                        }

                        TextField {
                            id: inputXAxisTicksPerMillimeter
                            text: qsTr("0")
                        }

                        Text {
                            id: labelEncoderSettingsWheelAxis
                            text: qsTr("Koło:")
                            font.pointSize: 10
                        }

                        TextField {
                            id: inputWheelAxisTicksPerMillimeter
                            text: qsTr("0")
                        }

                        Text {
                            id: labelEncoderSettingsBreakerAxisDescription
                            text: qsTr("Oś napinacza:")
                            font.pointSize: 10
                        }

                        TextField {
                            id: inputBreakerAxisTicksPerMillimeter
                            text: qsTr("0")
                        }

                        Button {
                            id: buttonRestoreEncoderSettings
                            Layout.columnSpan: 2
                            Layout.fillWidth: true
                            text: qsTr("Przywróć z ustawień")
                            onPressed: settings.save()
                        }

                        Button {
                            id: buttonSaveEncoderSettings
                            Layout.columnSpan: 2
                            Layout.fillWidth: true
                            text: qsTr("Zapisz ustawienia")
                            onPressed: settings.restore()
                        }
                    }
                }
            }
        }
    }
}
