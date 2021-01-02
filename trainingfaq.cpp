#include "trainingfaq.h"
#include "ui_trainingfaq.h"

TrainingFaq::TrainingFaq(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingFaq)
{
    ui->setupUi(this);
}

TrainingFaq::~TrainingFaq()
{
    delete ui;
}
