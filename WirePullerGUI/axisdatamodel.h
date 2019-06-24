#ifndef AXISDATAMODEL_H
#define AXISDATAMODEL_H

#include <QObject>
#include <QString>

class AxisDataModel : public QObject {
 public:
  enum ControlMode { SpeedControl = 0, PowerControl = 1 };
  Q_ENUM(ControlMode)

 private:
  Q_OBJECT
  Q_PROPERTY(double controlValue READ controlValue WRITE setControlValue NOTIFY controlValueChanged)
  Q_PROPERTY(ControlMode controlMode READ controlMode WRITE setControlMode NOTIFY controlModeChanged)
  Q_PROPERTY(double distance READ distance NOTIFY distanceChanged)
  Q_PROPERTY(bool leftEndstopState READ leftEndstopState NOTIFY leftEndstopStateChanged)
  Q_PROPERTY(bool rightEndstopState READ rightEndstopState NOTIFY rightEndstopStateChanged)
  Q_PROPERTY(double displayedSpeed READ displayedSpeed NOTIFY displayedSpeedChanged)
  Q_PROPERTY(QString controlValueUnit READ controlValueUnit NOTIFY controlValueUnitChanged)
  Q_PROPERTY(QString distanceUnit READ distanceUnit WRITE setDistanceUnit NOTIFY distanceUnitChanged)
 public:
  AxisDataModel(QObject* parent = nullptr);

  double controlValue() const;
  ControlMode controlMode() const;
  double distance() const;
  bool leftEndstopState() const;
  bool rightEndstopState() const;
  double displayedSpeed() const;
  QString name() const;
  QString controlValueUnit() const;
  QString distanceUnit() const;

 public slots:
  void setControlValue(double newValue);
  void setControlMode(ControlMode newMode);
  void setDistance(double newDistance);
  void setLeftEndstopState(bool newState);
  void setRightEndstopState(bool newState);
  void setDisplayedSpeed(double newSpeed);
  void setName(QString const& newName);
  void setControlValueUnit(QString const& newUnit);
  void setDistanceUnit(QString newDistanceUnit);

 signals:
  void controlValueChanged(double);
  void controlModeChanged(ControlMode);
  void distanceChanged(double);
  void leftEndstopStateChanged(bool);
  void rightEndstopStateChanged(bool);
  void displayedSpeedChanged(double);
  void controlValueUnitChanged(QString);
  void distanceUnitChanged(QString);

  void modelChanged(AxisDataModel*);

 private:
  double m_controlValue{0.0};
  ControlMode m_controlMode{SpeedControl};
  double m_distance{0.0};
  bool m_leftEndstopState{false};
  bool m_rightEndstopState{false};
  double m_displayedSpeed{0};
  QString m_controlValueUnit{"mm/s"};
  QString m_name{};
  QString m_distanceUnit{"mm"};
};

#endif // AXISDATAMODEL_H
