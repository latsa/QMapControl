#include "QMapWidget.h"

#include <iostream>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDateTime>
#include <QRect>
#include <QGeoCoordinate>

#include <QMapControl/GeometryLineString.h>
#include <QMapControl/GeometryPointArrow.h>
#include <QMapControl/GeometryPointCircle.h>
#include <QMapControl/GeometryPolygon.h>
#include <QMapControl/GeometryWidget.h>
#include <QMapControl/LayerGeometry.h>
#include <QMapControl/LayerMapAdapter.h>
#include <QMapControl/MapAdapterGoogle.h>
#include <QMapControl/MapAdapterYahoo.h>
#include <QMapControl/MapAdapterWMS.h>
#include <QMapControl/MapAdapterOSM.h>

QMapWidget::QMapWidget(QWidget* parent) : 
   QWidget(parent) {
   setupMaps(parent);
   setupLayout(parent);

   m_gps_modul = new GPSSimulator();
   QObject::connect(m_gps_modul, &GPSSimulator::positionChanged, this, &QMapWidget::positionChanged);
   QObject::connect(m_gps_modul, &GPSSimulator::stopped, this, &QMapWidget::sailtoNextWaypoint);
}

QMapWidget::~QMapWidget() {
}

void QMapWidget::clear() {
   reset();
   std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->clearGeometries();
   m_map_control->requestRedraw();
   m_waypoints.clear();
}

void QMapWidget::reset() {
   m_button_add_point->setChecked(false);
   m_button_del_point->setChecked(false);
   m_button_mov_point->setChecked(false);
   m_button_simulator->setChecked(false);
   m_mode = mode::nav_mode;
   m_is_moving = false;
   stopSimulator();
}

bool QMapWidget::isModified() {
   return m_is_modified;
}

void QMapWidget::setModified(bool newVal) { 
   m_is_modified = newVal;

   if (m_is_modified)
      emit contentsChanged();
}

void QMapWidget::setTrajectory(const QString& newVal) {
   setTrajectory(newVal.split("\n"));
}

qreal QMapWidget::getAttr(const QString& word, const QString& line) {
   QString s = line.mid(line.indexOf(word) + word.size());
   s = s.mid(1 + s.indexOf("="));
   s = s.mid(1 + s.indexOf("\""));
   s = s.mid(0, s.indexOf("\""));
   return atof(s.toStdString().c_str());
}

void QMapWidget::setTrajectory(const QStringList& newVal) {
   foreach(QString line, newVal) {
      QString sl = line.simplified().toLower();
      QString wp("<waypoint");
      if (sl.mid(0,wp.size()).compare(wp,Qt::CaseInsensitive))
         continue;

      PointWorldCoord coordinate;
      coordinate.setLatitude(getAttr("lat", sl));
      coordinate.setLongitude(getAttr("lon", sl));
      m_waypoints.append(coordinate.rawPoint());
   }

   updateGeometries();
}

