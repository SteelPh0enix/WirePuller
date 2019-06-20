import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    property alias inputData: inputField.text
    property alias inputDescription: inputDescription.text
    width: 350

    id: labeledInput
    height: 30

    RowLayout{
        Text {
            id: inputDescription
            font.pointSize: 10
            text: qsTr("Sample description")
        }

        TextField {
            id: inputField
            Layout.preferredHeight: 25
        }
    }
}
