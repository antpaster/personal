/********************************************************************************
** Form generated from reading UI file 'limitedcapitalinvportfoliomaking.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIMITEDCAPITALINVPORTFOLIOMAKING_H
#define UI_LIMITEDCAPITALINVPORTFOLIOMAKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LimitedCapitalInvPortfolioMaking
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *limitedCapitalInvPortfolioMakingLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *capitalLimitationValueLabel;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *capitalLimitationValueDoubleSpinBox;
    QLabel *sensetivityIntervalLabel;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *sensetivityIntervalDoubleSpinBox;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *makeInvPortfolioPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LimitedCapitalInvPortfolioMaking)
    {
        if (LimitedCapitalInvPortfolioMaking->objectName().isEmpty())
            LimitedCapitalInvPortfolioMaking->setObjectName(QStringLiteral("LimitedCapitalInvPortfolioMaking"));
        LimitedCapitalInvPortfolioMaking->resize(800, 169);
        centralwidget = new QWidget(LimitedCapitalInvPortfolioMaking);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(302, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 2);

        limitedCapitalInvPortfolioMakingLabel = new QLabel(centralwidget);
        limitedCapitalInvPortfolioMakingLabel->setObjectName(QStringLiteral("limitedCapitalInvPortfolioMakingLabel"));

        gridLayout->addWidget(limitedCapitalInvPortfolioMakingLabel, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(296, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 2);

        capitalLimitationValueLabel = new QLabel(centralwidget);
        capitalLimitationValueLabel->setObjectName(QStringLiteral("capitalLimitationValueLabel"));

        gridLayout->addWidget(capitalLimitationValueLabel, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(507, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 3);

        capitalLimitationValueDoubleSpinBox = new QDoubleSpinBox(centralwidget);
        capitalLimitationValueDoubleSpinBox->setObjectName(QStringLiteral("capitalLimitationValueDoubleSpinBox"));

        gridLayout->addWidget(capitalLimitationValueDoubleSpinBox, 1, 4, 1, 1);

        sensetivityIntervalLabel = new QLabel(centralwidget);
        sensetivityIntervalLabel->setObjectName(QStringLiteral("sensetivityIntervalLabel"));

        gridLayout->addWidget(sensetivityIntervalLabel, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(507, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 1, 1, 3);

        sensetivityIntervalDoubleSpinBox = new QDoubleSpinBox(centralwidget);
        sensetivityIntervalDoubleSpinBox->setObjectName(QStringLiteral("sensetivityIntervalDoubleSpinBox"));

        gridLayout->addWidget(sensetivityIntervalDoubleSpinBox, 2, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(646, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 4);

        makeInvPortfolioPushButton = new QPushButton(centralwidget);
        makeInvPortfolioPushButton->setObjectName(QStringLiteral("makeInvPortfolioPushButton"));

        gridLayout->addWidget(makeInvPortfolioPushButton, 3, 4, 1, 1);

        LimitedCapitalInvPortfolioMaking->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LimitedCapitalInvPortfolioMaking);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        LimitedCapitalInvPortfolioMaking->setMenuBar(menubar);
        statusbar = new QStatusBar(LimitedCapitalInvPortfolioMaking);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LimitedCapitalInvPortfolioMaking->setStatusBar(statusbar);

        retranslateUi(LimitedCapitalInvPortfolioMaking);

        QMetaObject::connectSlotsByName(LimitedCapitalInvPortfolioMaking);
    } // setupUi

    void retranslateUi(QMainWindow *LimitedCapitalInvPortfolioMaking)
    {
        LimitedCapitalInvPortfolioMaking->setWindowTitle(QApplication::translate("LimitedCapitalInvPortfolioMaking", "MainWindow", 0));
        limitedCapitalInvPortfolioMakingLabel->setText(QApplication::translate("LimitedCapitalInvPortfolioMaking", "TextLabel", 0));
        capitalLimitationValueLabel->setText(QApplication::translate("LimitedCapitalInvPortfolioMaking", "TextLabel", 0));
        sensetivityIntervalLabel->setText(QApplication::translate("LimitedCapitalInvPortfolioMaking", "TextLabel", 0));
        makeInvPortfolioPushButton->setText(QApplication::translate("LimitedCapitalInvPortfolioMaking", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class LimitedCapitalInvPortfolioMaking: public Ui_LimitedCapitalInvPortfolioMaking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIMITEDCAPITALINVPORTFOLIOMAKING_H