QString QMapWidget::getTrajectoryText() {
   QString trajectory;
   
   qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
   qreal speed = 15.0;

   trajectory.append(QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"));
   trajectory.append(QString("<!DOCTYPE osm-trajectory>\n"));
   trajectory.append(QString("<trajectory time=\"%1\" speed=\"%2\" version=\"1.0\">\n").arg(timestamp).arg(speed));

   foreach(QPointF waypoint, m_waypoints) {      
      trajectory.append(QString("   <waypoint lat=\"%1\" lon=\"%2\" alt=\"0\"/>\n").arg(waypoint.y()).arg(waypoint.x()));
   }
   
   trajectory.append(QString("</trajectory>\n"));

   return trajectory;
}

///////////////////////////////////////////////////////////////////////////////

void QMapWidget::setupLayout(QWidget* parent) {
   // Create the buttons.
   m_button_add_point = new QPushButton(tr("Add New Point"));
   m_button_add_point->setCheckable(true);
   m_button_add_point->setMaximumWidth(100);
   m_button_add_point->setMaximumHeight(20);
   m_button_add_point->setFont(QFont("Verdana", 8));
   m_button_add_point->setFocusPolicy(Qt::NoFocus);
   QObject::connect(m_button_add_point, &QPushButton::toggled, this, &QMapWidget::toggleAddPoint);

   m_button_del_point = new QPushButton(tr("Delete Point"));
   m_button_del_point->setCheckable(true);
   m_button_del_point->setMaximumWidth(100);
   m_button_del_point->setMaximumHeight(20);
   m_button_del_point->setFont(QFont("Verdana", 8));
   m_button_del_point->setFocusPolicy(Qt::NoFocus);
   QObject::connect(m_button_del_point, &QPushButton::toggled, this, &QMapWidget::toggleDelPoint);

   m_button_mov_point = new QPushButton(tr("Move Point"));
   m_button_mov_point->setCheckable(true);
   m_button_mov_point->setMaximumWidth(100);
   m_button_mov_point->setMaximumHeight(20);
   m_button_mov_point->setFont(QFont("Verdana", 8));
   m_button_mov_point->setFocusPolicy(Qt::NoFocus);
   QObject::connect(m_button_mov_point, &QPushButton::toggled, this, &QMapWidget::toggleMovPoint);

   m_button_simulator = new QPushButton(tr("Simulator"));
   m_button_simulator->setCheckable(true);
   m_button_simulator->setMaximumWidth(100);
   m_button_simulator->setMaximumHeight(20);
   m_button_simulator->setFont(QFont("Verdana", 8));
   m_button_simulator->setFocusPolicy(Qt::NoFocus);
   QObject::connect(m_button_simulator, &QPushButton::toggled, this, &QMapWidget::toggleSimulator);

   // Create an inner layout to display buttons
   QVBoxLayout* layout_inner = new QVBoxLayout;
   layout_inner->addWidget(m_button_add_point);
   layout_inner->addWidget(m_button_del_point);
   layout_inner->addWidget(m_button_mov_point);
   layout_inner->addWidget(m_button_simulator);
   QSpacerItem* spacer = new QSpacerItem(0,0,QSizePolicy::Minimum, QSizePolicy::Expanding);
   layout_inner->addSpacerItem(spacer);


   // Set the main map control to use the inner layout.
   m_map_control->setLayout(layout_inner);

   // Create a main layout for the main map control.
   QHBoxLayout* layout_main = new QHBoxLayout;
   layout_main->addWidget(m_map_control);
   layout_main->setMargin(0);

   // Set the main layout to the QWidget.
   QWidget::setLayout(layout_main);
}

void QMapWidget::setupMaps(QWidget* parent) {
   // Create a new QMapControl.
   m_map_control = new QMapControl(parent);

   // Set the mouse button functionality required for the QMapControl.
   m_map_control->setMouseButtonLeft(QMapControl::MouseButtonMode::None, false);
   m_map_control->setMouseButtonRight(QMapControl::MouseButtonMode::Pan, true);

   // Enable the zoom controls.
   m_map_control->enableZoomControls(true, false);

   // Create a base map adapter to use.
   std::shared_ptr<MapAdapter> map_adapter(std::make_shared<MapAdapterGoogle>(MapAdapterGoogle::GoogleLayerType::MAPS));
   //std::shared_ptr<MapAdapter> map_adapter(std::make_shared<MapAdapterOSM>());

   // Create/add a layer with the selected map adapter.
   m_map_control->addLayer(std::make_shared<LayerMapAdapter>("Map Layer", map_adapter));

   // Create a layer to store geometries.
   m_layer_geometries = std::make_shared<LayerGeometry>("Geometry Layer");
   m_map_control->addLayer(m_layer_geometries);

   m_line_string = std::make_shared<GeometryLineString>(std::vector<PointWorldCoord>());

   // Create a GeometryArrow with a heading set.
   m_arrow_point = std::shared_ptr<GeometryPointArrow>(std::make_shared<GeometryPointArrow>(PointWorldCoord(0.0, 0.0), QSizeF(15.0, 15.0)));
   m_arrow_point->setPen(QPen(Qt::red));
   m_arrow_point->setVisible(false);
   m_layer_geometries->addGeometry(m_arrow_point);

   // Create GeometryPoints with PushButton widgets.
   QPushButton* pb_nav = new QPushButton("Navigate", m_map_control);
   std::shared_ptr<GeometryWidget> widget_point(std::make_shared<GeometryWidget>(PointWorldCoord(-20.0, -20.0), pb_nav));
   widget_point->setAlignmentType(GeometryPoint::AlignmentType::TopLeft);
   widget_point->setMetadata("name", "nav_button");
   widget_point->setBaseZoom(3);
   m_layer_geometries->addGeometry(widget_point);

   // Make sure we are not following any geometry.
   m_map_control->stopFollowingGeometry();
   
   // Connect the signal/slots are required.
   QObject::connect(m_map_control, &QMapControl::geometryClicked, this, &QMapWidget::geometryClickEvent);
   //QObject::connect(m_map_control, &QMapControl::geometriesSelected, this, &QMapWidget::geometriesSelectedEvent);
   QObject::connect(m_map_control, &QMapControl::mouseEventPressCoordinate, this, &QMapWidget::main_mouseEventPressCoordinate);
   QObject::connect(m_map_control, &QMapControl::mouseEventMoveCoordinate, this, &QMapWidget::main_mouseEventMoveCoordinate);
   QObject::connect(m_map_control, &QMapControl::mouseEventReleaseCoordinate, this, &QMapWidget::main_mouseEventReleaseCoordinate);
   QObject::connect(m_map_control, &QMapControl::keyPressed, this, &QMapWidget::main_keyPressed); 
}


void QMapWidget::resizeEvent(QResizeEvent* event) {
   m_map_control->setViewportSize(event->size());
}

///////////////////////////////////////////////////////////////////////////////

/*
void QMapWidget::geometriesSelectedEvent(std::map<std::string, std::vector<std::shared_ptr<Geometry>>> selected_geometries) {
   for (const auto& layers : selected_geometries) {
      for (const auto& geometry : layers.second) {
         geometryClickEvent(geometry.get());
      }
   }
}
*/

void QMapWidget::geometryClickEvent(const Geometry* geometry) {
   m_geometry_clicked = true;

   if (geometry->geometryType() == Geometry::GeometryType::GeometryPoint) {
      // QMessageBox::information(this, geometry->metadata("name").toString(), geometry->metadata("name").toString());
   }
}

///////////////////////////////////////////////////////////////////////////////

void QMapWidget::main_mouseEventPressCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate) {

   if (mode::nav_mode == m_mode) {
      //..
   } else
   if (mode::add_mode == m_mode) {
      if (mouse_event->button() == Qt::MouseButton::LeftButton) {
         addWayPoint(press_coordinate);
      }
   } else
   if (mode::del_mode == m_mode) {
      if (mouse_event->button() == Qt::MouseButton::LeftButton) {
         delWayPoint(press_coordinate);
      }
   } else
   if (mode::mov_mode == m_mode) {
      if (mouse_event->button() == Qt::MouseButton::LeftButton) {
         if (m_is_moving) {
            movWayPointEnd(press_coordinate);
         } else {
            movWayPointBeg(press_coordinate);
         }      
      }
   } 

   if (m_geometry_clicked)
      m_geometry_clicked = false;
}

void QMapWidget::addWayPoint(const PointWorldCoord& press_coordinate) {

   // Save last point, we'll need it later to draw a line between this point and the newly added point
   QPointF last_point;
   if (m_waypoints.size()) {
      last_point = m_waypoints.at(m_waypoints.size() - 1);
   }

   // Add a new waypoint
   QPointF this_point = press_coordinate.rawPoint();
   m_waypoints.append(press_coordinate.rawPoint());

   updateGeometries();

   // Add a GeometryPointCircle with a radius of 10.0 pixels.
   std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(press_coordinate, QSizeF(10.0, 10.0)));
}

void QMapWidget::delWayPoint(const PointWorldCoord& press_coordinate) {
   QPointF this_point = press_coordinate.rawPoint();
   m_waypoints.remove(closestPoint(this_point));
   updateGeometries();
}

void QMapWidget::movWayPointBeg(PointWorldCoord& press_coordinate) {
   m_prev_coordinate = press_coordinate;
   QPointF this_point = press_coordinate.rawPoint();
   m_prev_waypoint_index = closestPoint(this_point);

   // Add a GeometryPointCircle with a radius of 12.0 pixels.
   std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(PointWorldCoord(m_waypoints.at(m_prev_waypoint_index).x(), m_waypoints.at(m_prev_waypoint_index).y()), QSizeF(12.0, 12.0)));

   m_is_moving = true;
}

