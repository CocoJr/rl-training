#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QStringListModel>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>
#include <QDesktopServices>
#include "dlwindow.h"
#include "addtrainingwindow.h"
#include "filemanager.h"
#include "configuration.h"
#include "map.h"
#include "training.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setInstallationDirectoryLabel(QString str);
    void setConfigurationListViewModel(QStringListModel *model);
    QModelIndex getMapListViewSelectedIndex();
    void setMapListViewModel(QStringListModel *model);
    QModelIndex getTrainingListViewSelectedIndex();
    void setTrainingListViewModel(QStringListModel *model);
    Configuration* getConfiguration();
    FileManager* getFileManager();
    Map* getMap();
    Training* getTraining();
    void showDlWindow();
    void hideDlWindow();
    void loadCurrentConfiguration();

private slots:
    void showMapList();
    void showAssociateBtn();
    void showTrainingRemoveBtn();
    void associateTrainingToMap();
    void removeTrainingConfiguration();
    void resetTraining();
    void startGame();
    void showAddTrainingWindow();
    void removeTraining();

private:
    Ui::MainWindow *ui;
    DlWindow *dlWindow;
    AddTrainingWindow *addTrainingWindow;
    FileManager *fileManager;
    Configuration *configuration;
    Map *map;
    Training *training;
    QString directory;

    void resetTrainingConfiguration();
    void saveCurrentConfiguration();
};

#endif // MAINWINDOW_H
