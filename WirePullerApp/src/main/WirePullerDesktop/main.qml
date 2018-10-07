import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


ApplicationWindow {
    id: app
    visible: true
    width: 640
    height: 480
    title: createWindowTitle("")

    function createWindowTitle(title)
    {
        return qsTr("WirePuller Desktop App") + (title ? ": " + title : "")
    }

    header: MenuBar {
        id: menuBar

        Menu {
            title: qsTr("&File")
            MenuItem { text: qsTr("Quit"); onClicked: Qt.quit() }
        }

        Menu {
            title: qsTr("&Help")
        }
    }

    footer: ToolBar {
        Button {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            text: "<"
            enabled: stackView.currentIndex > 0
            onClicked: {
                stackView.currentIndex -= 1
                stackView.pop()
            }
        }

        Label {
            id: statusLabel
            anchors.centerIn: parent
        }
        Button {
            id: forwardButton
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            text: ">"
            enabled: stackView.currentIndex < avaiablePages.count - 1
            onClicked: {
                stackView.currentIndex += 1
                stackView.push(avaiablePages.get(stackView.currentIndex).src)
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        state: "initial"

        property int currentIndex: 0

        initialItem: {
            var element = avaiablePages.get(currentIndex)
            if (element) {
                app.title = createWindowTitle(element.name)
                return element.src
            }
            else {
                return currentItem
            }
        }
        onCurrentItemChanged: {
            if (currentItem.connected) {
                currentItem.connected.connect(function () {
                    if (stackView.currentIndex < avaiablePages.count - 1) {
                        stackView.currentIndex += 1
                        stackView.push(avaiablePages.get(stackView.currentIndex).src)
                    }
                });
            }
        }
    }

    ListModel {
        id: avaiablePages
        ListElement { name: qsTr("Introduction page"); src: "qrc:/pages/IntroPage.qml" }
        ListElement { name: qsTr("Select device"); src: "qrc:/pages/SerialDevicePage.qml" }
        ListElement { name: qsTr("Device Control"); src: "qrc:/pages/ControlPage.qml" }
    }
}
