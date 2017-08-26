#include "sportsmanaddingdialog.h"
#include "ui_sportsmanaddingdialog.h"

SportsmanAddingDialog::SportsmanAddingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SportsmanAddingDialog)
{
    ui->setupUi(this);
}

SportsmanAddingDialog::~SportsmanAddingDialog()
{
    delete ui;
}
