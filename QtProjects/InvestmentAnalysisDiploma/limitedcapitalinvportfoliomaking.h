#ifndef LIMITEDCAPITALINVPORTFOLIOMAKING_H
#define LIMITEDCAPITALINVPORTFOLIOMAKING_H

#include <QMainWindow>

namespace Ui {
class LimitedCapitalInvPortfolioMaking;
}

class LimitedCapitalInvPortfolioMaking : public QMainWindow
{
    Q_OBJECT

public:
    explicit LimitedCapitalInvPortfolioMaking(QWidget *parent = 0);
    ~LimitedCapitalInvPortfolioMaking();

private:
    Ui::LimitedCapitalInvPortfolioMaking *ui;
};

#endif // LIMITEDCAPITALINVPORTFOLIOMAKING_H
