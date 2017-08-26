#ifndef SPORTSMANADDINGDIALOG_H
#define SPORTSMANADDINGDIALOG_H

#include <QDialog>

namespace Ui {
class SportsmanAddingDialog;
}

class SportsmanAddingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SportsmanAddingDialog(QWidget *parent = 0);
    ~SportsmanAddingDialog();

private:
    Ui::SportsmanAddingDialog *ui;
};

#endif // SPORTSMANADDINGDIALOG_H
