#ifndef INVPORTFOLIOMAKINGMODULE_H
#define INVPORTFOLIOMAKINGMODULE_H

#include <QMainWindow>

namespace Ui {
class InvPortfolioMakingModule;
}

class InvPortfolioMakingModule : public QMainWindow
{
    Q_OBJECT

public:
    explicit InvPortfolioMakingModule(QWidget *parent = 0);
    ~InvPortfolioMakingModule();

public slots:
    void toExactPortfMakingPushButtonClicked();

private:
    Ui::InvPortfolioMakingModule *ui;
};

#endif // INVPORTFOLIOMAKINGMODULE_H
