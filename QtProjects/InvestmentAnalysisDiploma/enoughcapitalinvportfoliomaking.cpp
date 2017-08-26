#include "enoughcapitalinvportfoliomaking.h"
#include "ui_enoughcapitalinvportfoliomaking.h"

#include "invportfoliomakingresults.h"

EnoughCapitalInvPortfolioMaking::EnoughCapitalInvPortfolioMaking(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EnoughCapitalInvPortfolioMaking)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->enoughCapitalInvPortfMakingLabel->setText("Enough capital investment portfolio making");

    ui->stocksGroupBox->setTitle("Stocks");
    ui->stockEmissionCheckBox->setText("Stock emission");
    ui->initialExpensesLabel->setText("Initial expenses");
    ui->dividendValueLabel->setText("Dividend value");
    ui->dividendGrowthRateLabel->setText("Dividend growth rate");
    ui->stockCountLabel->setText("Stock count");

    ui->undistributedProfitGroupBox->setTitle("Undistributed profit");
    ui->undistributedProfitExistanceCheckBox->setText("Existance of the undistributed profit");
    ui->undistributedProfitValueLabel->setText("Undistributed profit value");

    ui->makeInvPortfolioPushButton->setText("Make an investment portfolio...");
    InvPortfolioMakingResults *ipmr = new InvPortfolioMakingResults(this);
    connect(ui->makeInvPortfolioPushButton, SIGNAL(clicked()),
            ipmr, SLOT(show()));
}

EnoughCapitalInvPortfolioMaking::~EnoughCapitalInvPortfolioMaking()
{
    delete ui;
}
