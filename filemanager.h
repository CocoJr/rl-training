#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMainWindow>
#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QEventLoop>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class FileManager : public QObject
{
    Q_OBJECT

private:
    const QString repositoryUrl = "https://github.com/CocoJr/rl-training";
    const QString trainingFilename = "training.json";
    const QString mapFilename = "map.json";
    QJsonObject getJsonObject(QString filename);

public:
    FileManager();

    QJsonObject getTrainingJsonObject();
    QJsonObject getMapJsonObject();
    void downloadFileFromRepository(QString filename, QString destination);
    void saveTrainingFile(QJsonObject training);
};

#endif // FILEMANAGER_H
