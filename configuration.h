#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringListModel>

class MainWindow;

class Configuration
{
private:
    MainWindow *parent;

public:
    const QString filename = "configuration.json";
    const QString defaultInstallationDirectory = "C:\\Program Files\\Epic Games\\rocketleague";
    const QString tagameSubDirectory = "\\TAGame";

    QString installationDirectory;
    QJsonObject configurationJsonObject;

    Configuration(MainWindow *parent);
    void initConfiguration();
    void saveConfiguration();
    void resetConfiguration();
    void checkInstallationDirectory();
    void askInstallationDirectory();
    void initConfigurationList();
    void resetTraining();

private:
};

#endif // CONFIGURATION_H
