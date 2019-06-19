import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    property alias name: labelAxisName.text
    property alias leftEndstopState: checkEndstopLeft.state
    property alias rightEndstopState: checkEndstopRight.state
    property alias endstopsEnabled: groupEndstops.visible
    property alias leftEndstopEnabled: checkEndstopLeft.visible
    property alias rightEndstopEnabled: checkEndstopRight.visible
    property alias leftEndstopName: checkEndstopLeft.text
    property alias rightEndstopName: checkEndstopRight.text

    property real speed: 0.0
    property real distance: 0.0
    property string speedUnit: "mm/s"
    property string distanceUnit: "mm"

    signal distanceReset()

    id: axisControl
    width: 300
    height: 240

    Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: "black"
    }

    Slider {
        id: sliderSpeed
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 10
        antialiasing: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: labelSpeed.bottom
        anchors.topMargin: 5
        from: -100
        to: 100
        value: 0
    }

    Text {
        id: labelSpeed
        text: qsTr("Szybkość: ") + speed + speedUnit
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: labelAxisName.bottom
        anchors.topMargin: 5
        font.pixelSize: 12
    }

    GroupBox {
        id: groupEndstops
        height: 59
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: buttonResetSpeed.bottom
        anchors.topMargin: 5
        title: qsTr("Krańcówki")

        CheckDelegate {
            id: checkEndstopLeft
            text: qsTr("Lewa")
            checkable: false
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            padding: 5
        }

        CheckDelegate {
            id: checkEndstopRight
            x: 160
            width: 96
            height: 40
            text: qsTr("Prawa")
            checkable: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            padding: 5
        }
    }

    Text {
        id: labelDistance
        text: qsTr("Przebyta odległość: ") + distance + distanceUnit
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.FixedSize
        anchors.top: groupEndstops.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 14
    }

    Button {
        id: buttonResetSpeed
        height: 26
        text: qsTr("Wyzeruj szybkość")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: sliderSpeed.bottom
        anchors.topMargin: 5

        onClicked: sliderSpeed.value = 0
    }

    Button {
        id: buttonResetDistance
        height: 26
        text: qsTr("Wyzeruj odległość")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: labelDistance.bottom
        anchors.topMargin: 5

        onClicked: distanceReset()
    }

    Text {
        id: labelAxisName
        width: 282
        height: 14
        text: qsTr("AxisName")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 5
        font.pixelSize: 16
    }

}