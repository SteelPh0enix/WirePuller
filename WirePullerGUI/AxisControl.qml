import QtQuick 2.12
import QtQuick.Controls 2.12
import steelph0enix.axisdatamodel 1.0

Item {

    property alias name: labelAxisName.text

    property alias endstopsEnabled: groupEndstops.visible

    property alias leftEndstopState: checkEndstopLeft.state
    property alias rightEndstopState: checkEndstopRight.state

    property alias leftEndstopVisible: checkEndstopLeft.visible
    property alias rightEndstopVisible: checkEndstopRight.visible

    property alias leftEndstopName: checkEndstopLeft.text
    property alias rightEndstopName: checkEndstopRight.text

    property int controlMode: 0

    property alias resetDistanceButton: buttonResetDistance

    property bool reverseDistance: false

    property AxisDataModel dataModel
    property double maxSpeed: getMaxSpeed()

    signal distanceReset()

    id: axisControl
    width: 310
    height: 350

    function linearApprox(value, xMin, xMax, yMin, yMax) {
        return ((yMax - yMin) * (value - xMin) / (xMax - xMin)) + yMin;
    }

    function convertSpeedToMMPS(speed, unit) {
        let units = unit.split('/')

        if (units[0] === 'cm') {
            speed *= 10.;
        } else if (units[0] === 'm') {
            speed *= 1000.;
        }

        if (units[1] === 'min') {
            speed /= 60.;
        } else if (units[1] === 'h') {
            speed /= (60. * 60.);
        }

        return speed
    }

    function convertSpeedFromMMPS(speed, unit) {
        let units = unit.split('/')

        if (units[0] === 'cm') {
            speed /= 10.;
        } else if (units[0] === 'm') {
            speed /= 1000.;
        }

        if (units[1] === 'min') {
            speed *= 60.;
        } else if (units[1] === 'h') {
            speed *= (60. * 60.);
        }

        return speed
    }

    function convertPercentageToSpeed(percentage) {
        let percentageSign = Math.sign(percentage)
        let percentageAbs = Math.abs(percentage)
        return linearApprox(percentageAbs, 0, 100, dataModel.minSpeed, dataModel.maxSpeed) * percentageSign
    }

    function convertSpeedToPower(speed) {
        let speedSign = Math.sign(speed)
        let speedAbs = Math.abs(speed)
        return linearApprox(speedAbs, dataModel.minSpeed, dataModel.maxSpeed, dataModel.minPWM, dataModel.maxPWM) * speedSign
    }

    function normalizeDistanceUnit(distance) {
        if (distanceSelector.currentText == "cm") {
            return distance / 10;
        }

        return distance;
    }

    function calculateDistance() {
        let distance = normalizeDistanceUnit(dataModel.encoderValue / dataModel.ticksPerMm);
        if (reverseDistance) {
            return -distance
        }
        return distance
    }

    function normalizeSpeed(value) {
        if (Number.isNaN(value)) { return; }

        let limit = maxSpeed
        if (value < -limit) {
            value = -limit
        } else if (value > limit) {
            value = limit
        }

        return value
    }

    function convertSpeedToPercentage(speed) {
        let speedSign = Math.sign(speed)
        let speedAbs = Math.abs(speed)
        return linearApprox(speedAbs, dataModel.minSpeed, dataModel.maxSpeed, 0, 100) * speedSign
    }

    function getMaxSpeed() {
        return convertSpeedFromMMPS(dataModel.maxSpeed, comboSpeedUnit.currentText)
    }


    Rectangle {
        height: 310
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
        anchors.top: labelMaxSpeed.bottom
        anchors.topMargin: 5
        from: -100
        to: 100
        value: 0

        onValueChanged: {
            let speed = convertPercentageToSpeed(value)
            let displayedSpeed = convertSpeedFromMMPS(speed, comboSpeedUnit.currentText)
            let power = convertSpeedToPower(speed)

            inputSpeed.text = displayedSpeed.toFixed(3)
            dataModel.setPower(power)
        }
    }

    Text {
        id: labelSpeed
        text: qsTr("Szybkość:")
        anchors.verticalCenter: inputSpeed.verticalCenter
        verticalAlignment: Text.AlignVCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: labelAxisName.bottom
        anchors.topMargin: 5
        font.pixelSize: 12
    }

    Text {
        id: labelMaxSpeed
        text: qsTr("Max: ±") + maxSpeed.toFixed(3)
        anchors.left: labelSpeed.left
        anchors.leftMargin: 0
        anchors.top: inputSpeed.bottom
        anchors.topMargin: 3
    }

    TextField {
        id: inputSpeed
        text: "0"
        anchors.verticalCenter: comboSpeedUnit.verticalCenter
        anchors.left: labelSpeed.right
        anchors.leftMargin: 5
        anchors.top: labelAxisName.bottom
        anchors.topMargin: 5
        height: 25
        width: 100

        onAccepted: {
            let normalizedSpeed = normalizeSpeed(parseFloat(text))
            text = normalizedSpeed.toFixed(3)

            let speedMMPS = convertSpeedToMMPS(normalizedSpeed, comboSpeedUnit.currentText)
            let speedPercentage = convertSpeedToPercentage(speedMMPS)
            let power = convertSpeedToPower(speedMMPS)

            sliderSpeed.value = speedPercentage
            dataModel.setPower(power)
        }
    }

    ComboBox {
        id: comboSpeedUnit
        anchors.left: inputSpeed.right
        anchors.leftMargin: 5
        anchors.top: labelAxisName.bottom
        anchors.topMargin: 5
        width: 100
        height: 30

        property string lastUnit: currentText

        model: ListModel {
            ListElement { key: "mm/s" }
            ListElement { key: "mm/min" }
            ListElement { key: "mm/h" }
            ListElement { key: "cm/s" }
            ListElement { key: "cm/min" }
            ListElement { key: "cm/h" }
            ListElement { key: "m/s" }
            ListElement { key: "m/min" }
            ListElement { key: "m/h" }
        }

        onCurrentTextChanged: {
            let previousSpeed = convertSpeedToMMPS(parseFloat(inputSpeed.text), lastUnit)
            let newSpeed = convertSpeedFromMMPS(previousSpeed, currentText)
            inputSpeed.text = newSpeed.toFixed(3)

            lastUnit = currentText
        }
    }

    GroupBox {
        id: groupEndstops
        height: 55
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: buttonResetSpeed.bottom
        anchors.topMargin: 5
        title: qsTr("Krańcówki")

        CheckDelegate {
            id: checkEndstopLeft
            height: 30
            text: qsTr("Lewa")
            checkable: false
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            padding: 1

            checked: dataModel.leftEndstopState
        }

        CheckDelegate {
            id: checkEndstopRight
            x: 160
            width: 96
            height: 30
            text: qsTr("Prawa")
            checkable: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            padding: 1

            checked: dataModel.rightEndstopState
        }
    }

    Text {
        id: labelDistance
        text: qsTr("Przebyta odległość: ") + calculateDistance().toFixed(3)
        anchors.verticalCenter: distanceSelector.verticalCenter
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.FixedSize
        anchors.top: groupMode.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 14
    }

    ComboBox {
        id: distanceSelector
        anchors.leftMargin: 5
        anchors.top: groupMode.bottom
        anchors.topMargin: 5
        width: 100
        height: 30
        anchors.left: labelDistance.right

        model: ListModel {
            ListElement { key: "mm" }
            ListElement { key: "cm" }
        }
    }

    GroupBox {
        visible: false
        id: groupMode
        height: 65
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: groupEndstops.bottom
        anchors.topMargin: 5
        title: qsTr("Tryb")

        RadioButton {
            id: radioModeSpeed
            text: qsTr("Szybkość")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            padding: 1
            checked: true
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            onCheckedChanged: {
                if (checked) {
                    controlMode = 0;
                }
            }
        }

        RadioButton {
            id: radioModePower
            text: qsTr("Moc")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            padding: 1
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            onCheckedChanged: {
                if (checked) {
                    controlMode = 1;
                }
            }
        }
    }

    Button {
        id: buttonResetSpeed
        height: 26
        text: qsTr("Stop")
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
        anchors.top: distanceSelector.bottom
        anchors.topMargin: 5
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
