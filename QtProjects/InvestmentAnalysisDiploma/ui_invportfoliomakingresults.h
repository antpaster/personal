/********************************************************************************
** Form generated from reading UI file 'invportfoliomakingresults.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVPORTFOLIOMAKINGRESULTS_H
#define UI_INVPORTFOLIOMAKINGRESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvPortfolioMakingResults
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *invPortfMakingResultsLabel;
    QSpacerItem *horizontalSpacer_2;
    QGraphicsView *graphicsView;
    QTableWidget *resultsTableWidget;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *backToInputDataPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InvPortfolioMakingResults)
    {
        if (InvPortfolioMakingResults->objectName().isEmpty())
            InvPortfolioMakingResults->setObjectName(QStringLiteral("InvPortfolioMakingResults"));
        InvPortfolioMakingResults->resize(800, 600);
        centralwidget = new QWidget(InvPortfolioMakingResults);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(428, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        invPortfMakingResultsLabel = new QLabel(centralwidget);
        invPortfMakingResultsLabel->setObjectName(QStringLiteral("invPortfMakingResultsLabel"));

        gridLayout->addWidget(invPortfMakingResultsLabel, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(290, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 1, 0, 1, 4);

        resultsTableWidget = new QTableWidget(centralwidget);
        resultsTableWidget->setObjectName(QStringLiteral("resultsTableWidget"));

        gridLayout->addWidget(resultsTableWidget, 2, 0, 1, 4);

        horizontalSpacer_3 = new QSpacerItem(630, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 0, 1, 3);

        backToInputDataPushButton = new QPushButton(centralwidget);
        backToInputDataPushButton->setObjectName(QStringLiteral("backToInputDataPushButton"));

        gridLayout->addWidget(backToInputDataPushButton, 3, 3, 1, 1);

        InvPortfolioMakingResults->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InvPortfolioMakingResults);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        InvPortfolioMakingResults->setMenuBar(menubar);
        statusbar = new QStatusBar(InvPortfolioMakingResults);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        InvPortfolioMakingResults->setStatusBar(statusbar);

        retranslateUi(InvPortfolioMakingResults);

        QMetaObject::connectSlotsByName(InvPortfolioMakingResults);
    } // setupUi

    void retranslateUi(QMainWindow *InvPortfolioMakingResults)
    {
        InvPortfolioMakingResults->setWindowTitle(QApplication::translate("InvPortfolioMakingResults", "MainWindow", 0));
        invPortfMakingResultsLabel->setText(QApplication::translate("InvPortfolioMakingResults", "TextLabel", 0));
        backToInputDataPushButton->setText(QApplication::translate("InvPortfolioMakingResults", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class InvPortfolioMakingResults: public Ui_InvPortfolioMakingResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVPORTFOLIOMAKINGRESULTS_H
