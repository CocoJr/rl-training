#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QStringListModel>

class MainWindow;

class Map
{
private:
    MainWindow *parent;

public:
    Map(MainWindow *parent);

    void initMapList();
    QString getMapSelected();
    QString getMapFilename(QString key);
    void saveOriginalMapFile(QString mapFilename);
    void replaceOriginalMapFile(QString mapFilename);
};

#endif // MAP_H
