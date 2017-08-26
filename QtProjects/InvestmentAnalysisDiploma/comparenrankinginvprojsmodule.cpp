#include "comparenrankinginvprojsmodule.h"
#include "ui_comparenrankinginvprojsmodule.h"
#include "comparenrankinginvprojsresults.h"

#include <QMessageBox>

CompareNrankingInvProjsModule::CompareNrankingInvProjsModule(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompareNrankingInvProjsModule)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");

    ui->discountRateLabel->setText("Discount rate value");

    ui->consideringEconEfficKoeffsGroupBox->setTitle("Considering economical efficiency koefficients");
    ui->piCheckBox->setText("Profitability index (PI)");
    ui->npvCheckBox->setText("Net present value (NPV)");
    ui->irrCheckBox->setText("Internal rate of return (IRR)");
    ui->dppCheckBox->setText("Discounted payback period (DPP)");

    ui->differentInvProjsLifeTimeRankMethodChoiceGroupBox->setTitle("Choosing the ranking method in case of "
                                                                    "different investment projects life time");
    ui->chainRepeatMethodCheckBox->setText("Chain repeat method");
    ui->equalAnnuitetMethodCheckBox->setText("An equal annuitet method");
    ui->salesMethodCheckBox->setText("Sales method");

    ui->investmentRisksGroupBox->setTitle("Investment risks analysis");
    ui->investmentRisksCheckBox->setText("Investment risks analysis");
    ui->sensitivityAnalysisCheckBox->setText("Sensetivity analysis");
    ui->sensetivityAnalysisFactorsListLabel->setText("Sensetivity analysis factors list");
    ui->sensitivityAnalysisIntervalLabel->setText("Sensetivity interval");
    ui->bepCheckBox->setText("Break-even point (BEP)");
    ui->scenarioAnalysisPushButton->setText("Scenario analysis...");
    ui->monteKarloAnalysisPushButton->setText("Monte-Karlo analysis...");

    ui->rankingCriterionsWeightsCalculatingGroupBox->setTitle("Ranking criterions' weights calculating");
    ui->estimatedRepaymentTimeLabel->setText("Estimated repayment time, years:");
    ui->estimatedInvestmentValueLabel->setText("Estimated investment value, thousands:");
    ui->estimatedInvCycleLabel->setText("Estimated investment cycle, years:");
    ui->estimatedProductionVolumeLabel->setText("Estimated production volume, thousands:");

    ui->compareNrankingInvProjsPushButton->setText("Compare and rank investment projects...");

    connect(ui->investmentRisksCheckBox, SIGNAL(clicked()),
            this, SLOT(investmentRisksAnalysing()));

    CompareNrankingInvProjsResults *cripr = new CompareNrankingInvProjsResults;
    connect(ui->compareNrankingInvProjsPushButton, SIGNAL(clicked()),
            cripr, SLOT(show()));
}

CompareNrankingInvProjsModule::~CompareNrankingInvProjsModule()
{
    delete ui;
}

void CompareNrankingInvProjsModule::investmentRisksAnalysing()
{
    connect(ui->sensitivityAnalysisCheckBox, SIGNAL(clicked()),
            this, SLOT(sensetivityRiskAnalysing()));

    connect(ui->bepCheckBox, SIGNAL(clicked()),
            this, SLOT(bepAnalysing()));

    QMessageBox *sensitivityAnalysisMessageBox = new QMessageBox;
    sensitivityAnalysisMessageBox->setIcon(QMessageBox::Information);
    sensitivityAnalysisMessageBox->setWindowTitle("Scenario risks analysis");
    sensitivityAnalysisMessageBox->setText("To be realized...");
    sensitivityAnalysisMessageBox->setStandardButtons(QMessageBox::Ok);

    connect(ui->scenarioAnalysisPushButton, SIGNAL(clicked()),
            sensitivityAnalysisMessageBox, SLOT(open()));

    QMessageBox *monteKarloAnalysisMessageBox = new QMessageBox;
    monteKarloAnalysisMessageBox->setIcon(QMessageBox::Information);
    monteKarloAnalysisMessageBox->setWindowTitle("Monte-Karlo risks analysis");
    monteKarloAnalysisMessageBox->setText("To be realized...");
    monteKarloAnalysisMessageBox->setStandardButtons(QMessageBox::Ok);

    connect(ui->monteKarloAnalysisPushButton, SIGNAL(clicked()),
            monteKarloAnalysisMessageBox, SLOT(open()));
}

void CompareNrankingInvProjsModule::sensetivityRiskAnalysing()
{
    // Factors list processing
}

void CompareNrankingInvProjsModule::bepAnalysing()
{
    // _ip.calculateBep(_ip.pcf(), unitSalePrice, unitAverageVariableCosts);
}
