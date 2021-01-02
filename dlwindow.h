#ifndef DLWINDOW_H
#define DLWINDOW_H

#include <QDialog>

namespace Ui {
class DlWindow;
}

class DlWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DlWindow(QWidget *parent = nullptr);
    ~DlWindow();

private:
    Ui::DlWindow *ui;
};

#endif // DLWINDOW_H
