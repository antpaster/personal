#include "limitedcapitalinvportfoliomaking.h"
#include "ui_limitedcapitalinvportfoliomaking.h"

#include "invportfoliomakingresults.h"

LimitedCapitalInvPortfolioMaking::LimitedCapitalInvPortfolioMaking(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LimitedCapitalInvPortfolioMaking)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->limitedCapitalInvPortfolioMakingLabel->setText("Limited capital investment portfolio making");

    ui->capitalLimitationValueLabel->setText("Capital limitation value");
    ui->sensetivityIntervalLabel->setText("Sensetivity interval (for long capital limitation time)");

    ui->makeInvPortfolioPushButton->setText("Make an investment portfolio...");
    InvPortfolioMakingResults *ipmr = new InvPortfolioMakingResults(this);
    connect(ui->makeInvPortfolioPushButton, SIGNAL(clicked()),
            ipmr, SLOT(show()));
}

LimitedCapitalInvPortfolioMaking::~LimitedCapitalInvPortfolioMaking()
{
    delete ui;
}
