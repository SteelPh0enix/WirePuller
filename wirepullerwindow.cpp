#include "wirepullerwindow.hpp"
#include <QMessageBox>
#include "devicenames.hpp"
#include "ui_wirepullerwindow.h"

WirePullerWindow::WirePullerWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::WirePullerWindow) {
  ui->setupUi(this);

  on_refreshSerialPortsButton_clicked();
}

WirePullerWindow::~WirePullerWindow() {
  delete ui;
}

void WirePullerWindow::on_refreshSerialPortsButton_clicked() {
  serialPortInfoManager.refreshPortList();
  auto portNames = serialPortInfoManager.getPortNames();
  ui->serialPortsListCombo->clear();
  for (auto const& portName : portNames) {
    ui->serialPortsListCombo->addItem(portName);
  }
}

void WirePullerWindow::on_openSerialPortButton_clicked() {
  auto selectedPort = ui->serialPortsListCombo->currentText();
  emit openSerialPort(selectedPort);
}

void WirePullerWindow::on_helpButton_clicked() {
  QMessageBox::question(
      this, "Help",
      "* Use sliders to set motors speed.\n"
      "* Enter motor offset from calibrated "
      "position in input below sliders and press <Enter> to move them to "
      "specified position.\n"
      "* To callibrate, first press <Callibrate> button, "
      "wait until elements will hit endstops and stop moving, and then slowly "
      "move them using sliders by 1cm and write tick count to the input "
      "corresponding to motor.\n"
      "While uncallibrated, <Distance from origin> label will show raw tick "
      "count instead of position, which you can use to callibrate readings.",
      QMessageBox::Ok);
}

void WirePullerWindow::on_actionExit_triggered() {
  QApplication::exit();
}

void WirePullerWindow::on_actionButton_clicked() {
  if (movingState) {
    emit stopMoving();
  } else {
    emit startMoving();
  }
}

void WirePullerWindow::on_resetButton_clicked() {
  emit stopMoving();

  if (!movingState) {
    emit callibrate();
  }
}

void WirePullerWindow::setMovingState(bool state) {
  if (state) {
    ui->actionButton->setText("Stop");
  } else {
    ui->actionButton->setText("Start");
  }

  movingState = state;
}

void WirePullerWindow::updateAxisData(UIData::Axis axis,
                                      UIData::AxisInputData const& data) {
  switch (axis) {
    case UIData::Axis::None: {
      break;
    }
    case UIData::Axis::X: {
      ui->xAxisLeftEndstopStatus->setChecked(data.leftEndstopState);
      ui->xAxisRightEndstopStatus->setChecked(data.rightEndstopState);
      ui->xAxisDistance->setText(QString::number(
          translateTicksToDistance(UIData::Axis::X, data.distanceTicks)));
      break;
    }
    case UIData::Axis::Wheel: {
      ui->wheelAxisLeftEndstopStatus->setChecked(data.leftEndstopState);
      ui->wheelAxisRightEndstopStatus->setChecked(data.rightEndstopState);
      ui->wheelAxisDistance->setText(QString::number(
          translateTicksToDistance(UIData::Axis::Wheel, data.distanceTicks)));
      break;
    }
    case UIData::Axis::Breaker: {
      ui->breakerAxisLeftEndstopStatus->setChecked(data.leftEndstopState);
      ui->breakerAxisRightEndstopStatus->setChecked(data.rightEndstopState);
      ui->breakerAxisDistance->setText(QString::number(
          translateTicksToDistance(UIData::Axis::Breaker, data.distanceTicks)));
      break;
    }
  }
}

void WirePullerWindow::serialPortOpenFeedback(bool isOpen) {
  if (isOpen) {
    ui->openedPortName->setText(
        QString("Opened port: %1")
            .arg(ui->serialPortsListCombo->currentText()));
    portOpenState = true;
  } else {
    ui->openedPortName->setText("Unable to open port!");
    portOpenState = false;
  }
}

double WirePullerWindow::translateTicksToDistance(UIData::Axis axis,
                                                  double ticks) const {
  double ticksPerCm{0.};
  switch (axis) {
    case UIData::Axis::None: {
      break;
    }
    case UIData::Axis::X: {
      ticksPerCm = ui->xAxisTicksPerCm->text().toDouble();
      break;
    }
    case UIData::Axis::Wheel: {
      ticksPerCm = ui->wheelAxisTicksPerCm->text().toDouble();
      break;
    }
    case UIData::Axis::Breaker: {
      ticksPerCm = ui->breakerAxisTicksPerCm->text().toDouble();
      break;
    }
  }

  if (ticksPerCm == 0.) {
    return ticks;
  } else {
    return ticks / ticksPerCm;
  }
}

void WirePullerWindow::on_xAxisMotorPower_valueChanged(int value) {}

void WirePullerWindow::on_wheelAxisMotorPower_valueChanged(int value) {}

void WirePullerWindow::on_breakerAxisMotorPower_valueChanged(int value) {}

void WirePullerWindow::on_xAxisPosition_returnPressed() {}

void WirePullerWindow::on_wheelAxisPosition_returnPressed() {}

void WirePullerWindow::on_breakerAxisPosition_returnPressed() {}

void WirePullerWindow::on_xAxisModePosition_toggled(bool checked) {}

void WirePullerWindow::on_xAxisModePower_toggled(bool checked) {}

void WirePullerWindow::on_wheelAxisModePosition_toggled(bool checked) {}

void WirePullerWindow::on_wheelAxisModePower_toggled(bool checked) {}

void WirePullerWindow::on_breakerAxisModePosition_toggled(bool checked) {}

void WirePullerWindow::on_breakerAxisModePower_toggled(bool checked) {}
