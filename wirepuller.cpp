#include "wirepuller.hpp"
#include <QJsonObject>
#include "jsonconstants.hpp"

WirePuller::WirePuller(QObject* parent) : QObject(parent) {
  storedData[UIData::Axis::X] = UIData::AxisOutputData{};
  storedData[UIData::Axis::Wheel] = UIData::AxisOutputData{};
  storedData[UIData::Axis::Breaker] = UIData::AxisOutputData{};

  communicator.setBaudRate(QSerialPort::Baud115200);

  communicatorTimer.setInterval(100);
  QObject::connect(&communicatorTimer, &QTimer::timeout, this,
                   &WirePuller::sendData);
}

bool WirePuller::setSerialPort(const QString& portName) {
  communicator.setSerialPort(portName);
  return communicator.open();
}

void WirePuller::startMoving() {
  if (!isPortOpen() || movingState()) {
    return;
  }

  communicatorTimer.start();
  setMovingState(true);
}

void WirePuller::stopMoving() {
  if (!isPortOpen() || !movingState()) {
    return;
  }

  communicatorTimer.stop();
  setMovingState(false);
}

void WirePuller::callibrate() {
  QJsonObject callibrationRequest{};
  callibrationRequest[Json::Key::RequestType] =
      Json::Value::RequestType::Callibrate;
  callibrationRequest[Json::Key::RequestData] = QJsonObject();
  communicator.send(QJsonDocument(callibrationRequest), 1000, 100);
}

bool WirePuller::movingState() const {
  return movingStateFlag;
}

bool WirePuller::isPortOpen() const {
  return communicator.isOpen();
}

void WirePuller::setMovingState(bool state) {
  movingStateFlag = state;
  emit movingStateFeedback(state);
}

void WirePuller::openSerialPort(QString const& portName) {
  emit serialPortOpened(setSerialPort(portName));
}

void WirePuller::sendData() {
  auto data = storedDataToJson();
  QJsonObject request{};

  request[Json::Key::RequestType] = Json::Value::RequestType::SetPower;
  request[Json::Key::RequestData] = data;

  QJsonDocument response = communicator.send(QJsonDocument(std::move(request)));

  auto UIDataMap = convertResponseToInputData(response);

  checkDistances(UIDataMap);

  emit updateData(UIData::Axis::X, UIDataMap[UIData::Axis::X]);
  emit updateData(UIData::Axis::Wheel, UIDataMap[UIData::Axis::Wheel]);
  emit updateData(UIData::Axis::Breaker, UIDataMap[UIData::Axis::Breaker]);
}

QJsonObject WirePuller::storedDataToJson() const {
  QJsonObject data{};

  auto getAxisPower = [&](UIData::Axis axis) -> int {
    switch (storedData[axis].mode) {
      case UIData::AxisOutputData::Mode::SetPower: {
        return storedData[axis].power;
      }
      case UIData::AxisOutputData::Mode::SetPosition: {
        if (storedData[axis].destinationAchieved) {
          return 0;
        } else {
          return storedData[axis].power;
        }
      }
      default: {
        return 0;
      }
    }
  };

  data[Json::Key::AxisName::X] = getAxisPower(UIData::Axis::X);
  data[Json::Key::AxisName::Wheel] = getAxisPower(UIData::Axis::Wheel);
  data[Json::Key::AxisName::Breaker] = getAxisPower(UIData::Axis::Breaker);
  return data;
}

QMap<UIData::Axis, UIData::AxisInputData> WirePuller::convertResponseToInputData(
    const QJsonDocument& response) const {
  QMap<UIData::Axis, UIData::AxisInputData> data{};

  auto dataFromJson = [&](auto axis) {
    UIData::AxisInputData inputData{};

    inputData.distanceTicks = response[axis][Json::Key::EncoderTicks].toInt();
    inputData.leftEndstopState =
        response[axis][Json::Key::EndstopLeft].toBool();
    inputData.rightEndstopState =
        response[axis][Json::Key::EndstopRight].toBool();

    return inputData;
  };

  data[UIData::Axis::X] = dataFromJson(Json::Key::AxisName::X);
  data[UIData::Axis::Wheel] = dataFromJson(Json::Key::AxisName::Wheel);
  data[UIData::Axis::Breaker] = dataFromJson(Json::Key::AxisName::Breaker);
  return data;
}

void WirePuller::checkDistances(
    QMap<UIData::Axis, UIData::AxisInputData>& data) {
  auto distanceAchieved = [&](auto axisID, auto axisData) -> bool {
    return (axisData.distanceTicks >=
            (storedData[axisID].distanceCm *
             (static_cast<unsigned>(storedData[axisID].ticksPerCm) - TICK_HISTERESIS))) ||
           (axisData.distanceTicks <=
            (storedData[axisID].distanceCm *
             (static_cast<unsigned>(storedData[axisID].ticksPerCm) + TICK_HISTERESIS)));
  };

  for (auto axisDataIt = data.begin(); axisDataIt != data.end(); axisDataIt++) {
    storedData[axisDataIt.key()].destinationAchieved =
        distanceAchieved(axisDataIt.key(), axisDataIt.value());
  }
}

void WirePuller::axisPowerUpdated(UIData::Axis axis, int power) {
  storedData[axis].power = power;
}

void WirePuller::axisPositionUpdate(UIData::Axis axis, double position) {
  storedData[axis].distanceCm = position;
}

void WirePuller::axisModeUpdated(UIData::Axis axis,
                                 UIData::AxisOutputData::Mode mode) {
  storedData[axis].mode = mode;
}
