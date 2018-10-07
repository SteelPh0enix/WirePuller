import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    id: deviceWidget
    width: parent.width
    height: parent.height - controls.height

    Item {
        id: widget
        width: parent.width * .75
        height: parent.height * .75

        Rectangle {
            color: "#808080"
            width: 30
            height: 30
            x: (parent.width - width) / 2

            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: widget.width - parent.width
            }

            onXChanged: translationValue.text = x.toPrecision(4)
        }

        Rectangle {
            x: (parent.width - width) / 2; y: (parent.height - height) / 2
            antialiasing: true
            color: "#808080"
            width: 100
            height: 100
            radius: height / 4

            MouseArea {
                anchors.fill: parent

                property real centerX: parent.width / 2
                property real centerY: parent.height / 2
                property real clickX: centerX
                property real clickY: centerY

                onPressed: {
                    clickX = mouse.x - centerX
                    clickY = centerY - mouse.y
                }

                onPositionChanged: {
                    var startRad = Math.atan2(clickY, Math.abs(clickX))
                    var endRad = Math.atan2(centerY - mouse.y, Math.abs(mouse.x - centerX))
                    var diffRad = endRad - startRad
                    var deg = diffRad * 180.0 / Math.PI
                    parent.rotation = deg
                }
            }

            onRotationChanged: rotationValue.text = rotation.toPrecision(5)
        }
    }

    Column {
        anchors.right: parent.right
        anchors.top: parent.top
        width: parent.width * .25
        padding: 10
        spacing: 10

        Row {
            Text {
                text: "Translation: "
            }
            Text {
                id: translationValue
            }
        }
        Row {
            Text {
                text: "Rotation: "
            }
            Text {
                id: rotationValue
            }
        }
    }

}
