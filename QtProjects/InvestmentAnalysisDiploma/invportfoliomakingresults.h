#ifndef INVPORTFOLIOMAKINGRESULTS_H
#define INVPORTFOLIOMAKINGRESULTS_H

#include <QMainWindow>

namespace Ui {
class InvPortfolioMakingResults;
}

class InvPortfolioMakingResults : public QMainWindow
{
    Q_OBJECT

public:
    explicit InvPortfolioMakingResults(QWidget *parent = 0);
    ~InvPortfolioMakingResults();

private:
    Ui::InvPortfolioMakingResults *ui;
};

#endif // INVPORTFOLIOMAKINGRESULTS_H
