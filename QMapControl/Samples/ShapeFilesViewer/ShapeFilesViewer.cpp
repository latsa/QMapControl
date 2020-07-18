//
// Created by fuga on 18/07/2020.
//

#include "ShapeFilesViewer.h"

#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

#include <stdexcept>
#include <sstream>

using namespace qmapcontrol;

ShapeFilesViewer::ShapeFilesViewer()
: QMainWindow(nullptr)
{
    map = new QMapControl(QSizeF(800,600),this);

    baseAdapter = std::make_shared<MapAdapterOSM>();
    baseLayer = std::make_shared<LayerMapAdapter>("OpenStreetMap", baseAdapter);

    map->addLayer(baseLayer);

    map->setMapFocusPoint(PointWorldCoord(  -77.042793, -12.046374));
    map->setZoom(9);
    map->setBackgroundColour(Qt::white);

    setCentralWidget(map);

    buildMenu();
}

void ShapeFilesViewer::buildMenu() {
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    auto actionSelectShapeFile = new QAction("Load Shapefile...");
    fileMenu->addAction(actionSelectShapeFile);

    connect(actionSelectShapeFile, &QAction::triggered, this, &ShapeFilesViewer::onLoadShapeFile);
}

void ShapeFilesViewer::onLoadShapeFile() {
    try
    {
        qDebug() << "Triggered";
        auto shapefile
            = QFileDialog::getOpenFileName(this, tr("Select Shapefile to load"), QString(),
                                           tr("ShapeFiles (*.shp);;All files (*.*)"));

        qDebug() << "Selected: " << shapefile;
        if(!shapefile.isEmpty())
        {
            if (shpDataSet != nullptr)
                delete shpDataSet;

            shpDataSet = (GDALDataset*)OGROpen(shapefile.toStdString().c_str(), 0, nullptr);
            if(!shpDataSet)
            {
                std::ostringstream  ss;
                ss << "Can't load shapefile " << shapefile.toStdString() << ": ";
                throw std::runtime_error(ss.str());
            }

            auto stdShapeFileName = shapefile.toStdString();

            // NOTE: the second parameter *must* be either nullstring or the name
            // of a layer present in the shape file! Otherwise nothing will be displayed.
            shpAdapter = std::make_shared<ESRIShapefile>(shpDataSet, "");

            shpAdapter->setPenPolygon(QPen(Qt::red));
            QColor col(Qt::yellow);
            col.setAlpha(64);
            shpAdapter->setBrushPolygon(QBrush(col));

            shpLayer = std::make_shared<LayerESRIShapefile>("ShapeFile-Layer");
            shpLayer->addESRIShapefile(shpAdapter);

            map->addLayer(shpLayer);
            shpLayer->setVisible(true);
        }
    } catch (std::exception &x) {
        QMessageBox::warning(this, "Error loading shapefile", x.what());
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GDALAllRegister();

    ShapeFilesViewer mainWindow;
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}