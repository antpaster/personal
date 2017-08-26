#ifndef COMPARENRANKINGINVPROJSMODULE_H
#define COMPARENRANKINGINVPROJSMODULE_H

#include <QMainWindow>

namespace Ui {
class CompareNrankingInvProjsModule;
}

class CompareNrankingInvProjsModule : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompareNrankingInvProjsModule(QWidget *parent = 0);
    ~CompareNrankingInvProjsModule();

public slots:
    void investmentRisksAnalysing();

    void sensetivityRiskAnalysing();

    void bepAnalysing();

private:
    Ui::CompareNrankingInvProjsModule *ui;
};

#endif // COMPARENRANKINGINVPROJSMODULE_H
