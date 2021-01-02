#ifndef TRAININGFAQ_H
#define TRAININGFAQ_H

#include <QDialog>

namespace Ui {
class TrainingFaq;
}

class TrainingFaq : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingFaq(QWidget *parent = nullptr);
    ~TrainingFaq();

private:
    Ui::TrainingFaq *ui;
};

#endif // TRAININGFAQ_H
