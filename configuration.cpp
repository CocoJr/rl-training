#include "configuration.h"
#include "mainwindow.h"

Configuration::Configuration(MainWindow *parent): parent(parent)
{
    this->initConfiguration();
    this->checkInstallationDirectory();
}

void Configuration::initConfiguration()
{
    QFile file;
    QString fileValue;

    file.setFileName(this->filename);
    if (file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        fileValue = file.readAll();
        file.close();

        QJsonDocument fileDocument = QJsonDocument::fromJson(fileValue.toUtf8());
        this->configurationJsonObject = fileDocument.object();
        if (!this->configurationJsonObject.contains("installDirectory")) {
            this->configurationJsonObject.insert("installDirectory", this->defaultInstallationDirectory);
            this->saveConfiguration();
        }

        this->installationDirectory = this->configurationJsonObject["installDirectory"].toString();

        return;
    }

    file.open(QFile::WriteOnly | QFile::Text);
    if (!file.isOpen()) {
        file.close();

        exit(EXIT_FAILURE);
    }

    file.write("{}");
    file.close();

    return this->initConfiguration();
}

void Configuration::saveConfiguration()
{
    QFile file;

    file.setFileName(this->filename);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);

    QJsonDocument configurationJsonDocument;
    configurationJsonDocument.setObject(this->configurationJsonObject);

    file.write(configurationJsonDocument.toJson());
    file.close();
}

void Configuration::checkInstallationDirectory()
{
    QFileInfo dirInfo(this->installationDirectory);
    if ((!dirInfo.exists()) || (!dirInfo.isDir())) {
        this->askInstallationDirectory();
    } else {
        // Check TAGame folder
        QFileInfo tagameDirInfo(this->installationDirectory + this->tagameSubDirectory);
        if ((!tagameDirInfo.exists()) || (!tagameDirInfo.isDir())) {
            this->askInstallationDirectory();
        } else {
            if (!this->configurationJsonObject.contains("installDirectory") || this->configurationJsonObject["installDirectory"] != this->installationDirectory) {
                this->configurationJsonObject.insert("installDirectory", this->installationDirectory);
                this->saveConfiguration();
            }
        }
    }
}

void Configuration::askInstallationDirectory()
{
    if (this->installationDirectory == "")
    {
        exit(EXIT_SUCCESS);
    }

    QMessageBox::critical(nullptr, "Jeux introuvable", "Impossible de trouver le répertoire d'installation du jeux. Il doit contenir le dossier \"TAGame\". Cliquez sur \"Ok\" pour continuer et choisir le dossier d'installation manuellement.");
    this->installationDirectory = QFileDialog::getExistingDirectory
            (
                nullptr,
                "Choisir le dossier d'installation",
                QDir::currentPath()
            );
    this->checkInstallationDirectory();
}

void Configuration::initConfigurationList()
{
    this->parent->setInstallationDirectoryLabel("Dossier d'installation du jeux: " + this->installationDirectory);

    QStringListModel *model = new QStringListModel(this->parent);
    QStringList List;

    foreach(const QString& key, this->configurationJsonObject.keys()) {
        if (key == "installDirectory") {
            continue;
        }

        List << key;
    }

    model->setStringList(List);
    this->parent->setConfigurationListViewModel(model);
}

void Configuration::resetTraining()
{
    foreach(const QString& configurationKey, this->configurationJsonObject.keys()) {
        if (configurationKey == "installDirectory") {
            continue;
        }

        QString mapKey = this->configurationJsonObject[configurationKey].toObject()["map"].toString();
        QJsonObject map = this->parent->getFileManager()->getMapJsonObject();
        QString mapFilename = this->installationDirectory + this->tagameSubDirectory + "\\CookedPCConsole\\" + map[mapKey].toString();

        this->parent->getMap()->replaceOriginalMapFile(mapFilename);
        this->configurationJsonObject.remove(configurationKey);
    }

    this->saveConfiguration();
}

