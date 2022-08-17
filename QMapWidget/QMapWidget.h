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
#include <QMapControl/GeometryPointArrow.h>

#include "GPSSimulator/GPSSimulator.h"

using namespace qmapcontrol;

class QMAPWIDGET_EXPORT QMapWidget : 
   public QWidget {
   Q_OBJECT

   enum class mode {
      nav_mode, add_mode, del_mode, mov_mode, sim_mode
   };

public:
   QMapWidget(QWidget* parent = Q_NULLPTR);
   QMapWidget(const QMapWidget&) = delete;
   QMapWidget& operator=(const QMapWidget&) = delete;
   ~QMapWidget();

   void clear();
   void reset();
   bool isModified();
   void setModified(bool newVal);

   void setTrajectory(const QString& newVal);
   void setTrajectory(const QStringList& newVal);
   QString getTrajectoryText();

signals:
   void contentsChanged();
   void StatusBarMessage(const QString& msg, int timeout);

private slots:
   //void geometriesSelectedEvent(std::map<std::string, std::vector<std::shared_ptr<Geometry>>> selected_geometries);
   void geometryClickEvent(const Geometry* geometry);
   void main_mouseEventPressCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate);
   void main_mouseEventMoveCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate, PointWorldCoord current_coordinate);
   void main_mouseEventReleaseCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate, PointWorldCoord release_coordinate);
   void main_keyPressed(QKeyEvent* key_event);

   void toggleAddPoint();
   void toggleDelPoint();
   void toggleMovPoint();
   void toggleSimulator();

private:
   void setupLayout(QWidget* parent);
   void setupMaps(QWidget* parent);
   void resizeEvent(QResizeEvent* event) override;
   qreal getAttr(const QString& word, const QString& line);

   void addWayPoint(const PointWorldCoord& press_coordinate);
   void delWayPoint(const PointWorldCoord& press_coordinate);
   void movWayPointBeg(PointWorldCoord& press_coordinate);
   void movWayPointEnd(PointWorldCoord& press_coordinate);
   void updateGeometries();
   int closestPoint(QPointF point);

   std::shared_ptr<GeometryLineString> m_line_string;
   QMapControl* m_map_control;

   QPushButton* m_button_add_point = Q_NULLPTR;
   QPushButton* m_button_del_point = Q_NULLPTR;
   QPushButton* m_button_mov_point = Q_NULLPTR;
   QPushButton* m_button_simulator = Q_NULLPTR;

   enum class mode m_mode = mode::nav_mode;
   bool m_is_modified = false;
   bool m_geometry_clicked = false;
   
   bool m_is_moving = false;
   PointWorldCoord m_prev_coordinate;
   int m_prev_waypoint_index = -1;

   QVector<QPointF> m_waypoints;
   std::shared_ptr<LayerGeometry> m_layer_geometries;

   // Simulator
private:
   void startSimulator(const QPointF& point1, const QPointF& point2, const qreal& speed);
   void stopSimulator();

   GPSSimulator* m_gps_modul = Q_NULLPTR;
   int m_gps_current_waypoint_index = 0;
   std::shared_ptr<GeometryPointArrow> m_arrow_point;
   qreal bearing(const QPointF& point1, const QPointF& point2);

private slots:
   void positionChanged(PointWorldCoord point);
   void sailtoNextWaypoint();
};
