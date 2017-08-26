/********************************************************************************
** Form generated from reading UI file 'comparenrankinginvprojsmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPARENRANKINGINVPROJSMODULE_H
#define UI_COMPARENRANKINGINVPROJSMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CompareNrankingInvProjsModule
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QLabel *discountRateLabel;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *discountRateDoubleSpinBox;
    QGroupBox *consideringEconEfficKoeffsGroupBox;
    QGridLayout *gridLayout;
    QCheckBox *piCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *npvCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *irrCheckBox;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *dppCheckBox;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *differentInvProjsLifeTimeRankMethodChoiceGroupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *chainRepeatMethodCheckBox;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *equalAnnuitetMethodCheckBox;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *salesMethodCheckBox;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *investmentRisksGroupBox;
    QGridLayout *gridLayout_3;
    QCheckBox *investmentRisksCheckBox;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *sensitivityAnalysisCheckBox;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_11;
    QLabel *sensetivityAnalysisFactorsListLabel;
    QSpacerItem *horizontalSpacer_12;
    QTextBrowser *sensetivityAnalysisFactorsListTextBrowser;
    QSpacerItem *horizontalSpacer_13;
    QLabel *sensitivityAnalysisIntervalLabel;
    QSpacerItem *horizontalSpacer_14;
    QDoubleSpinBox *sensetivityAnalysisIntervalDoubleSpinBox;
    QCheckBox *bepCheckBox;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *scenarioAnalysisPushButton;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *monteKarloAnalysisPushButton;
    QSpacerItem *horizontalSpacer_17;
    QGroupBox *rankingCriterionsWeightsCalculatingGroupBox;
    QGridLayout *gridLayout_4;
    QLabel *estimatedRepaymentTimeLabel;
    QSpacerItem *horizontalSpacer_18;
    QDoubleSpinBox *estimatedRepaymentTimeDoubleSpinBox;
    QLabel *estimatedInvestmentValueLabel;
    QSpacerItem *horizontalSpacer_19;
    QDoubleSpinBox *estimatedInvestmentValueDoubleSpinBox;
    QLabel *estimatedInvCycleLabel;
    QSpacerItem *horizontalSpacer_20;
    QDoubleSpinBox *estimatedInvCycleDoubleSpinBox;
    QLabel *estimatedProductionVolumeLabel;
    QSpacerItem *horizontalSpacer_21;
    QSpinBox *estimatedProductionVolumeSpinBox;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *compareNrankingInvProjsPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CompareNrankingInvProjsModule)
    {
        if (CompareNrankingInvProjsModule->objectName().isEmpty())
            CompareNrankingInvProjsModule->setObjectName(QStringLiteral("CompareNrankingInvProjsModule"));
        CompareNrankingInvProjsModule->resize(800, 836);
        centralwidget = new QWidget(CompareNrankingInvProjsModule);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        discountRateLabel = new QLabel(centralwidget);
        discountRateLabel->setObjectName(QStringLiteral("discountRateLabel"));

        gridLayout_5->addWidget(discountRateLabel, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(493, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 1, 1, 3);

        discountRateDoubleSpinBox = new QDoubleSpinBox(centralwidget);
        discountRateDoubleSpinBox->setObjectName(QStringLiteral("discountRateDoubleSpinBox"));

        gridLayout_5->addWidget(discountRateDoubleSpinBox, 0, 4, 1, 1);

        consideringEconEfficKoeffsGroupBox = new QGroupBox(centralwidget);
        consideringEconEfficKoeffsGroupBox->setObjectName(QStringLiteral("consideringEconEfficKoeffsGroupBox"));
        gridLayout = new QGridLayout(consideringEconEfficKoeffsGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        piCheckBox = new QCheckBox(consideringEconEfficKoeffsGroupBox);
        piCheckBox->setObjectName(QStringLiteral("piCheckBox"));

        gridLayout->addWidget(piCheckBox, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        npvCheckBox = new QCheckBox(consideringEconEfficKoeffsGroupBox);
        npvCheckBox->setObjectName(QStringLiteral("npvCheckBox"));

        gridLayout->addWidget(npvCheckBox, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        irrCheckBox = new QCheckBox(consideringEconEfficKoeffsGroupBox);
        irrCheckBox->setObjectName(QStringLiteral("irrCheckBox"));

        gridLayout->addWidget(irrCheckBox, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        dppCheckBox = new QCheckBox(consideringEconEfficKoeffsGroupBox);
        dppCheckBox->setObjectName(QStringLiteral("dppCheckBox"));

        gridLayout->addWidget(dppCheckBox, 3, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 1, 1, 1);


        gridLayout_5->addWidget(consideringEconEfficKoeffsGroupBox, 1, 0, 1, 2);

        differentInvProjsLifeTimeRankMethodChoiceGroupBox = new QGroupBox(centralwidget);
        differentInvProjsLifeTimeRankMethodChoiceGroupBox->setObjectName(QStringLiteral("differentInvProjsLifeTimeRankMethodChoiceGroupBox"));
        gridLayout_2 = new QGridLayout(differentInvProjsLifeTimeRankMethodChoiceGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        chainRepeatMethodCheckBox = new QCheckBox(differentInvProjsLifeTimeRankMethodChoiceGroupBox);
        chainRepeatMethodCheckBox->setObjectName(QStringLiteral("chainRepeatMethodCheckBox"));

        gridLayout_2->addWidget(chainRepeatMethodCheckBox, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(340, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        equalAnnuitetMethodCheckBox = new QCheckBox(differentInvProjsLifeTimeRankMethodChoiceGroupBox);
        equalAnnuitetMethodCheckBox->setObjectName(QStringLiteral("equalAnnuitetMethodCheckBox"));

        gridLayout_2->addWidget(equalAnnuitetMethodCheckBox, 1, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(340, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 1, 1, 1);

        salesMethodCheckBox = new QCheckBox(differentInvProjsLifeTimeRankMethodChoiceGroupBox);
        salesMethodCheckBox->setObjectName(QStringLiteral("salesMethodCheckBox"));

        gridLayout_2->addWidget(salesMethodCheckBox, 2, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(340, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 2, 1, 1, 1);


        gridLayout_5->addWidget(differentInvProjsLifeTimeRankMethodChoiceGroupBox, 1, 2, 1, 3);

        investmentRisksGroupBox = new QGroupBox(centralwidget);
        investmentRisksGroupBox->setObjectName(QStringLiteral("investmentRisksGroupBox"));
        gridLayout_3 = new QGridLayout(investmentRisksGroupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        investmentRisksCheckBox = new QCheckBox(investmentRisksGroupBox);
        investmentRisksCheckBox->setObjectName(QStringLiteral("investmentRisksCheckBox"));

        gridLayout_3->addWidget(investmentRisksCheckBox, 0, 0, 1, 2);

        horizontalSpacer_9 = new QSpacerItem(672, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 0, 2, 1, 5);

        sensitivityAnalysisCheckBox = new QCheckBox(investmentRisksGroupBox);
        sensitivityAnalysisCheckBox->setObjectName(QStringLiteral("sensitivityAnalysisCheckBox"));

        gridLayout_3->addWidget(sensitivityAnalysisCheckBox, 1, 0, 1, 2);

        horizontalSpacer_10 = new QSpacerItem(672, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 1, 2, 1, 5);

        horizontalSpacer_11 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 2, 0, 1, 1);

        sensetivityAnalysisFactorsListLabel = new QLabel(investmentRisksGroupBox);
        sensetivityAnalysisFactorsListLabel->setObjectName(QStringLiteral("sensetivityAnalysisFactorsListLabel"));

        gridLayout_3->addWidget(sensetivityAnalysisFactorsListLabel, 2, 1, 1, 3);

        horizontalSpacer_12 = new QSpacerItem(529, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_12, 2, 4, 1, 1);

        sensetivityAnalysisFactorsListTextBrowser = new QTextBrowser(investmentRisksGroupBox);
        sensetivityAnalysisFactorsListTextBrowser->setObjectName(QStringLiteral("sensetivityAnalysisFactorsListTextBrowser"));

        gridLayout_3->addWidget(sensetivityAnalysisFactorsListTextBrowser, 2, 5, 1, 2);

        horizontalSpacer_13 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_13, 3, 0, 1, 1);

        sensitivityAnalysisIntervalLabel = new QLabel(investmentRisksGroupBox);
        sensitivityAnalysisIntervalLabel->setObjectName(QStringLiteral("sensitivityAnalysisIntervalLabel"));

        gridLayout_3->addWidget(sensitivityAnalysisIntervalLabel, 3, 1, 1, 3);

        horizontalSpacer_14 = new QSpacerItem(578, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_14, 3, 4, 1, 2);

        sensetivityAnalysisIntervalDoubleSpinBox = new QDoubleSpinBox(investmentRisksGroupBox);
        sensetivityAnalysisIntervalDoubleSpinBox->setObjectName(QStringLiteral("sensetivityAnalysisIntervalDoubleSpinBox"));

        gridLayout_3->addWidget(sensetivityAnalysisIntervalDoubleSpinBox, 3, 6, 1, 1);

        bepCheckBox = new QCheckBox(investmentRisksGroupBox);
        bepCheckBox->setObjectName(QStringLiteral("bepCheckBox"));

        gridLayout_3->addWidget(bepCheckBox, 4, 0, 1, 2);

        horizontalSpacer_15 = new QSpacerItem(672, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_15, 4, 2, 1, 5);

        scenarioAnalysisPushButton = new QPushButton(investmentRisksGroupBox);
        scenarioAnalysisPushButton->setObjectName(QStringLiteral("scenarioAnalysisPushButton"));

        gridLayout_3->addWidget(scenarioAnalysisPushButton, 5, 0, 1, 3);

        horizontalSpacer_16 = new QSpacerItem(654, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_16, 5, 3, 1, 4);

        monteKarloAnalysisPushButton = new QPushButton(investmentRisksGroupBox);
        monteKarloAnalysisPushButton->setObjectName(QStringLiteral("monteKarloAnalysisPushButton"));

        gridLayout_3->addWidget(monteKarloAnalysisPushButton, 6, 0, 1, 3);

        horizontalSpacer_17 = new QSpacerItem(654, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_17, 6, 3, 1, 4);


        gridLayout_5->addWidget(investmentRisksGroupBox, 2, 0, 1, 5);

        rankingCriterionsWeightsCalculatingGroupBox = new QGroupBox(centralwidget);
        rankingCriterionsWeightsCalculatingGroupBox->setObjectName(QStringLiteral("rankingCriterionsWeightsCalculatingGroupBox"));
        gridLayout_4 = new QGridLayout(rankingCriterionsWeightsCalculatingGroupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        estimatedRepaymentTimeLabel = new QLabel(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedRepaymentTimeLabel->setObjectName(QStringLiteral("estimatedRepaymentTimeLabel"));

        gridLayout_4->addWidget(estimatedRepaymentTimeLabel, 0, 0, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(648, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_18, 0, 1, 1, 1);

        estimatedRepaymentTimeDoubleSpinBox = new QDoubleSpinBox(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedRepaymentTimeDoubleSpinBox->setObjectName(QStringLiteral("estimatedRepaymentTimeDoubleSpinBox"));

        gridLayout_4->addWidget(estimatedRepaymentTimeDoubleSpinBox, 0, 2, 1, 2);

        estimatedInvestmentValueLabel = new QLabel(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedInvestmentValueLabel->setObjectName(QStringLiteral("estimatedInvestmentValueLabel"));

        gridLayout_4->addWidget(estimatedInvestmentValueLabel, 1, 0, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(648, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_19, 1, 1, 1, 1);

        estimatedInvestmentValueDoubleSpinBox = new QDoubleSpinBox(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedInvestmentValueDoubleSpinBox->setObjectName(QStringLiteral("estimatedInvestmentValueDoubleSpinBox"));

        gridLayout_4->addWidget(estimatedInvestmentValueDoubleSpinBox, 1, 2, 1, 2);

        estimatedInvCycleLabel = new QLabel(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedInvCycleLabel->setObjectName(QStringLiteral("estimatedInvCycleLabel"));

        gridLayout_4->addWidget(estimatedInvCycleLabel, 2, 0, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(648, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_20, 2, 1, 1, 1);

        estimatedInvCycleDoubleSpinBox = new QDoubleSpinBox(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedInvCycleDoubleSpinBox->setObjectName(QStringLiteral("estimatedInvCycleDoubleSpinBox"));

        gridLayout_4->addWidget(estimatedInvCycleDoubleSpinBox, 2, 2, 1, 2);

        estimatedProductionVolumeLabel = new QLabel(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedProductionVolumeLabel->setObjectName(QStringLiteral("estimatedProductionVolumeLabel"));

        gridLayout_4->addWidget(estimatedProductionVolumeLabel, 3, 0, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(664, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_21, 3, 1, 1, 2);

        estimatedProductionVolumeSpinBox = new QSpinBox(rankingCriterionsWeightsCalculatingGroupBox);
        estimatedProductionVolumeSpinBox->setObjectName(QStringLiteral("estimatedProductionVolumeSpinBox"));

        gridLayout_4->addWidget(estimatedProductionVolumeSpinBox, 3, 3, 1, 1);


        gridLayout_5->addWidget(rankingCriterionsWeightsCalculatingGroupBox, 3, 0, 1, 5);

        horizontalSpacer_22 = new QSpacerItem(507, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_22, 4, 0, 1, 3);

        compareNrankingInvProjsPushButton = new QPushButton(centralwidget);
        compareNrankingInvProjsPushButton->setObjectName(QStringLiteral("compareNrankingInvProjsPushButton"));

        gridLayout_5->addWidget(compareNrankingInvProjsPushButton, 4, 3, 1, 2);

        CompareNrankingInvProjsModule->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CompareNrankingInvProjsModule);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        CompareNrankingInvProjsModule->setMenuBar(menubar);
        statusbar = new QStatusBar(CompareNrankingInvProjsModule);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CompareNrankingInvProjsModule->setStatusBar(statusbar);

        retranslateUi(CompareNrankingInvProjsModule);

        QMetaObject::connectSlotsByName(CompareNrankingInvProjsModule);
    } // setupUi

    void retranslateUi(QMainWindow *CompareNrankingInvProjsModule)
    {
        CompareNrankingInvProjsModule->setWindowTitle(QApplication::translate("CompareNrankingInvProjsModule", "MainWindow", 0));
        discountRateLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        consideringEconEfficKoeffsGroupBox->setTitle(QApplication::translate("CompareNrankingInvProjsModule", "GroupBox", 0));
        piCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        npvCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        irrCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        dppCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        differentInvProjsLifeTimeRankMethodChoiceGroupBox->setTitle(QApplication::translate("CompareNrankingInvProjsModule", "GroupBox", 0));
        chainRepeatMethodCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        equalAnnuitetMethodCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        salesMethodCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        investmentRisksGroupBox->setTitle(QApplication::translate("CompareNrankingInvProjsModule", "GroupBox", 0));
        investmentRisksCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        sensitivityAnalysisCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        sensetivityAnalysisFactorsListLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        sensitivityAnalysisIntervalLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        bepCheckBox->setText(QApplication::translate("CompareNrankingInvProjsModule", "CheckBox", 0));
        scenarioAnalysisPushButton->setText(QApplication::translate("CompareNrankingInvProjsModule", "PushButton", 0));
        monteKarloAnalysisPushButton->setText(QApplication::translate("CompareNrankingInvProjsModule", "PushButton", 0));
        rankingCriterionsWeightsCalculatingGroupBox->setTitle(QApplication::translate("CompareNrankingInvProjsModule", "GroupBox", 0));
        estimatedRepaymentTimeLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        estimatedInvestmentValueLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        estimatedInvCycleLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        estimatedProductionVolumeLabel->setText(QApplication::translate("CompareNrankingInvProjsModule", "TextLabel", 0));
        compareNrankingInvProjsPushButton->setText(QApplication::translate("CompareNrankingInvProjsModule", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class CompareNrankingInvProjsModule: public Ui_CompareNrankingInvProjsModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPARENRANKINGINVPROJSMODULE_H
