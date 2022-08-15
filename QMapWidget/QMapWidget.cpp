#include "QMapWidget.h"

#include <iostream>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

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

   // m_gps_modul = new GPSSimulator();
   // QObject::connect(m_gps_modul, &GPSSimulator::positionChanged, m_gps_point.get(), &GeometryPointImage::setCoord);
   // QObject::connect(m_gps_modul, &GPSSimulator::positionChanged, this, &QMapWidget::positionChanged);
   // m_gps_modul->start();
}

QMapWidget::~QMapWidget() {
}

void QMapWidget::clear() {
   std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->clearGeometries();
   m_map_control->requestRedraw();
   m_waypoints.clear();
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
      std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(coordinate, QSizeF(10.0, 10.0)));
   }
}

QStringList QMapWidget::getTrajectoryList() {
   QStringList trajectory;

   trajectory.append(QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
   trajectory.append(QString("<!DOCTYPE osm-trajectory>"));
   trajectory.append(QString("<trajectory version=\"1.0\">"));

   foreach(QPointF waypoint, m_waypoints) {
      trajectory.append(QString("   <waypoint lat=\"%1\" lon=\"%2\" alt=\"0\"/>").arg(waypoint.x()).arg(waypoint.y()));
   }

   trajectory.append(QString("</trajectory>"));

   return trajectory;
}

QString QMapWidget::getTrajectoryText() {
   QString trajectory;
   
   trajectory.append(QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"));
   trajectory.append(QString("<!DOCTYPE osm-trajectory>\n"));
   trajectory.append(QString("<trajectory version=\"1.0\">\n"));

   foreach(QPointF waypoint, m_waypoints) {      
      trajectory.append(QString("   <waypoint lat=\"%1\" lon=\"%2\" alt=\"0\"/>\n").arg(waypoint.x()).arg(waypoint.y()));
   }
   
   trajectory.append(QString("</trajectory>\n"));

   return trajectory;
}

///////////////////////////////////////////////////////////////////////////////

void QMapWidget::setupLayout(QWidget* parent) {
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
   m_map_control->setMouseButtonRight(QMapControl::MouseButtonMode::None, false);

   // Enable the zoom controls.
   m_map_control->enableZoomControls(true, false);

   // Create a base map adapter to use.
   std::shared_ptr<MapAdapter> map_adapter(std::make_shared<MapAdapterGoogle>(MapAdapterGoogle::GoogleLayerType::MAPS));
   //std::shared_ptr<MapAdapter> map_adapter(std::make_shared<MapAdapterOSM>());

   // Create/add a layer with the selected map adapter.
   m_map_control->addLayer(std::make_shared<LayerMapAdapter>("Map Layer", map_adapter));

   // Create a layer to store geometries.
   std::shared_ptr<LayerGeometry> layer_geometries(std::make_shared<LayerGeometry>("Geometry Layer"));
   m_map_control->addLayer(layer_geometries);

   // Create some GeometryPoints to add to a GeometryLineString.
   // QPen pen(QColor(255, 0, 0, 100));
   // pen.setWidth(2);
   // std::vector<std::shared_ptr<GeometryPoint>> points;
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.259959, 50.001781)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Hauptbahnhof");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.263758, 49.998917)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Münsterplatz");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.265812, 50.001952)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Neubrunnenplatz");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.2688, 50.004015)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Bauhofstraße LRP");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.272845, 50.00495)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Landtag");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.272845, 50.00495)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Brückenplatz");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.280349, 50.008173)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Mainz, Brückenkopf");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.273573, 50.016315)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Wiesbaden-Mainz-Kastel, Eleonorenstraße");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.275145, 50.016992)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Wiesbaden-Mainz-Kastel, Johannes-Goßner-Straße");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.270476, 50.021426)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Wiesbaden-Mainz-Kastel, Ruthof");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.266445, 50.025913)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Wiesbaden-Mainz-Kastel, Mudra Kaserne");
   // points.emplace_back(std::make_shared<GeometryPointCircle>(PointWorldCoord(8.260378, 50.030345)));
   // points.back()->setPen(pen);
   // points.back()->setMetadata("name", "Wiesbaden-Mainz-Amoneburg, Dyckerhoffstraße");

   // A QPen also can use transparency.
   // pen = QPen(QColor(0, 0, 255, 100));
   // pen.setWidth(5);

   // Add the GeometryPoints to GeometryLineString.
   // std::vector<PointWorldCoord> raw_points;
   // for (const auto& point : points) {
   //    // Add the point.
   //    raw_points.push_back(point->coord());
   // 
   //    // Also add the point to the custom layer.
   //    layer_geometries->addGeometry(point);
   // }

   // m_line_string = std::make_shared<GeometryLineString>(std::vector<PointWorldCoord>());
   // m_line_string->setPen(pen);
   // m_line_string->setMetadata("name", "Busline 54");
   //    m_line_string->setPoints(raw_points);

   // Add the GeoemtryLineString to the Geometry layer.
   // layer_geometries->addGeometry(m_line_string);


   // Create a GPS GeometryPoint that can dynamically move, and add it to the geometry layer.
   // m_gps_point = std::make_shared<GeometryPointImage>(PointWorldCoord(0.0, 0.0), ":/resources/images/marker1.png");
   // m_gps_point->setAlignmentType(GeometryPoint::AlignmentType::TopRight);
   // m_gps_point->setMetadata("name", "image point");
   // layer_geometries->addGeometry(m_gps_point);

   // Create a GeometryArrow with a heading set.
   // std::shared_ptr<GeometryPointArrow> arrow_point(std::make_shared<GeometryPointArrow>(PointWorldCoord(-20.0, 20.0), QSizeF(15.0, 15.0)));
   // arrow_point->setPen(QPen(Qt::red));
   // arrow_point->setRotation(92.4);
   // layer_geometries->addGeometry(arrow_point);

   // Create a GeometryPoint with a PushButton widget.
   // QPushButton* pb = new QPushButton("test button", m_map_control);
   // std::shared_ptr<GeometryWidget> widget_point(std::make_shared<GeometryWidget>(PointWorldCoord(-20.0, -20.0), pb));
   // widget_point->setAlignmentType(GeometryPoint::AlignmentType::TopLeft);
   // widget_point->setMetadata("name", ".");
   // widget_point->setBaseZoom(3);
   // layer_geometries->addGeometry(widget_point);

   // Make sure we are not following any geometry.
   m_map_control->stopFollowingGeometry();
   //m_map_control->followGeometry(m_gps_point);

   // Connect the signal/slots are required.
   QObject::connect(m_map_control, &QMapControl::geometryClicked, this, &QMapWidget::geometryClickEvent);
   //QObject::connect(m_map_control, &QMapControl::geometriesSelected, this, &QMapWidget::geometriesSelectedEvent);
   QObject::connect(m_map_control, &QMapControl::mouseEventPressCoordinate, this, &QMapWidget::main_mouseEventPressCoordinate);
   QObject::connect(m_map_control, &QMapControl::mouseEventMoveCoordinate, this, &QMapWidget::main_mouseEventMoveCoordinate);
   QObject::connect(m_map_control, &QMapControl::mouseEventReleaseCoordinate, this, &QMapWidget::main_mouseEventReleaseCoordinate);
}


