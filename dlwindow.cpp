#include "dlwindow.h"
#include "ui_dlwindow.h"

DlWindow::DlWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlWindow)
{
    ui->setupUi(this);
}

DlWindow::~DlWindow()
{
    delete ui;
}
