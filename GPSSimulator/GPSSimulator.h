#pragma once
#include <QtCore/QObject>
#include <Point.h>

using namespace qmapcontrol;

class GPSSimulator :
   public QObject {
   Q_OBJECT

public:
    explicit GPSSimulator(QObject* parent = 0);

    GPSSimulator(const GPSSimulator&) = delete;
    GPSSimulator& operator=(const GPSSimulator&) = delete;
    ~GPSSimulator() = default;

    void start(const QPointF& point1, const QPointF& point2, double speed);
    void stop();


public slots:
    void tick();

signals:
    void positionChanged(PointWorldCoord point);
    void stopped();

private:
    qreal distance(const QPointF& point1, const QPointF& point2);

    bool m_running = false;
    double m_freq = 25; //Hz

    int m_steps = 0;
    int m_current_step = 0;
    double m_dx_inc = 0.0;
    double m_dy_inc = 0.0;

    double m_dx = 0.0;
    double m_dy = 0.0;
    double m_speed = 0.0;

    double m_x;
    double m_y;
};
