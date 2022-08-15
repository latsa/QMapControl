#include "TrajectoryEditor.h"
#include <QtWidgets>

TrajectoryEditor::TrajectoryEditor(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    //m_mapWidget = new QMapWidget(parent);
    m_mapWidget = ui.mapWidget;

    createActions();
    createStatusBar();
    readSettings();
    setCurrentFile(QString());
}

void TrajectoryEditor::createActions() {

   QMenu* fileMenu = ui.menu_File;
   QToolBar* fileToolBar = ui.mainToolBar;

   QAction* newAct = ui.action_New;
   newAct->setIcon(QIcon::fromTheme("document-new", QIcon(":/images/new.png")));
   newAct->setShortcuts(QKeySequence::New);
   newAct->setStatusTip(tr("Create a new file"));
   connect(newAct, &QAction::triggered, this, &TrajectoryEditor::newFile);
   fileToolBar->addAction(newAct);

   QAction* openAct = ui.action_Open;
   openAct->setIcon(QIcon::fromTheme("document-open", QIcon(":/images/open.png")));
   openAct->setShortcuts(QKeySequence::Open);
   openAct->setStatusTip(tr("Open an existing file"));
   connect(openAct, &QAction::triggered, this, &TrajectoryEditor::open);
   fileToolBar->addAction(openAct);

   QAction* saveAct = ui.action_Save;
   saveAct->setIcon(QIcon::fromTheme("document-save", QIcon(":/images/save.png")));
   saveAct->setShortcuts(QKeySequence::Save);
   saveAct->setStatusTip(tr("Save the document to disk"));
   connect(saveAct, &QAction::triggered, this, &TrajectoryEditor::save);
   fileToolBar->addAction(saveAct);

   QAction* saveAsAct = ui.action_SaveAs;
   saveAsAct->setIcon(QIcon::fromTheme("document-save-as"));
   saveAsAct->setShortcuts(QKeySequence::SaveAs);
   saveAsAct->setStatusTip(tr("Save the document under a new name"));
   connect(saveAsAct, &QAction::triggered, this, &TrajectoryEditor::saveAs);

   QAction* exitAct = ui.action_Exit;
   exitAct->setIcon(QIcon::fromTheme("application-exit"));
   exitAct->setShortcuts(QKeySequence::Quit);
   exitAct->setStatusTip(tr("Exit the application"));
   connect(exitAct, &QAction::triggered, this, &TrajectoryEditor::quit);

   QMenu* helpMenu = ui.menu_Help;

   QAction* aboutAct = ui.action_About;
   aboutAct->setStatusTip(tr("Show the application's About box"));
   connect(aboutAct, &QAction::triggered, this, &TrajectoryEditor::about);
}

void TrajectoryEditor::createStatusBar() {
   statusBar()->showMessage(tr("Ready"));
}

void TrajectoryEditor::readSettings() {
   QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
   const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
   if (geometry.isEmpty()) {
      const QRect availableGeometry = screen()->availableGeometry();
      resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
      move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);
   }
   else {
      restoreGeometry(geometry);
   }
}

void TrajectoryEditor::writeSettings() {
   QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
   settings.setValue("geometry", saveGeometry());
}

void TrajectoryEditor::setCurrentFile(const QString& fileName) {
   m_curFile = fileName;
   m_mapWidget->setModified(false);

   if (m_curFile.isEmpty())
      m_curFile = "untitled.trj";

   setWindowFilePath(m_curFile);
   setWindowTitle(QString("%1 %2 - %3").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()).arg(QFileInfo(m_curFile).fileName()));
}

void TrajectoryEditor::loadFile(const QString& fileName) {
   QFile file(fileName);
   if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this, tr("Application"),
         tr("Cannot read file %1:\n%2.")
         .arg(QDir::toNativeSeparators(fileName), file.errorString()));
      return;
   }

   QTextStream in(&file);

#ifndef QT_NO_CURSOR
   QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif

   m_mapWidget->setTrajectory(in.readAll());

#ifndef QT_NO_CURSOR
   QGuiApplication::restoreOverrideCursor();
#endif

   setCurrentFile(fileName);
   statusBar()->showMessage(tr("File loaded"), 2000);
   m_mapWidget->setModified(false);
}

bool TrajectoryEditor::saveFile(const QString& fileName) {
   QString errorMessage;

   QGuiApplication::setOverrideCursor(Qt::WaitCursor);

   QSaveFile file(fileName);
   if (file.open(QFile::WriteOnly | QFile::Text)) {

      QTextStream out(&file);
      out << m_mapWidget->getTrajectoryText();
      if (!file.commit()) {
         errorMessage = tr("Cannot write file %1:\n%2.")
            .arg(QDir::toNativeSeparators(fileName), file.errorString());
      }
   }
   else {
      errorMessage = tr("Cannot open file %1 for writing:\n%2.")
         .arg(QDir::toNativeSeparators(fileName), file.errorString());
   }

   QGuiApplication::restoreOverrideCursor();

   if (!errorMessage.isEmpty()) {
      QMessageBox::warning(this, tr("Trajectory Editor"), errorMessage);
      return false;
   }

   setCurrentFile(fileName);
   statusBar()->showMessage(tr("File saved"), 2000);
   m_mapWidget->setModified(false);
   return true;
}

bool TrajectoryEditor::confirmSave() {
   if (!m_mapWidget->isModified())
      return true;

   const QMessageBox::StandardButton ret
      = QMessageBox::warning(this, tr("Trajectory Editor"),
         tr("The document has been modified.\n"
            "Do you want to save your changes?"),
         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

   switch (ret) {
      case QMessageBox::Save:
         return save();
      case QMessageBox::Cancel:
         return false;
      default:
         break;
   }

   return true;
}

///////////////////////////////////////////////////////////////////////////////

void TrajectoryEditor::closeEvent(QCloseEvent *event) {
   if (confirmSave()) {
      writeSettings();
      event->accept();
   } else {
      event->ignore();
   }
}

void TrajectoryEditor::quit() {
   if (!confirmSave())
      return;

   writeSettings();
   qApp->quit();
}

void TrajectoryEditor::newFile() {
   if (!confirmSave())
      return;

   m_mapWidget->clear();
   setCurrentFile(QString());
}

void TrajectoryEditor::open() {
   if (!confirmSave())
      return;

   QString fileName = QFileDialog::getOpenFileName(this);
   if (!fileName.isEmpty())
      loadFile(fileName);
}

bool TrajectoryEditor::save() {
   if (m_curFile.isEmpty())
      return saveAs();

   if (!m_curFile.compare("untitled.trj", Qt::CaseInsensitive))
      return saveAs();

   return saveFile(m_curFile);
}

bool TrajectoryEditor::saveAs() {
   QFileDialog dialog(this);
   dialog.setWindowModality(Qt::WindowModal);
   dialog.setAcceptMode(QFileDialog::AcceptSave);
   dialog.setNameFilter(tr("Trajectory Files (*.trj)"));
   dialog.setViewMode(QFileDialog::ViewMode::List);

   if (dialog.exec() != QDialog::Accepted)
      return false;

   return saveFile(dialog.selectedFiles().first());
}

void TrajectoryEditor::about() {
   QMessageBox::about(this, tr("About Trajectory Editor"),
            tr("The <b>Trajectory Editor</b> application allows creating and "
               "editing trajectory files to be used as input by the MARINA "
               "Virtual GNSS Device."));
}
