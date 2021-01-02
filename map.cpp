#include "map.h"
#include "mainwindow.h"

Map::Map(MainWindow *parent): parent(parent)
{

}

void Map::initMapList()
{
    QStringListModel *model = new QStringListModel(this->parent);
    QStringList List;

    FileManager* filemanager = this->parent->getFileManager();
    QJsonObject mapJsonObject = filemanager->getMapJsonObject();
    QJsonObject configurationObject = this->parent->getConfiguration()->configurationJsonObject;
    bool property_matched = false;
    foreach(const QString& key, mapJsonObject.keys()) {
        foreach(const QString& configurationKey, configurationObject.keys()) {
            if (configurationObject[configurationKey].toObject()["map"].toString() == key) {
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
    this->parent->setMapListViewModel(model);
}

QString Map::getMapSelected()
{
    QModelIndex index = this->parent->getMapListViewSelectedIndex();

    return index.data(Qt::DisplayRole).toString();
}


QString Map::getMapFilename(QString key)
{
    QJsonObject map = this->parent->getFileManager()->getMapJsonObject();

    return map[key].toString();
}

void Map::saveOriginalMapFile(QString mapFilename)
{
    QFile file;

    file.setFileName(mapFilename);
    file.copy(mapFilename+".RLT_ORIGINAL");
    file.close();
}

void Map::replaceOriginalMapFile(QString mapFilename)
{
    if (!QFile::exists(mapFilename+".RLT_ORIGINAL")) {
        return;
    }

    if (!QFile::remove(mapFilename)) {
        return;
    }

    if (!QFile::copy(mapFilename+".RLT_ORIGINAL", mapFilename)) {
        return;
    }

    QFile::remove(mapFilename+".RLT_ORIGINAL");
}
