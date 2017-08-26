#include "singleinvprojanalysismodule.h"
#include "ui_singleinvprojanalysismodule.h"
#include "cashflow.h"
#include "singleinvprojanalysisresults.h"

#include <QMessageBox>

SingleInvProjAnalysisModule::SingleInvProjAnalysisModule(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingleInvProjAnalysisModule)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");

    ui->theoreticalAnalysisGroupBox->setTitle("Theoretical analysis");
    ui->theoreticalAnalysisCheckBox->setText("Theoretical analysis");
    ui->ppCheckBox->setText("Payback period (PP)");
    ui->arrCheckBox->setText("Accounting rate of return (ARR)");
    ui->restCostValueLabel->setText("Rest cost value");

    ui->realAnalysisGroupBox->setTitle("Real analysis");
    ui->discountRateLabel->setText("Discount rate value");
    ui->piCheckBox->setText("Profitability index (PI)");
    ui->npvCheckBox->setText("Net present value (NPV)");
    ui->irrCheckBox->setText("Internal rate of return (IRR)");
    ui->dppCheckBox->setText("Discounted payback period (DPP)");

    ui->invRisksGroupBox->setTitle("Investment risks analysis");
    ui->invRisksCheckBox->setText("Investment risks analysis");
    ui->sensetivityAnalysisCheckBox->setText("Sensetivity analysis");
    ui->sensetivityAnalysisFactorsLabel->setText("Sensetivity analysis factors list");
    ui->sensetivityIntervalLabel->setText("Sensetivity interval");
    ui->bepCheckBox->setText("Break-even point (BEP)");
    ui->scenarioAnalysisPushButton->setText("Scenario analysis...");
    ui->monteKarloAnalysisPushButton->setText("Monte-Karlo analysis...");

    ui->singleInvProjAnalysePushButton->setText("Analyse...");

    connect(ui->invRisksCheckBox, SIGNAL(clicked()),
            this, SLOT(investmentRiskAnalysing()));

    SingleInvProjAnalysisResults *sipar = new SingleInvProjAnalysisResults(this);
    connect(ui->singleInvProjAnalysePushButton, SIGNAL(clicked()),
            sipar, SLOT(show()));
}

SingleInvProjAnalysisModule::~SingleInvProjAnalysisModule()
{
    delete ui;
}

void SingleInvProjAnalysisModule::theoreticalAnalysing()
{
//    if (ui->theoreticalAnalysisCheckBox->isChecked())
//    {
//        _ip.calculateArr(_ip.pcf(), ui->restCostValueDoubleSpinBox->value());
//        _ip.calculatePp(_ip.pcf());
//    }
}

void SingleInvProjAnalysisModule::realAnalysing()
{
//    _ip.calculatePi(_ip.pcf(), ui->discountRateDoubleSpinBox->value());
//    _ip.calculateNpv(_ip.pcf(), ui->discountRateDoubleSpinBox->value());
//    _ip.calculateIrr(_ip.pcf());
//    _ip.calculateDpp(_ip.pcf(), ui->discountRateDoubleSpinBox->value());
}

void SingleInvProjAnalysisModule::investmentRiskAnalysing()
{
    connect(ui->sensetivityAnalysisCheckBox, SIGNAL(clicked()),
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

void SingleInvProjAnalysisModule::sensetivityRiskAnalysing()
{
    // Factors list processing
}

void SingleInvProjAnalysisModule::bepAnalysing()
{
    // _ip.calculateBep(_ip.pcf(), unitSalePrice, unitAverageVariableCosts);
}
