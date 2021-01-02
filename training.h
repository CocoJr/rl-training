#ifndef TRAINING_H
#define TRAINING_H

#include <QString>
#include <QStringListModel>

class MainWindow;

class Training
{
private:
    MainWindow *parent;

public:
    Training(MainWindow* parent);

    void initTrainingList();
    QString getTrainingSelected();
    bool installTrainingMap(QString configurationKey);
    bool add(QString name, QString file);
};

#endif // TRAINING_H
