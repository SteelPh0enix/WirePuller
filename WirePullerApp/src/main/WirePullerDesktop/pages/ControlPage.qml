import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Page {
    id: controlPage

    DeviceWidget {
        id: deviceWidget
        anchors.top: parent.top
    }

    Column {
        id: controls
        anchors.bottom: parent.bottom
        width: controlPage.width
        padding: 20
        spacing: 20

        PwmControlWidget {
            description: "Horizontal translation: "
            onSpeed: backend.setHorizontalTranslationPwm(dV)
        }

        PwmControlWidget {
            description: "Wheel rotation: "
            onSpeed: backend.setWheelRotationPwm(dV)
        }
    }

    Column {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * .25
        padding: 10
        spacing: 5
        Label {
            text: qsTr("Feedback data")
            font.pixelSize: 16
            font.bold: true
            font.underline: true
        }

        Column {
            Label {
                text: qsTr("Horizontal translation:")
                font.bold: true
            }

            Row {
                Text {
                    text: "Speed: "
                }
                Text {
                    id: translationSpeedValue
                }
            }

            Row {
                Text {
                    text: "Current: "
                }
                Text {
                    id: translationCurrentValue
                }
            }

            Row {
                Text {
                    text: "Error: "
                }
                Text {
                    id: translationErrorValue
                }
            }
        }
        Column {
            Label {
                text: qsTr("Wheel:")
                font.bold: true
            }

            Row {
                Text {
                    text: "Rotation: "
                }
                Text {
                    id: rotationValue
                }
            }
            Row {
                Text {
                    text: "Current: "
                }
                Text {
                    id: rotationCurrentValue
                }
            }

            Row {
                Text {
                    text: "Error: "
                }
                Text {
                    id: rotationErrorValue
                }
            }
        }
    }

    Connections {
        target: backend
        onSerialError: {
            errorMsg.text = error
            errorDialog.open()
        }
    }

    Dialog {
        id: errorDialog
        title: qsTr("Serial error")
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: parent.width * 4 / 5
        height: parent.height * 4 / 5
        modal: true

        contentItem: Column {
            anchors.centerIn: parent
            spacing: 20
            padding: 20

            Label {
                text: "An error occured due to:"
                font.bold: true
                font.pixelSize: 14
            }

            Label {
                id: errorMsg
            }
        }
    }
}
