#include "comparenrankinginvprojsresults.h"
#include "ui_comparenrankinginvprojsresults.h"

CompareNrankingInvProjsResults::CompareNrankingInvProjsResults(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompareNrankingInvProjsResults)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->compareNrankingInvProjsLabel->setText("Investment projects comparison and ranking results");
    ui->backToInputModulePushButton->setText("Back to the data input module");

    ui->resultsTableWidget->setColumnCount(7);
    ui->resultsTableWidget->setRowCount(12);

    QList<QString> *qsl = new QList<QString>;
    qsl->append("Comparison criterion");
    qsl->append("Criterion importance weighted koefficient");

    qsl->append("Project 1");
    qsl->append("Project 2");
    qsl->append("Project 3");
    qsl->append("Project 4");
    qsl->append("Project 5");

    ui->resultsTableWidget->setHorizontalHeaderLabels(*qsl);
    ui->resultsTableWidget->resizeColumnsToContents();

    qsl->clear();
    qsl->append("NPV");
    qsl->append("PI");
    qsl->append("IRR");
    qsl->append("DPP");
    qsl->append("Project price");
    qsl->append("BEP");

    qsl->append("Sensetivity parameter 1");
    qsl->append("Sensetivity parameter 2");
    qsl->append("Sensetivity parameter 3");
    qsl->append("Sensetivity parameter 4");
    qsl->append("Sensetivity parameter 5");

    qsl->append("Summary");

    ui->resultsTableWidget->setVerticalHeaderLabels(*qsl);

    connect(ui->backToInputModulePushButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

CompareNrankingInvProjsResults::~CompareNrankingInvProjsResults()
{
    delete ui;
}
