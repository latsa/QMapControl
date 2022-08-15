#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "TrajectoryEditor.h"

int main(int argc, char *argv[]) {
   Q_INIT_RESOURCE(TrajectoryEditor);
   QApplication app(argc, argv);
   
   QCoreApplication::setOrganizationName("OSM");
   QCoreApplication::setApplicationName("Trajectory Editor");
   QCoreApplication::setApplicationVersion("1.00");
   QCommandLineParser parser;
   parser.setApplicationDescription(QCoreApplication::applicationName());
   parser.addHelpOption();
   parser.addVersionOption();
   parser.addPositionalArgument("file", "The file to open.");
   parser.process(app);
   
   TrajectoryEditor trajectoryEditor;

   if (!parser.positionalArguments().isEmpty())
      trajectoryEditor.loadFile(parser.positionalArguments().first());

   QDesktopWidget desktop;
   QRect screenSize = desktop.screenGeometry();
   float z = 0.9;
   screenSize.setTop((int)((1.0 - z) * (float)screenSize.height() / 2.0));
   screenSize.setLeft((int)((1.0 - z) * (float)screenSize.width() / 2.0));
   screenSize.setWidth((int)(z * (float)screenSize.width()));
   screenSize.setHeight((int)(z * (float)screenSize.height()));
   trajectoryEditor.setGeometry(screenSize);
   trajectoryEditor.setWindowTitle(QString("%1 %2").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()));
   trajectoryEditor.show();
   return app.exec();
}
