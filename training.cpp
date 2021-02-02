#include "training.h"
#include "mainwindow.h"

Training::Training(MainWindow* parent): parent(parent)
{

}

void Training::initTrainingList()
{
    QStringListModel *model = new QStringListModel(this->parent);
    QStringList List;

    QJsonObject trainingJsonObject = this->parent->getFileManager()->getTrainingJsonObject();

    bool property_matched = false;
    foreach(const QString& key, trainingJsonObject.keys()) {
        foreach(const QString& configurationKey, this->parent->getConfiguration()->configurationJsonObject.keys()) {
            if (this->parent->getConfiguration()->configurationJsonObject[configurationKey].toObject()["training"].toString() == key) {
                property_matched = true;
                break;
            }
        }
        if (property_matched) {
            property_matched = false;
            continue;
        }

        List << key;
    }

    model->setStringList(List);
    this->parent->setTrainingListViewModel(model);
}

QString Training::getTrainingSelected()
{
    QModelIndex index = this->parent->getTrainingListViewSelectedIndex();

    return index.data(Qt::DisplayRole).toString();
}

bool Training::installTrainingMap(QString configurationKey)
{
    QFile file;

    QJsonObject configuration = this->parent->getConfiguration()->configurationJsonObject[configurationKey].toObject();
    QJsonObject map = this->parent->getFileManager()->getMapJsonObject();
    QJsonObject training = this->parent->getFileManager()->getTrainingJsonObject();
    QString mapKey = configuration["map"].toString();
    QString trainingKey = configuration["training"].toString();
    QString mapFilename = this->parent->getConfiguration()->installationDirectory + this->parent->getConfiguration()->tagameSubDirectory + "\\CookedPCConsole\\" + map[mapKey].toString();
    QString trainingFilename = "./"+training[trainingKey].toString();

    file.setFileName(trainingFilename);
    if (!file.exists()) {
        if (trainingFilename.indexOf("./RLT_") != 0) {
            return false;
        }

        this->parent->showDlWindow();
        this->parent->getFileManager()->downloadFileFromRepository("rlt_maps/" + trainingFilename, "./" + trainingFilename);
        this->parent->hideDlWindow();
    }

    file.setFileName(mapFilename);
    file.copy(mapFilename+".RLT_ORIGINAL");

    file.setFileName(mapFilename);
    file.remove();

    file.setFileName(trainingFilename);
    file.copy(mapFilename);

    file.setFileName(mapFilename);
    file.setPermissions(file.permissions() | QFileDevice::WriteOwner | QFileDevice::WriteUser | QFileDevice::WriteGroup | QFileDevice::WriteOther);

    return true;
}

bool Training::add(QString name, QString file)
{
    QJsonObject training = this->parent->getFileManager()->getTrainingJsonObject();
    if (training[name].toString() == "") {
        training.insert(name, file);

        this->parent->getFileManager()->saveTrainingFile(training);

        return true;
    }

    return false;
}
