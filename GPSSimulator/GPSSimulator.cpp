#include "GPSSimulator.h"
#include <QTimer>
#include <QGeoCoordinate>

GPSSimulator::GPSSimulator(QObject *parent)
   : QObject(parent) {
}

void GPSSimulator::start(const QPointF& point1, const QPointF& point2, double speed) {
   if (m_running)
      return;
   m_x = point1.x();
   m_y = point1.y();

   m_dx = point2.x() - point1.x();
   m_dy = point2.y() - point1.y();
   m_speed = speed * 1852.0 / 3600.0; // convert knots to m/s

   m_steps = distance(point1, point2) / m_speed * m_freq;
   m_current_step = 0;

   m_dx_inc = m_dx / m_steps;
   m_dy_inc = m_dy / m_steps;

   m_running = true;
   QTimer::singleShot(1000.0/m_freq , this, SLOT(tick())); //25Hz
}

void GPSSimulator::stop() {
   m_running = false;
}

void GPSSimulator::tick() {
   m_x += m_dx_inc;
   m_y += m_dy_inc;
   emit positionChanged(PointWorldCoord(m_x, m_y));

   m_current_step++;
   if (m_current_step >= m_steps)
      m_running = false;

   if (m_running)
        QTimer::singleShot(1000.0 / m_freq, this, SLOT(tick()));
   else {
      emit stopped();
   }
}

qreal GPSSimulator::distance(const QPointF& point1, const QPointF& point2) {
   QGeoCoordinate gc1(point1.y(), point1.x());
   QGeoCoordinate gc2(point2.y(), point2.x());
   return gc1.distanceTo(gc2);
}