#ifndef SINGLEINVPROJANALYSISMODULE_H
#define SINGLEINVPROJANALYSISMODULE_H

#include "investmentproject.h"

#include <QMainWindow>

namespace Ui {
class SingleInvProjAnalysisModule;
}

class SingleInvProjAnalysisModule : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingleInvProjAnalysisModule(QWidget *parent = 0);
    ~SingleInvProjAnalysisModule();

public slots:
    void theoreticalAnalysing();

    void realAnalysing();

    void investmentRiskAnalysing();

    void sensetivityRiskAnalysing();

    void bepAnalysing();

private:
    Ui::SingleInvProjAnalysisModule *ui;

//    InvestmentProject _ip;
};

#endif // SINGLEINVPROJANALYSISMODULE_H
