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

    void start();
    void stop();

public slots:
    void tick();

signals:
    void positionChanged(PointWorldCoord point);

private:
    bool m_running;
};
