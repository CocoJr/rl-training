#include "addtrainingwindow.h"
#include "ui_addtrainingwindow.h"
#include "mainwindow.h"

AddTrainingWindow::AddTrainingWindow(MainWindow *parent) :
    parent(parent),
    ui(new Ui::AddTrainingWindow),
    trainingFaqWindow(new TrainingFaq(this))
{
    ui->setupUi(this);
    this->switchValidateBtn();
}

AddTrainingWindow::~AddTrainingWindow()
{
    delete ui;
}

void AddTrainingWindow::hideAddTrainingWindow()
{
    this->hide();
    this->parent->loadCurrentConfiguration();
    this->parent->show();
}

void AddTrainingWindow::askFile()
{
    this->file = QFileDialog::getOpenFileName
            (
                nullptr,
                "Choisir le fichier .udk",
                QDir::homePath(),
                tr("UDK (*.udk)")
            );

    this->switchValidateBtn();
}

void AddTrainingWindow::onNameChange(QString value)
{
    this->name = value;

    this->switchValidateBtn();
}

void AddTrainingWindow::add()
{
    QFile file;
    QFileInfo fileInfo(this->file);
    QString filename = fileInfo.fileName();

    file.setFileName(this->file);
    if (!file.copy("./" + filename)) {
        this->ui->errorLabel->setText("La copie du fichier a échoué.");
        return;
    }

    if (!this->parent->getTraining()->add(this->name, filename)) {
        this->ui->errorLabel->setText("Une erreur est survenue.");
        return;
    }

    this->hideAddTrainingWindow();
}

void AddTrainingWindow::showFaq()
{
    this->trainingFaqWindow->show();
}

void AddTrainingWindow::switchValidateBtn()
{
    this->ui->errorLabel->setText("");
    bool enable = false;
    if (this->file != "") {
        this->ui->fileLabel->setText(file);

        if (this->name != "") {
            enable = true;
        }
    } else {
        this->ui->fileLabel->setText("Aucun fichier choisis.");
    }

    if (enable) {
        this->ui->validateBtn->setEnabled(enable);
    }
}
