import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import pl.projektorion.serial 1.0


Dialog {
    id: dialog
    title: qsTr("Serial Settings Dialog")
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    function set_combobox_value(item, value)
    {
        var index = item.find(value);
        item.currentIndex = index
    }

    function set_combobox_value_from_model(item, model, value)
    {
        for (var i = 0; i < model.count; i++)
        {
            var element = model.get(i)

            if (element.value === value)
            {
                item.currentIndex = i;
            }
        }
    }

    function get_value_from_model(model, index)
    {
        return model.get(index).value
    }

    contentItem: Flickable {
        focus: true
        clip: true
        contentHeight: dialog.height
        ScrollBar.vertical: ScrollBar {}

        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            spacing: 5
            verticalItemAlignment: Qt.AlignVCenter

            Label {
                text: qsTr("Baudrate:")
            }

            ComboBox {
                id: baudrateBox
                editable: false
                model: [1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200]
            }

            Label {
                text: qsTr("Data bits:")
            }

            ComboBox {
                id: dataBitsBox
                editable: false
                model: [5, 6, 7, 8]
            }

            Label {
                text: qsTr("Flow control: ")
            }

            ComboBox {
                id: flowControlBox
                editable: false
                textRole: "label"
                model: flowControlModel
            }

            Label {
                text: qsTr("Parity bit: ")
            }

            ComboBox {
                id: parityBox
                editable: false
                textRole: "label"
                model: parityBitModel
            }

            Label {
                text: qsTr("Stop bits: ")
            }

            ComboBox {
                id: stopbitBox
                editable: false
                textRole: "label"
                model: stopBitsModel
            }
        }
    }


    ListModel {
        id: flowControlModel
        ListElement { label: qsTr("No flow control"); value: 0 }
        ListElement { label: qsTr("Hardware control"); value: 1 }
        ListElement { label: qsTr("Software control"); value: 2 }
    }

    ListModel {
        id: parityBitModel
        ListElement { label: qsTr("No parity"); value: 0 }
        ListElement { label: qsTr("Even parity"); value: 2 }
        ListElement { label: qsTr("Odd parity"); value: 3 }
        ListElement { label: qsTr("Space parity"); value: 4 }
        ListElement { label: qsTr("Mark parity"); value: 5 }
    }

    ListModel {
        id: stopBitsModel
        ListElement { label: qsTr("One stop"); value: 1 }
        ListElement { label: qsTr("One and half stop"); value: 3 }
        ListElement { label: qsTr("Two stop"); value: 2 }
    }

    SerialSettings {
        id: serialSettings
    }

    Component.onCompleted: {
        set_combobox_value(baudrateBox, serialSettings.baudrate)
        set_combobox_value(dataBitsBox, serialSettings.databits)
        set_combobox_value_from_model(flowControlBox, flowControlModel, serialSettings.flowcontrol)
        set_combobox_value_from_model(parityBox, parityBitModel, serialSettings.parity)
        set_combobox_value_from_model(stopbitBox, stopBitsModel, serialSettings.stopBits)
    }

    onAccepted: {
        serialSettings.setBaudrate(baudrateBox.currentText)
        serialSettings.setDatabits(dataBitsBox.currentText)
        serialSettings.setFlowcontrol(get_value_from_model(flowControlModel, flowControlBox.currentIndex))
        serialSettings.setParity(get_value_from_model(parityBitModel, parityBox.currentIndex))
        serialSettings.setStopBits(get_value_from_model(stopBitsModel, stopbitBox.currentIndex))

        serialSettings.store()
    }

}