void QMapWidget::movWayPointEnd(PointWorldCoord& press_coordinate) {
   m_is_moving = false;
   m_prev_coordinate = press_coordinate;

   int i = m_prev_waypoint_index;
   if (i > -1 && i < m_waypoints.size()) {
      QPointF this_point = press_coordinate.rawPoint();
      m_waypoints.insert(i, this_point);
      m_waypoints.remove(i+1);

      std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->clearGeometries();
      for (int i = 0; i < m_waypoints.size(); i++) {
            std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(PointWorldCoord(m_waypoints.at(i).x(), m_waypoints.at(i).y()), QSizeF(10.0, 10.0)));
      }
   }

   updateGeometries();
}

int QMapWidget::closestPoint(QPointF point) {
   qreal min_d = 400;
   int min_i = 0;

   for (int i = 0; i < m_waypoints.size(); i++) {
      qreal dx = m_waypoints.at(i).x() - point.x();
      qreal dy = m_waypoints.at(i).y() - point.y();
      qreal d = sqrt(dx * dx + dy * dy);

      if (d < min_d) {
         min_d = d; min_i = i;
      }
   }

   return min_i;
}

void QMapWidget::updateGeometries() {

   std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->clearGeometries();
   for (int i = 0; i < m_waypoints.size(); i++) {
      std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(PointWorldCoord(m_waypoints.at(i).x(), m_waypoints.at(i).y()), QSizeF(10.0, 10.0)));
   }

   // Add line segments
   QPen pen(QColor(255, 0, 255, 100));
   pen.setWidth(4);

   // Create points vector
   std::vector<PointWorldCoord> points;
   for (int i = 0; i < m_waypoints.size(); i++)
      points.push_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(m_waypoints.at(i).x(), m_waypoints.at(i).y()))->coord());

   // Add the GeometryLineString to the Geometry layer.
   m_line_string->setPen(pen);
   m_line_string->setPoints(points);
   m_layer_geometries->addGeometry(m_line_string);

   // Create a GeometryArrow with a heading set.
   if (m_mode == mode::sim_mode && m_waypoints.size()) {
      m_arrow_point = std::shared_ptr<GeometryPointArrow>(std::make_shared<GeometryPointArrow>(PointWorldCoord(m_waypoints.at(m_gps_current_waypoint_index).x(), m_waypoints.at(m_gps_current_waypoint_index).y()), QSizeF(15.0, 15.0)));
      m_arrow_point->setPen(QPen(Qt::red));
      m_layer_geometries->addGeometry(m_arrow_point);

      m_arrow_point->setVisible(m_button_simulator->isChecked());
   }

   setModified(true);
}

void QMapWidget::main_mouseEventMoveCoordinate(QMouseEvent* /*mouse_event*/, PointWorldCoord /*press_coordinate*/, PointWorldCoord current_coordinate) {
   if (m_is_moving) {
      m_prev_coordinate = current_coordinate;

      int i = m_prev_waypoint_index;
      if (i > -1 && i < m_waypoints.size()) {
         QPointF this_point = current_coordinate.rawPoint();
         m_waypoints.insert(i, this_point);
         m_waypoints.remove(i + 1);

         std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->clearGeometries();
         for (int i = 0; i < m_waypoints.size(); i++) {
            std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(PointWorldCoord(m_waypoints.at(i).x(), m_waypoints.at(i).y()), QSizeF(10.0, 10.0)));
         }
      }

      updateGeometries();
   }
}

void QMapWidget::main_mouseEventReleaseCoordinate(QMouseEvent* /*mouse_event*/, PointWorldCoord /*press_coordinate*/, PointWorldCoord /*release_coordinate*/) {
   if (m_is_moving) {

   }
}

