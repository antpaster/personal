#include "singleinvprojanalysisresults.h"
#include "ui_singleinvprojanalysisresults.h"

SingleInvProjAnalysisResults::SingleInvProjAnalysisResults(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingleInvProjAnalysisResults)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->singleInvProjResLabel->setText("Single investment project analysis results");
    ui->toInputModulePushButton->setText("Back to the data input module");

    ui->singleInvProjResTableWidget->setColumnCount(14);
    ui->singleInvProjResTableWidget->setRowCount(1);

    QList<QString> *qsl = new QList<QString>;
    qsl->append("Project name");
    qsl->append("Project profitability");
    qsl->append("PP");
    qsl->append("ARR");
    qsl->append("NPV");
    qsl->append("PI");
    qsl->append("IRR");
    qsl->append("DPP");
    qsl->append("BEP");

    qsl->append("Sensetivity parameter 1");
    qsl->append("Sensetivity parameter 2");
    qsl->append("Sensetivity parameter 3");
    qsl->append("Sensetivity parameter 4");
    qsl->append("Sensetivity parameter 5");
    ui->singleInvProjResTableWidget->setHorizontalHeaderLabels(*qsl);
    ui->singleInvProjResTableWidget->resizeColumnsToContents();

    connect(ui->toInputModulePushButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

SingleInvProjAnalysisResults::~SingleInvProjAnalysisResults()
{
    delete ui;
}
