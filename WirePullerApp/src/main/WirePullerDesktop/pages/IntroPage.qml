import QtQuick 2.0
import QtQuick.Controls 2.4


Page {
    id: introPage

    Label {
        anchors.centerIn: parent
        text: "Hello!"
    }

    Text {
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        text: qsTr("Please click the button below to proceed...")
    }
}
