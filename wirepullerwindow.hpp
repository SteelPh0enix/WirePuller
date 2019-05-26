#ifndef WIREPULLERWINDOW_HPP
#define WIREPULLERWINDOW_HPP

#include <QMainWindow>
#include "serialportinfomanager.hpp"
#include "uidata.hpp"
#include "wirepuller.hpp"

namespace Ui {
class WirePullerWindow;
}

class WirePullerWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit WirePullerWindow(QWidget* parent = nullptr);
  ~WirePullerWindow();

 private slots:
  void on_refreshSerialPortsButton_clicked();
  void on_openSerialPortButton_clicked();
  void on_helpButton_clicked();
  void on_actionExit_triggered();
  void on_actionButton_clicked();
  void on_resetButton_clicked();

  void on_xAxisMotorPower_valueChanged(int value);

  void on_wheelAxisMotorPower_valueChanged(int value);

  void on_breakerAxisMotorPower_valueChanged(int value);

  void on_xAxisPosition_returnPressed();

  void on_wheelAxisPosition_returnPressed();

  void on_breakerAxisPosition_returnPressed();

  void on_xAxisModePosition_toggled(bool checked);

  void on_xAxisModePower_toggled(bool checked);

  void on_wheelAxisModePosition_toggled(bool checked);

  void on_wheelAxisModePower_toggled(bool checked);

  void on_breakerAxisModePosition_toggled(bool checked);

  void on_breakerAxisModePower_toggled(bool checked);

 public slots:
  void setMovingState(bool state);
  void updateAxisData(UIData::Axis axis, UIData::AxisInputData const& data);
  void serialPortOpenFeedback(bool isOpen);

 signals:
  void callibrate();
  void startMoving();
  void stopMoving();
  void openSerialPort(QString const& portName);
  void axisUpdated(UIData::Axis axis, UIData::AxisOutputData const& data);

 private:
  Ui::WirePullerWindow* ui{nullptr};
  SerialPortInfoManager serialPortInfoManager{};

  bool movingState{false};
  bool portOpenState{false};

  double translateTicksToDistance(UIData::Axis axis, double ticks) const;
};

#endif  // WIREPULLERWINDOW_HPP