void QMapWidget::resizeEvent(QResizeEvent* event) {
   m_map_control->setViewportSize(event->size());
}

///////////////////////////////////////////////////////////////////////////////

void QMapWidget::positionChanged(const PointWorldCoord& point)
{
   std::cout << "Position updated (" << point.latitude() << "," << point.longitude() << ")"
      << std::endl;
   m_line_string->addPoint(point);
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

   if (mouse_event->button() == Qt::MouseButton::LeftButton) {

      if (m_geometry_clicked) {
         //..
      } else {
         // Add a GeometryPointCircle with a radius of 10.0 pixels.
         std::static_pointer_cast<LayerGeometry>(m_map_control->getLayer("Geometry Layer"))->addGeometry(std::make_shared<GeometryPointCircle>(press_coordinate, QSizeF(10.0, 10.0)));

         // Add a new waypoint
         m_waypoints.append(press_coordinate.rawPoint());
         setModified(true);
      }
   }
   else if (mouse_event->button() == Qt::MouseButton::RightButton) {
      if (m_geometry_clicked) {
         //..
      }
      else {
         //..
      }
   }
   
   if (m_geometry_clicked)
      m_geometry_clicked = false;
}

void QMapWidget::main_mouseEventMoveCoordinate(QMouseEvent* /*mouse_event*/, PointWorldCoord /*press_coordinate*/, PointWorldCoord /*current_coordinate*/) {
   //..
}

void QMapWidget::main_mouseEventReleaseCoordinate(QMouseEvent* /*mouse_event*/, PointWorldCoord /*press_coordinate*/, PointWorldCoord /*release_coordinate*/) {
   //..
}

// That's it
///////////////////////////////////////////////////////////////////////////////



