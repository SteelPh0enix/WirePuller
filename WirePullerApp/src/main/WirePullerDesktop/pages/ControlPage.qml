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
        }

        PwmControlWidget {
            description: "Wheel rotation: "
        }
    }
}
