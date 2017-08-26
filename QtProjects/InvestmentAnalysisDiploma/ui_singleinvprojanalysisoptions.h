/********************************************************************************
** Form generated from reading UI file 'singleinvprojanalysisoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEINVPROJANALYSISOPTIONS_H
#define UI_SINGLEINVPROJANALYSISOPTIONS_H

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

class Ui_SingleInvProjAnalysisResults
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *singleInvProjResLabel;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *singleInvProjResTableWidget;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *toInputModulePushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SingleInvProjAnalysisResults)
    {
        if (SingleInvProjAnalysisResults->objectName().isEmpty())
            SingleInvProjAnalysisResults->setObjectName(QStringLiteral("SingleInvProjAnalysisResults"));
        SingleInvProjAnalysisResults->resize(800, 600);
        centralwidget = new QWidget(SingleInvProjAnalysisResults);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(388, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        singleInvProjResLabel = new QLabel(centralwidget);
        singleInvProjResLabel->setObjectName(QStringLiteral("singleInvProjResLabel"));

        gridLayout->addWidget(singleInvProjResLabel, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(330, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        singleInvProjResTableWidget = new QTableWidget(centralwidget);
        singleInvProjResTableWidget->setObjectName(QStringLiteral("singleInvProjResTableWidget"));

        gridLayout->addWidget(singleInvProjResTableWidget, 1, 0, 1, 4);

        horizontalSpacer_3 = new QSpacerItem(610, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 0, 1, 3);

        toInputModulePushButton = new QPushButton(centralwidget);
        toInputModulePushButton->setObjectName(QStringLiteral("toInputModulePushButton"));

        gridLayout->addWidget(toInputModulePushButton, 2, 3, 1, 1);

        SingleInvProjAnalysisResults->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SingleInvProjAnalysisResults);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SingleInvProjAnalysisResults->setMenuBar(menubar);
        statusbar = new QStatusBar(SingleInvProjAnalysisResults);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SingleInvProjAnalysisResults->setStatusBar(statusbar);

        retranslateUi(SingleInvProjAnalysisResults);

        QMetaObject::connectSlotsByName(SingleInvProjAnalysisResults);
    } // setupUi

    void retranslateUi(QMainWindow *SingleInvProjAnalysisResults)
    {
        SingleInvProjAnalysisResults->setWindowTitle(QApplication::translate("SingleInvProjAnalysisResults", "MainWindow", 0));
        singleInvProjResLabel->setText(QApplication::translate("SingleInvProjAnalysisResults", "TextLabel", 0));
        toInputModulePushButton->setText(QApplication::translate("SingleInvProjAnalysisResults", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class SingleInvProjAnalysisResults: public Ui_SingleInvProjAnalysisResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEINVPROJANALYSISOPTIONS_H
