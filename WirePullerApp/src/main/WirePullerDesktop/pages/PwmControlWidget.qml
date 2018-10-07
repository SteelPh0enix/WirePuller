import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    height: 35
    width: 640
    property string description: "Value:"
    property int pixelSize: 14

    signal speed(var dV)

    Row {
        anchors.centerIn: parent
        spacing: 20
        Text {
            text: description
            height: slider.height
            verticalAlignment: Qt.AlignVCenter
            font.pixelSize: pixelSize
        }

        Slider {
            id: slider
            from: -400
            to: 400
            value: 0
            stepSize: 1.0
            snapMode: "SnapOnRelease"
            onValueChanged: speed(value)
        }

        Text {
            id: sliderValue
            text: slider.value.toPrecision(3)
            height: slider.height
            width: 3* pixelSize
            verticalAlignment: Qt.AlignVCenter
            font.pixelSize: pixelSize
        }

        Button {
            text: qsTr("Stop")
            onClicked: slider.value = 0
        }
    }
}

