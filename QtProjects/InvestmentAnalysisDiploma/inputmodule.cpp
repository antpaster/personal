#include "inputmodule.h"
#include "ui_inputmodule.h"

#include "singleinvprojanalysismodule.h"
#include "comparenrankinginvprojsmodule.h"
#include "invportfoliomakingmodule.h"
#include "investmentproject.h"
#include "cashflow.h"

#include <QMessageBox>
#include <QList>
#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>

InputModule::InputModule(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputModule)
{
    ui->setupUi(this);

    this->setWindowTitle("Automatic system of ranking and analysing projects in the investment portfolio");
    ui->inputDataLabel->setText("Input investment projects' data: ");
    ui->compareInvprojPushButton->setText("Compare the chosen projects");
    ui->makeInvPortfolioPushButton->setText("Make the investment portfolio");

    ui->invProjDataTableWidget->setColumnCount(27);
    ui->invProjDataTableWidget->setRowCount(5);

    QList<QString> *qsl = new QList<QString>;
    qsl->append("Choose the project");
    qsl->append("Analyse current project");
    qsl->append("Project name");
    qsl->append("Project cost");

    qsl->append("1st year profit");
    qsl->append("2nd year profit");
    qsl->append("3rd year profit");
    qsl->append("4th year profit");
    qsl->append("5th year profit");
    qsl->append("6th year profit");
    qsl->append("7th year profit");
    qsl->append("8th year profit");
    qsl->append("9th year profit");
    qsl->append("10th year profit");

    qsl->append("1st year investments");
    qsl->append("2nd year investments");
    qsl->append("3rd year investments");
    qsl->append("4th year investments");
    qsl->append("5th year investments");
    qsl->append("6th year investments");
    qsl->append("7th year investments");
    qsl->append("8th year investments");
    qsl->append("9th year investments");
    qsl->append("10th year investments");

    qsl->append("Investment expenses");
    qsl->append("Credit rate");
    qsl->append("Credit repayment period");
    ui->invProjDataTableWidget->setHorizontalHeaderLabels(*qsl);
    ui->invProjDataTableWidget->resizeColumnsToContents();

    for (int i = 0; i < ui->invProjDataTableWidget->rowCount(); i++)
    {
        QPushButton *analyseButton = new QPushButton("Analyse", ui->invProjDataTableWidget);
        QCheckBox *analyseCheckBox = new QCheckBox(ui->invProjDataTableWidget);

        ui->invProjDataTableWidget->setCellWidget(i, 1, analyseButton);
        analyseButton->show();
        connect(this, SIGNAL(analysePushButtonClick(int)),
                this, SLOT(analysePushButtonClicked(int)));

        ui->invProjDataTableWidget->setCellWidget(i, 0, analyseCheckBox);
        analyseCheckBox->show();
    }

    ui->compareInvprojPushButton->setText("Compare and rank the chosen investment projects");
    CompareNrankingInvProjsModule *cnipm = new CompareNrankingInvProjsModule(this);
    connect(ui->compareInvprojPushButton, SIGNAL(clicked()),
            cnipm, SLOT(show()));

    ui->makeInvPortfolioPushButton->setText("Make the investment portfolio from the chosen investment projects");
    InvPortfolioMakingModule *ipmm = new InvPortfolioMakingModule(this);
    connect(ui->makeInvPortfolioPushButton, SIGNAL(clicked()),
            ipmm, SLOT(show()));

    connect(ui->actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->actionAdd_column_after_selected, SIGNAL(triggered()),
            this, SLOT(addColumn(int)));
    connect(ui->actionRemove_column_after_selected, SIGNAL(triggered()),
            this, SLOT(deleteColumn(int)));
    connect(ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(actionAboutTriggered()));
}

InputModule::~InputModule()
{
    delete ui;
}

void InputModule::actionAboutTriggered()
{
    QMessageBox *aboutMessageBox = new QMessageBox;
    aboutMessageBox->setIcon(QMessageBox::Information);
    aboutMessageBox->setWindowTitle("About the program");
    aboutMessageBox->setText("Bla-bla-bla");
    aboutMessageBox->setStandardButtons(QMessageBox::Ok);
    aboutMessageBox->show();
}

void InputModule::analysePushButtonClicked(int row)
{
    InvestmentProject *ip = new InvestmentProject;
    ip->setInvProjName(ui->invProjDataTableWidget->item(row, 2)->text());
    ip->setInvProjPrice(ui->invProjDataTableWidget->item(row, 3)->text().toDouble());

    CashFlow *cf = new CashFlow;
    QList<CashFlow> *cfl = new QList<CashFlow>;
    for (int i = 0; i < 10; i++)
    {
        cf->setProfit(ui->invProjDataTableWidget->item(row, 4 + i)->text().toDouble());
        cf->setExpense(ui->invProjDataTableWidget->item(row, 14 + i)->text().toDouble());
        cfl->append(*cf);
    }
    ip->setPcf(cfl);

    // Append inv proj record to db

    SingleInvProjAnalysisModule *sipam = new SingleInvProjAnalysisModule;
    // Getting data about the inv proj from db in constructor
    // SingleInvProjAnalysisModule(InvestmentProject *ip) - constructor
    sipam->show();

    emit analysePushButtonClick(row);
}
