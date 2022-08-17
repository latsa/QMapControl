#pragma once
#include "ui_TrajectoryEditor.h"
#include "QMapWidget.h"
#include <QMainWindow>
#include <QString>

class TrajectoryEditor :
   public QMainWindow {
    Q_OBJECT

public:
    TrajectoryEditor(QWidget *parent = Q_NULLPTR);
    void loadFile(const QString &fileName);
    bool saveFile(const QString& fileName);

protected:
    void closeEvent(QCloseEvent *event) override;
    
private slots:
   void newFile();
   void open();
   bool save();
   bool saveAs();
   void about();
   void quit();
   void StatusBarMessage(const QString& msg, int timeout);

private:
   Ui::TrajectoryEditorClass ui;

   void createActions();
   void createStatusBar();
   void readSettings();
   void writeSettings();
   void setCurrentFile(const QString& fileName);
   bool confirmSave();

   QMapWidget* m_mapWidget = Q_NULLPTR;
   QString m_curFile;
};
