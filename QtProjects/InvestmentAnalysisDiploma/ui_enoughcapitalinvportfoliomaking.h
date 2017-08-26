/********************************************************************************
** Form generated from reading UI file 'enoughcapitalinvportfoliomaking.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENOUGHCAPITALINVPORTFOLIOMAKING_H
#define UI_ENOUGHCAPITALINVPORTFOLIOMAKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnoughCapitalInvPortfolioMaking
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *enoughCapitalInvPortfMakingLabel;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *stocksGroupBox;
    QGridLayout *gridLayout;
    QCheckBox *stockEmissionCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *stockTypeLabel;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *stockTypeComboBox;
    QLabel *initialExpensesLabel;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *initialExpensesDoubleSpinBox;
    QLabel *dividendValueLabel;
    QSpacerItem *horizontalSpacer_6;
    QDoubleSpinBox *dividendValueDoubleSpinBox;
    QLabel *dividendGrowthRateLabel;
    QSpacerItem *horizontalSpacer_7;
    QDoubleSpinBox *dividendGrowthRateDoubleSpinBox;
    QLabel *stockCountLabel;
    QSpacerItem *horizontalSpacer_8;
    QDoubleSpinBox *stockCountDoubleSpinBox;
    QGroupBox *undistributedProfitGroupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *undistributedProfitExistanceCheckBox;
    QSpacerItem *horizontalSpacer_9;
    QLabel *undistributedProfitValueLabel;
    QSpacerItem *horizontalSpacer_10;
    QDoubleSpinBox *undistributedProfitValueDoubleSpinBox;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *makeInvPortfolioPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EnoughCapitalInvPortfolioMaking)
    {
        if (EnoughCapitalInvPortfolioMaking->objectName().isEmpty())
            EnoughCapitalInvPortfolioMaking->setObjectName(QStringLiteral("EnoughCapitalInvPortfolioMaking"));
        EnoughCapitalInvPortfolioMaking->resize(800, 409);
        centralwidget = new QWidget(EnoughCapitalInvPortfolioMaking);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(526, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);

        enoughCapitalInvPortfMakingLabel = new QLabel(centralwidget);
        enoughCapitalInvPortfMakingLabel->setObjectName(QStringLiteral("enoughCapitalInvPortfMakingLabel"));

        gridLayout_3->addWidget(enoughCapitalInvPortfMakingLabel, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(192, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        stocksGroupBox = new QGroupBox(centralwidget);
        stocksGroupBox->setObjectName(QStringLiteral("stocksGroupBox"));
        gridLayout = new QGridLayout(stocksGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stockEmissionCheckBox = new QCheckBox(stocksGroupBox);
        stockEmissionCheckBox->setObjectName(QStringLiteral("stockEmissionCheckBox"));

        gridLayout->addWidget(stockEmissionCheckBox, 0, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(502, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 2);

        stockTypeLabel = new QLabel(stocksGroupBox);
        stockTypeLabel->setObjectName(QStringLiteral("stockTypeLabel"));

        gridLayout->addWidget(stockTypeLabel, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 1, 1, 2);

        stockTypeComboBox = new QComboBox(stocksGroupBox);
        stockTypeComboBox->setObjectName(QStringLiteral("stockTypeComboBox"));

        gridLayout->addWidget(stockTypeComboBox, 1, 3, 1, 1);

        initialExpensesLabel = new QLabel(stocksGroupBox);
        initialExpensesLabel->setObjectName(QStringLiteral("initialExpensesLabel"));

        gridLayout->addWidget(initialExpensesLabel, 2, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 1, 1, 2);

        initialExpensesDoubleSpinBox = new QDoubleSpinBox(stocksGroupBox);
        initialExpensesDoubleSpinBox->setObjectName(QStringLiteral("initialExpensesDoubleSpinBox"));

        gridLayout->addWidget(initialExpensesDoubleSpinBox, 2, 3, 1, 1);

        dividendValueLabel = new QLabel(stocksGroupBox);
        dividendValueLabel->setObjectName(QStringLiteral("dividendValueLabel"));

        gridLayout->addWidget(dividendValueLabel, 3, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 1, 1, 2);

        dividendValueDoubleSpinBox = new QDoubleSpinBox(stocksGroupBox);
        dividendValueDoubleSpinBox->setObjectName(QStringLiteral("dividendValueDoubleSpinBox"));

        gridLayout->addWidget(dividendValueDoubleSpinBox, 3, 3, 1, 1);

        dividendGrowthRateLabel = new QLabel(stocksGroupBox);
        dividendGrowthRateLabel->setObjectName(QStringLiteral("dividendGrowthRateLabel"));

        gridLayout->addWidget(dividendGrowthRateLabel, 4, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 4, 1, 1, 2);

        dividendGrowthRateDoubleSpinBox = new QDoubleSpinBox(stocksGroupBox);
        dividendGrowthRateDoubleSpinBox->setObjectName(QStringLiteral("dividendGrowthRateDoubleSpinBox"));

        gridLayout->addWidget(dividendGrowthRateDoubleSpinBox, 4, 3, 1, 1);

        stockCountLabel = new QLabel(stocksGroupBox);
        stockCountLabel->setObjectName(QStringLiteral("stockCountLabel"));

        gridLayout->addWidget(stockCountLabel, 5, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 5, 1, 1, 2);

        stockCountDoubleSpinBox = new QDoubleSpinBox(stocksGroupBox);
        stockCountDoubleSpinBox->setObjectName(QStringLiteral("stockCountDoubleSpinBox"));

        gridLayout->addWidget(stockCountDoubleSpinBox, 5, 3, 1, 1);


        gridLayout_3->addWidget(stocksGroupBox, 1, 0, 1, 4);

        undistributedProfitGroupBox = new QGroupBox(centralwidget);
        undistributedProfitGroupBox->setObjectName(QStringLiteral("undistributedProfitGroupBox"));
        gridLayout_2 = new QGridLayout(undistributedProfitGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        undistributedProfitExistanceCheckBox = new QCheckBox(undistributedProfitGroupBox);
        undistributedProfitExistanceCheckBox->setObjectName(QStringLiteral("undistributedProfitExistanceCheckBox"));

        gridLayout_2->addWidget(undistributedProfitExistanceCheckBox, 0, 0, 1, 2);

        horizontalSpacer_9 = new QSpacerItem(502, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 2, 1, 2);

        undistributedProfitValueLabel = new QLabel(undistributedProfitGroupBox);
        undistributedProfitValueLabel->setObjectName(QStringLiteral("undistributedProfitValueLabel"));

        gridLayout_2->addWidget(undistributedProfitValueLabel, 1, 0, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 1, 1, 1, 2);

        undistributedProfitValueDoubleSpinBox = new QDoubleSpinBox(undistributedProfitGroupBox);
        undistributedProfitValueDoubleSpinBox->setObjectName(QStringLiteral("undistributedProfitValueDoubleSpinBox"));

        gridLayout_2->addWidget(undistributedProfitValueDoubleSpinBox, 1, 3, 1, 1);


        gridLayout_3->addWidget(undistributedProfitGroupBox, 2, 0, 1, 4);

        horizontalSpacer_11 = new QSpacerItem(679, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 3, 0, 1, 3);

        makeInvPortfolioPushButton = new QPushButton(centralwidget);
        makeInvPortfolioPushButton->setObjectName(QStringLiteral("makeInvPortfolioPushButton"));

        gridLayout_3->addWidget(makeInvPortfolioPushButton, 3, 3, 1, 1);

        EnoughCapitalInvPortfolioMaking->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EnoughCapitalInvPortfolioMaking);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        EnoughCapitalInvPortfolioMaking->setMenuBar(menubar);
        statusbar = new QStatusBar(EnoughCapitalInvPortfolioMaking);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EnoughCapitalInvPortfolioMaking->setStatusBar(statusbar);

        retranslateUi(EnoughCapitalInvPortfolioMaking);

        QMetaObject::connectSlotsByName(EnoughCapitalInvPortfolioMaking);
    } // setupUi

    void retranslateUi(QMainWindow *EnoughCapitalInvPortfolioMaking)
    {
        EnoughCapitalInvPortfolioMaking->setWindowTitle(QApplication::translate("EnoughCapitalInvPortfolioMaking", "MainWindow", 0));
        enoughCapitalInvPortfMakingLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        stocksGroupBox->setTitle(QApplication::translate("EnoughCapitalInvPortfolioMaking", "GroupBox", 0));
        stockEmissionCheckBox->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "CheckBox", 0));
        stockTypeLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        stockTypeComboBox->clear();
        stockTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("EnoughCapitalInvPortfolioMaking", "general", 0)
         << QApplication::translate("EnoughCapitalInvPortfolioMaking", "privileged", 0)
        );
        initialExpensesLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        dividendValueLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        dividendGrowthRateLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        stockCountLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        undistributedProfitGroupBox->setTitle(QApplication::translate("EnoughCapitalInvPortfolioMaking", "GroupBox", 0));
        undistributedProfitExistanceCheckBox->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "CheckBox", 0));
        undistributedProfitValueLabel->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "TextLabel", 0));
        makeInvPortfolioPushButton->setText(QApplication::translate("EnoughCapitalInvPortfolioMaking", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class EnoughCapitalInvPortfolioMaking: public Ui_EnoughCapitalInvPortfolioMaking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENOUGHCAPITALINVPORTFOLIOMAKING_H
