#include "filemanager.h"

FileManager::FileManager()
{
}

QJsonObject FileManager::getTrainingJsonObject()
{
    QFile file;

    file.setFileName("./" + this->trainingFilename);
    if (file.exists()) {
        return this->getJsonObject("./" + this->trainingFilename);
    }

    this->downloadFileFromRepository(this->trainingFilename, "./" + this->trainingFilename);

    return this->getTrainingJsonObject();
}

QJsonObject FileManager::getMapJsonObject()
{
    QFile file;

    file.setFileName("./" + this->mapFilename);
    if (file.exists()) {
        return this->getJsonObject("./" + this->mapFilename);
    }

    this->downloadFileFromRepository(this->mapFilename, "./" + this->mapFilename);

    return this->getMapJsonObject();
}

QJsonObject FileManager::getJsonObject(QString filename)
{
    QFile file;
    QString fileValue;

    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileValue = file.readAll();
    file.close();

    QJsonDocument fileDocument = QJsonDocument::fromJson(fileValue.toUtf8());

    return fileDocument.object();
}

void FileManager::downloadFileFromRepository(QString filename, QString destination)
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(this->repositoryUrl + "/raw/v3.1/" + filename)));
    QEventLoop event;
    connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();

    QFile file;
    file.setFileName(destination);
    file.open(QFile::WriteOnly);
    file.write(response->readAll());
    file.close();
}

void FileManager::saveTrainingFile(QJsonObject training)
{
    QJsonDocument doc(training);
    QFile file;

    file.setFileName("./" + this->trainingFilename);
    file.open(QFile::WriteOnly);
    file.write(doc.toJson());
    file.close();
}
