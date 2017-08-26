#ifndef COMPARENRANKINGINVPROJSRESULTS_H
#define COMPARENRANKINGINVPROJSRESULTS_H

#include <QMainWindow>

namespace Ui {
class CompareNrankingInvProjsResults;
}

class CompareNrankingInvProjsResults : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompareNrankingInvProjsResults(QWidget *parent = 0);
    ~CompareNrankingInvProjsResults();

private:
    Ui::CompareNrankingInvProjsResults *ui;
};

#endif // COMPARENRANKINGINVPROJSRESULTS_H
