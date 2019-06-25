#ifndef AXISDATAMODEL_H
#define AXISDATAMODEL_H

#include <QObject>
#include <QString>

class AxisDataModel : public QObject {
 private:
  Q_OBJECT
  Q_PROPERTY(double power READ power WRITE setPower NOTIFY powerChanged)
  Q_PROPERTY(double encoderValue READ encoderValue NOTIFY encoderValueChanged)
  Q_PROPERTY(bool leftEndstopState READ leftEndstopState NOTIFY leftEndstopStateChanged)
  Q_PROPERTY(bool rightEndstopState READ rightEndstopState NOTIFY rightEndstopStateChanged)
  Q_PROPERTY(double ticksPerMm READ ticksPerMm NOTIFY ticksPerMmChanged)
  Q_PROPERTY(double minPWM READ minPWM NOTIFY minPWMChanged)
  Q_PROPERTY(double maxPWM READ maxPWM NOTIFY maxPWMChanged)
  Q_PROPERTY(double minSpeed READ minSpeed NOTIFY minSpeedChanged)
  Q_PROPERTY(double maxSpeed READ maxSpeed NOTIFY maxSpeedChanged)
 public:
  AxisDataModel(QObject* parent = nullptr);

  double power() const;
  double encoderValue() const;
  bool leftEndstopState() const;
  bool rightEndstopState() const;
  QString name() const;
  double ticksPerMm() const;
  double minPWM() const;
  double maxPWM() const;
  double minSpeed() const;
  double maxSpeed() const;

 public slots:
  void setPower(double newPower);
  void setEncoderValue(double newEncoderValue);
  void setLeftEndstopState(bool newState);
  void setRightEndstopState(bool newState);
  void setName(QString const& newName);

  void setTicksPerMm(double ticks);
  void setMinPWM(double pwm);
  void setMaxPWM(double pwm);
  void setMinSpeed(double speed);
  void setMaxSpeed(double speed);

 signals:
  void powerChanged(double);
  void encoderValueChanged(double);
  void leftEndstopStateChanged(bool);
  void rightEndstopStateChanged(bool);

  void ticksPerMmChanged(double);
  void minPWMChanged(double);
  void maxPWMChanged(double);
  void minSpeedChanged(double);
  void maxSpeedChanged(double);

  void modelChanged(AxisDataModel*);

 private:
  double m_power{0.0};
  double m_encoderValue{0.0};
  bool m_leftEndstopState{false};
  bool m_rightEndstopState{false};
  QString m_name{};

  double m_ticksPerMm{};
  double m_minPWM{};
  double m_maxPWM{};
  double m_minSpeed{};
  double m_maxSpeed{};
};

#endif // AXISDATAMODEL_H
