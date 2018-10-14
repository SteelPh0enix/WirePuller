import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import pl.projektorion.serial 1.0

Page {
    id: serialDevicePage

    signal connected()

    function reload_model()
    {
        model.reload()
        discoveredDevices.currentIndex = 0
    }

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
                textRole: "display"
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
                reload_model()
            }
        }
    }

    SerialDeviceListModel {
        id: model
    }

    Component.onCompleted: {
        reload_model()
    }
}
