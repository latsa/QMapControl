#include "GPSSimulator.h"
#include <QTimer>
#include <random>

namespace {
   qreal m_x = 1.0; // The current x point.
   qreal m_y = 1.0; // The current y point.
   std::random_device m_rd;  // A random device.
   std::mt19937 m_mt(m_rd());// A random engine.
   std::uniform_int_distribution<int> m_dist(0, 10);// A uniform distribution.
}

GPSSimulator::GPSSimulator(QObject *parent)
   : QObject(parent), m_running(false) {
}

void GPSSimulator::start() {
   if (m_running)
      return;

   m_running = true;
   QTimer::singleShot(40 , this, SLOT(tick())); //25Hz
}

void GPSSimulator::stop() {
   m_running = false;
}

void GPSSimulator::tick() {

   if (0 == m_dist(m_mt)) {
      m_x += 0.1;
      m_y += 0.1;

      emit positionChanged(PointWorldCoord(m_x ,m_y));
   }

   if (m_running)
        QTimer::singleShot(40, this, SLOT(tick()));
}
