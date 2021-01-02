#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dlWindow(new DlWindow(this)),
    addTrainingWindow(new AddTrainingWindow(this)),
    fileManager(new FileManager),
    configuration(new Configuration(this)),
    map(new Map(this)),
    training(new Training(this))
{
    this->ui->setupUi(this);
    this->loadCurrentConfiguration();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMapList()
{
    this->ui->mapListView->setEnabled(true);
    this->ui->removeTrainingBtn->setEnabled(true);
}

void MainWindow::showAssociateBtn()
{
    this->ui->associateBtn->setEnabled(true);
}

void MainWindow::showTrainingRemoveBtn()
{
    this->ui->deleteBtn->setEnabled(true);
}

void MainWindow::associateTrainingToMap()
{
    this->ui->associateBtn->setEnabled(false);
    this->ui->mapListView->setEnabled(false);

    QJsonObject trainingJsonObject = this->fileManager->getTrainingJsonObject();
    QJsonObject mapJsonObject = this->fileManager->getMapJsonObject();

    QString key = this->map->getMapSelected() + " => " + this->training->getTrainingSelected();
    QJsonObject value;
    value.insert("map", this->map->getMapSelected());
    value.insert("training", this->training->getTrainingSelected());

    this->configuration->configurationJsonObject.insert(key, value);
    this->saveCurrentConfiguration();

    if (!this->training->installTrainingMap(key)) {
        this->configuration->configurationJsonObject.remove(key);
        this->saveCurrentConfiguration();
    }
}

void MainWindow::resetTraining()
{
    this->configuration->resetTraining();

    QStringList nameFilter("*.RLT_ORIGINAL");
    QDir directory(this->configuration->installationDirectory + this->configuration->tagameSubDirectory + "\\CookedPCConsole");
    QStringList txtFilesAndDirectories = directory.entryList(nameFilter);

    foreach (QString str, txtFilesAndDirectories) {
        QString mapFilename = this->configuration->installationDirectory + this->configuration->tagameSubDirectory + "\\CookedPCConsole\\" + str.replace(".RLT_ORIGINAL", "");

        this->map->replaceOriginalMapFile(mapFilename);
    }

    this->saveCurrentConfiguration();
}

void MainWindow::removeTrainingConfiguration()
{
    QString key = this->ui->configurationListView->currentIndex().data(Qt::DisplayRole).toString();
    QString mapKey = this->configuration->configurationJsonObject[key].toObject()["map"].toString();
    QJsonObject map = this->fileManager->getMapJsonObject();
    QString mapFilename = this->configuration->installationDirectory + this->configuration->tagameSubDirectory + "\\CookedPCConsole\\" + map[mapKey].toString();

    this->map->replaceOriginalMapFile(mapFilename);
    this->configuration->configurationJsonObject.remove(key);
    this->saveCurrentConfiguration();
}

void MainWindow::startGame()
{
    QDesktopServices::openUrl(QUrl("com.epicgames.launcher://apps/Sugar?action=launch&silent=true", QUrl::TolerantMode));
}

void MainWindow::showAddTrainingWindow()
{
    this->hide();
    this->addTrainingWindow->show();
}

void MainWindow::removeTraining()
{
    QJsonObject training = this->getFileManager()->getTrainingJsonObject();
    QString filename = training[this->training->getTrainingSelected()].toString();
    if (filename == "") {
        return;
    }

    qDebug() << filename;

    training.remove(this->training->getTrainingSelected());
    this->fileManager->saveTrainingFile(training);

    QFile file;
    file.setFileName("./"+filename);
    file.remove();

    this->loadCurrentConfiguration();
}

void MainWindow::setInstallationDirectoryLabel(QString str)
{
    this->ui->label->setText(str);
}

void MainWindow::setConfigurationListViewModel(QStringListModel *model)
{
    this->ui->configurationListView->setModel(model);
}

QModelIndex MainWindow::getMapListViewSelectedIndex()
{
    return this->ui->mapListView->currentIndex();
}

void MainWindow::setMapListViewModel(QStringListModel *model)
{
    this->ui->mapListView->setModel(model);
}

QModelIndex MainWindow::getTrainingListViewSelectedIndex()
{
    return this->ui->trainingListView->currentIndex();
}

void MainWindow::setTrainingListViewModel(QStringListModel *model)
{
    this->ui->trainingListView->setModel(model);
}

Configuration* MainWindow::getConfiguration()
{
    return this->configuration;
}

FileManager* MainWindow::getFileManager()
{
    return this->fileManager;
}


Map* MainWindow::getMap()
{
    return this->map;
}

Training* MainWindow::getTraining()
{
    return this->training;
}

void MainWindow::saveCurrentConfiguration()
{
    this->configuration->saveConfiguration();
    this->loadCurrentConfiguration();
}

void MainWindow::showDlWindow()
{
    this->dlWindow->show();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->setEnabled(false);
}

void MainWindow::hideDlWindow()
{
    this->setEnabled(true);
    QApplication::restoreOverrideCursor();
    this->dlWindow->hide();
}

void MainWindow::loadCurrentConfiguration()
{
    this->ui->removeTrainingBtn->setEnabled(false);
    this->configuration->initConfigurationList();
    this->map->initMapList();
    this->training->initTrainingList();
}
