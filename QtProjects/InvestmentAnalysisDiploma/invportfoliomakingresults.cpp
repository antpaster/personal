#include "invportfoliomakingresults.h"
#include "ui_invportfoliomakingresults.h"

InvPortfolioMakingResults::InvPortfolioMakingResults(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InvPortfolioMakingResults)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->invPortfMakingResultsLabel->setText("Investment portfolio making results");
    ui->backToInputDataPushButton->setText("Back to the data input module");

    ui->resultsTableWidget->setColumnCount(9);
    ui->resultsTableWidget->setRowCount(5);

    QList<QString> *qsl = new QList<QString>;
    qsl->append("Project name");
    qsl->append("NPV");
    qsl->append("PI");
    qsl->append("IRR");

    qsl->append("Sensetivity parameter 1");
    qsl->append("Sensetivity parameter 2");
    qsl->append("Sensetivity parameter 3");
    qsl->append("Sensetivity parameter 4");
    qsl->append("Sensetivity parameter 5");

    ui->resultsTableWidget->setHorizontalHeaderLabels(*qsl);
    ui->resultsTableWidget->resizeColumnsToContents();

    connect(ui->backToInputDataPushButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

InvPortfolioMakingResults::~InvPortfolioMakingResults()
{
    delete ui;
}
