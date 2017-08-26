#ifndef ENOUGHCAPITALINVPORTFOLIOMAKING_H
#define ENOUGHCAPITALINVPORTFOLIOMAKING_H

#include <QMainWindow>

namespace Ui {
class EnoughCapitalInvPortfolioMaking;
}

class EnoughCapitalInvPortfolioMaking : public QMainWindow
{
    Q_OBJECT

public:
    explicit EnoughCapitalInvPortfolioMaking(QWidget *parent = 0);
    ~EnoughCapitalInvPortfolioMaking();

private:
    Ui::EnoughCapitalInvPortfolioMaking *ui;
};

#endif // ENOUGHCAPITALINVPORTFOLIOMAKING_H
