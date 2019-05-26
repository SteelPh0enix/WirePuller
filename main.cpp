#include <QApplication>
#include <QObject>
#include "wirepuller.hpp"
#include "wirepullerwindow.hpp"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  WirePullerWindow ui;
  WirePuller wirePuller;

  QObject::connect(&ui, &WirePullerWindow::openSerialPort, &wirePuller,
                   &WirePuller::openSerialPort);
  QObject::connect(&wirePuller, &WirePuller::serialPortOpened, &ui,
                   &WirePullerWindow::serialPortOpenFeedback);

  QObject::connect(&ui, &WirePullerWindow::startMoving, &wirePuller,
                   &WirePuller::startMoving);
  QObject::connect(&ui, &WirePullerWindow::stopMoving, &wirePuller,
                   &WirePuller::stopMoving);
  QObject::connect(&wirePuller, &WirePuller::movingStateFeedback, &ui,
                   &WirePullerWindow::setMovingState);

  QObject::connect(&wirePuller, &WirePuller::updateUI, &ui,
                   &WirePullerWindow::updateAxisData);
  QObject::connect(&ui, &WirePullerWindow::axisUpdated, &wirePuller,
                   &WirePuller::axisUpdated);

  QObject::connect(&ui, &WirePullerWindow::callibrate, &wirePuller,
                   &WirePuller::callibrate);

  ui.show();
  return a.exec();
}
