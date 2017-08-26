#include "invportfoliomakingmodule.h"
#include "ui_invportfoliomakingmodule.h"

#include "limitedcapitalinvportfoliomaking.h"
#include "enoughcapitalinvportfoliomaking.h"

InvPortfolioMakingModule::InvPortfolioMakingModule(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InvPortfolioMakingModule)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->invPortfolioMakingLabel->setText("Investment portfolio making module");
    ui->discountRateLabel->setText("Discount rate value");

    ui->enoughCapitalRadioButton->setText("Capital is enough");
    ui->notEnoughCapitalRadioButton->setText("Capital is not enough");
    ui->shortCapitalLimitationTimeRadioButton->setText("Short capital limitation time (about 1 year)");
    ui->longCapitalLimitationTimeRadioButton->setText("Long capital limitation time (more than 1 year)");

    ui->toExactPortfMakingPushButton->setText("Go to the exact investment portfolio making...");
    connect(ui->toExactPortfMakingPushButton, SIGNAL(clicked()),
            this, SLOT(toExactPortfMakingPushButtonClicked()));
}

InvPortfolioMakingModule::~InvPortfolioMakingModule()
{
    delete ui;
}

void InvPortfolioMakingModule::toExactPortfMakingPushButtonClicked()
{
    if (ui->notEnoughCapitalRadioButton->isChecked())
    {
        LimitedCapitalInvPortfolioMaking *lcipm = new LimitedCapitalInvPortfolioMaking(this);
        lcipm->show();
    }

    if (ui->enoughCapitalRadioButton->isChecked())
    {
        EnoughCapitalInvPortfolioMaking *ecipm = new EnoughCapitalInvPortfolioMaking(this);
        ecipm->show();
    }
}

