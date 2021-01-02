#ifndef ADDTRAININGWINDOW_H
#define ADDTRAININGWINDOW_H

#include <QDialog>
#include <trainingfaq.h>

class MainWindow;

namespace Ui {
class AddTrainingWindow;
}

class AddTrainingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainingWindow(MainWindow *parent = nullptr);
    ~AddTrainingWindow();

public slots:
    void hideAddTrainingWindow();
    void askFile();
    void onNameChange(QString value);
    void add();
    void showFaq();

private:
    QString file = "";
    QString name = "";
    MainWindow* parent;
    Ui::AddTrainingWindow *ui;
    TrainingFaq* trainingFaqWindow;
    void switchValidateBtn();
};

#endif // ADDTRAININGWINDOW_H
