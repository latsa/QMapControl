#pragma once
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPoint>

#include "qmapwidget_global.h"
#include "QMapControl.h"

#include <QMapControl/GeometryLineString.h>
#include <QMapControl/QMapControl.h>
#include <QMapControl/GeometryPointImage.h>

#include "GPSSimulator/GPSSimulator.h"

using namespace qmapcontrol;

class QMAPWIDGET_EXPORT QMapWidget : 
   public QWidget {
   Q_OBJECT

public:
   QMapWidget(QWidget* parent = Q_NULLPTR);
   QMapWidget(const QMapWidget&) = delete;
   QMapWidget& operator=(const QMapWidget&) = delete;
   ~QMapWidget();

private:
   void setupLayout(QWidget* parent);
   void setupMaps(QWidget* parent);
   void resizeEvent(QResizeEvent* event) override;
   qreal getAttr(const QString& word, const QString& line);

public:
    void clear();
    bool isModified();
    void setModified(bool newVal);

    void setTrajectory(const QString& newVal);
    void setTrajectory(const QStringList& newVal);
    QStringList getTrajectoryList();
    QString getTrajectoryText();

signals:
   void contentsChanged();

private slots:
   void positionChanged(const PointWorldCoord& point);

   //void geometriesSelectedEvent(std::map<std::string, std::vector<std::shared_ptr<Geometry>>> selected_geometries);
   void geometryClickEvent(const Geometry* geometry);
   void main_mouseEventPressCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate);
   void main_mouseEventMoveCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate, PointWorldCoord current_coordinate);
   void main_mouseEventReleaseCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate, PointWorldCoord release_coordinate);

private:
   std::shared_ptr<GeometryLineString> m_line_string;
   QMapControl* m_map_control;

   // std::shared_ptr<GeometryPointImage> m_gps_point;
   // GPSSimulator* m_gps_modul;

private:
   bool m_is_modified = false;
   bool m_geometry_clicked = false;
   QVector<QPointF> m_waypoints;
};