void QMapWidget::toggleAddPoint() {

   if (m_button_add_point->isChecked()) {
      m_mode = mode::add_mode;
      m_button_del_point->setChecked(false);
      m_button_mov_point->setChecked(false);
      m_button_simulator->setChecked(false);
      stopSimulator();
   } else
   if (!m_button_del_point->isChecked() && !m_button_mov_point->isChecked() && !m_button_simulator->isChecked())
      m_mode = mode::nav_mode;

   updateGeometries();
}

void QMapWidget::toggleDelPoint() {

   if (m_button_del_point->isChecked()) {
      m_mode = mode::del_mode;
      m_button_add_point->setChecked(false);
      m_button_mov_point->setChecked(false);
      m_button_simulator->setChecked(false);
      stopSimulator();
   } else
   if (!m_button_add_point->isChecked() && !m_button_mov_point->isChecked() && !m_button_simulator->isChecked())
      m_mode = mode::nav_mode;

   updateGeometries();
}

void QMapWidget::toggleMovPoint() {
   
   if (m_button_mov_point->isChecked()) {
      m_mode = mode::mov_mode;
      m_button_add_point->setChecked(false);
      m_button_del_point->setChecked(false);
      m_button_simulator->setChecked(false);
      stopSimulator();
   } else
   if (!m_button_add_point->isChecked() && !m_button_del_point->isChecked() && !m_button_simulator->isChecked())
      m_mode = mode::nav_mode;

   updateGeometries();
}

void QMapWidget::main_keyPressed(QKeyEvent* key_event) {
   if (Qt::Key_Escape == key_event->key()) {
      reset();
   }
}

///////////////////////////////////////////////////////////////////////////////

void QMapWidget::startSimulator(const QPointF& point1, const QPointF& point2, const qreal& speed) {
   //m_map_control->followGeometry(m_arrow_point);
   m_gps_modul->start(point1, point2, 15.0);
}

void QMapWidget::stopSimulator() {
   m_gps_modul->stop();
   m_gps_current_waypoint_index = 0;
   m_map_control->stopFollowingGeometry();
}


void QMapWidget::toggleSimulator() {
   if (m_button_simulator->isChecked()) {
      m_mode = mode::sim_mode;
      m_button_add_point->setChecked(false);
      m_button_del_point->setChecked(false);
      m_button_mov_point->setChecked(false);
   }
   else
      if (!m_button_add_point->isChecked() && !m_button_del_point->isChecked() && !m_button_mov_point->isChecked())
         m_mode = mode::nav_mode;

   updateGeometries();

   ////////////////////////////
   
   if (m_waypoints.size() < 2) {
      m_button_simulator->setChecked(false);
      StatusBarMessage(QString("Cannot start simulator. At least two waypoints are needed."), 6000);
      return;
   }

   if (m_button_simulator->isChecked()) {
      sailtoNextWaypoint();
   } else {
      stopSimulator();
   }
}

void QMapWidget::positionChanged(PointWorldCoord point) {
   m_arrow_point->setCoord(point);
   QString msg = QString("lat=%1 lon=%2").arg(point.latitude()).arg(point.longitude());
   emit StatusBarMessage(msg, 0);
   setModified(true);
}

void QMapWidget::sailtoNextWaypoint() {
   if (!m_button_simulator->isChecked())
      return;

   QPointF point1 = m_waypoints.at(m_gps_current_waypoint_index);

   m_gps_current_waypoint_index++;
   if (m_gps_current_waypoint_index < m_waypoints.size()) {
      QPointF point2 = m_waypoints.at(m_gps_current_waypoint_index);

      m_arrow_point->setRotation(bearing(point1, point2));
      m_arrow_point->setCoord(PointWorldCoord(point1.x(), point1.y()));
      m_arrow_point->setVisible(true);
      setModified(true);
      qreal speed = 15.0;
      startSimulator(point1,point2,speed);
   }
}

qreal QMapWidget::bearing(const QPointF& point1, const QPointF& point2) {
   QGeoCoordinate gc1(point1.y(), point1.x());
   QGeoCoordinate gc2(point2.y(), point2.x());
   return gc1.azimuthTo(gc2);
}

// That's it
///////////////////////////////////////////////////////////////////////////////




