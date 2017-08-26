/********************************************************************************
** Form generated from reading UI file 'comparenrankinginvprojsresults.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPARENRANKINGINVPROJSRESULTS_H
#define UI_COMPARENRANKINGINVPROJSRESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_CompareNrankingInvProjsResults
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *compareNrankingInvProjsLabel;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *resultsTableWidget;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *backToInputModulePushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CompareNrankingInvProjsResults)
    {
        if (CompareNrankingInvProjsResults->objectName().isEmpty())
            CompareNrankingInvProjsResults->setObjectName(QStringLiteral("CompareNrankingInvProjsResults"));
        CompareNrankingInvProjsResults->resize(800, 600);
        centralwidget = new QWidget(CompareNrankingInvProjsResults);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(408, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        compareNrankingInvProjsLabel = new QLabel(centralwidget);
        compareNrankingInvProjsLabel->setObjectName(QStringLiteral("compareNrankingInvProjsLabel"));

        gridLayout->addWidget(compareNrankingInvProjsLabel, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(310, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        resultsTableWidget = new QTableWidget(centralwidget);
        resultsTableWidget->setObjectName(QStringLiteral("resultsTableWidget"));

        gridLayout->addWidget(resultsTableWidget, 1, 0, 1, 4);

        horizontalSpacer_3 = new QSpacerItem(620, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 0, 1, 3);

        backToInputModulePushButton = new QPushButton(centralwidget);
        backToInputModulePushButton->setObjectName(QStringLiteral("backToInputModulePushButton"));

        gridLayout->addWidget(backToInputModulePushButton, 2, 3, 1, 1);

        CompareNrankingInvProjsResults->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CompareNrankingInvProjsResults);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        CompareNrankingInvProjsResults->setMenuBar(menubar);
        statusbar = new QStatusBar(CompareNrankingInvProjsResults);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CompareNrankingInvProjsResults->setStatusBar(statusbar);

        retranslateUi(CompareNrankingInvProjsResults);

        QMetaObject::connectSlotsByName(CompareNrankingInvProjsResults);
    } // setupUi

    void retranslateUi(QMainWindow *CompareNrankingInvProjsResults)
    {
        CompareNrankingInvProjsResults->setWindowTitle(QApplication::translate("CompareNrankingInvProjsResults", "MainWindow", 0));
        compareNrankingInvProjsLabel->setText(QApplication::translate("CompareNrankingInvProjsResults", "TextLabel", 0));
        backToInputModulePushButton->setText(QApplication::translate("CompareNrankingInvProjsResults", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class CompareNrankingInvProjsResults: public Ui_CompareNrankingInvProjsResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPARENRANKINGINVPROJSRESULTS_H
