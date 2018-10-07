import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Page {
    id: serialDevicePage

    signal connected()

    Column {
        anchors.fill: parent
        padding: 20
        spacing: 20

        Label {
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Please select a serial device:")
        }

        Row {
            id: row
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            ComboBox {
                id: discoveredDevices
                model: model
            }

            Button {
                text: qsTr("Connect")
                onClicked: {
                    connected()
                }
            }
        }

        DelayButton {
            anchors.horizontalCenter: parent.horizontalCenter
            width: row.width
            text: qsTr("Reload")
            onActivated: {
                model.append({"data": "DATA"})
            }
        }
    }

    ListModel {
        id: model
    }
}
