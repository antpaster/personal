/********************************************************************************
** Form generated from reading UI file 'singleinvprojanalysismodule.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEINVPROJANALYSISMODULE_H
#define UI_SINGLEINVPROJANALYSISMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleInvProjAnalysisModule
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QGroupBox *theoreticalAnalysisGroupBox;
    QGridLayout *gridLayout;
    QCheckBox *theoreticalAnalysisCheckBox;
    QSpacerItem *horizontalSpacer;
    QCheckBox *ppCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *arrCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *restCostValueLabel;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *restCostValueDoubleSpinBox;
    QGroupBox *realAnalysisGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *discountRateLabel;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *discountRateDoubleSpinBox;
    QCheckBox *piCheckBox;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *npvCheckBox;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *irrCheckBox;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *dppCheckBox;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *invRisksGroupBox;
    QGridLayout *gridLayout_3;
    QCheckBox *invRisksCheckBox;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *sensetivityAnalysisCheckBox;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_12;
    QLabel *sensetivityAnalysisFactorsLabel;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_14;
    QLabel *sensetivityIntervalLabel;
    QSpacerItem *horizontalSpacer_15;
    QDoubleSpinBox *sensetivityIntervaDoubleSpinBox;
    QCheckBox *bepCheckBox;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *scenarioAnalysisPushButton;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *monteKarloAnalysisPushButton;
    QSpacerItem *horizontalSpacer_18;
    QPlainTextEdit *sensetivityAnalysisFactorsPlainTextEdit;
    QFrame *line;
    QSpacerItem *horizontalSpacer_19;
    QPushButton *singleInvProjAnalysePushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SingleInvProjAnalysisModule)
    {
        if (SingleInvProjAnalysisModule->objectName().isEmpty())
            SingleInvProjAnalysisModule->setObjectName(QStringLiteral("SingleInvProjAnalysisModule"));
        SingleInvProjAnalysisModule->resize(800, 600);
        centralwidget = new QWidget(SingleInvProjAnalysisModule);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        theoreticalAnalysisGroupBox = new QGroupBox(centralwidget);
        theoreticalAnalysisGroupBox->setObjectName(QStringLiteral("theoreticalAnalysisGroupBox"));
        gridLayout = new QGridLayout(theoreticalAnalysisGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        theoreticalAnalysisCheckBox = new QCheckBox(theoreticalAnalysisGroupBox);
        theoreticalAnalysisCheckBox->setObjectName(QStringLiteral("theoreticalAnalysisCheckBox"));

        gridLayout->addWidget(theoreticalAnalysisCheckBox, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 2);

        ppCheckBox = new QCheckBox(theoreticalAnalysisGroupBox);
        ppCheckBox->setObjectName(QStringLiteral("ppCheckBox"));

        gridLayout->addWidget(ppCheckBox, 1, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 2);

        arrCheckBox = new QCheckBox(theoreticalAnalysisGroupBox);
        arrCheckBox->setObjectName(QStringLiteral("arrCheckBox"));

        gridLayout->addWidget(arrCheckBox, 2, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 2);

        restCostValueLabel = new QLabel(theoreticalAnalysisGroupBox);
        restCostValueLabel->setObjectName(QStringLiteral("restCostValueLabel"));

        gridLayout->addWidget(restCostValueLabel, 3, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(139, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 1, 1, 2);

        restCostValueDoubleSpinBox = new QDoubleSpinBox(theoreticalAnalysisGroupBox);
        restCostValueDoubleSpinBox->setObjectName(QStringLiteral("restCostValueDoubleSpinBox"));

        gridLayout->addWidget(restCostValueDoubleSpinBox, 3, 3, 1, 1);


        gridLayout_4->addWidget(theoreticalAnalysisGroupBox, 0, 0, 1, 1);

        realAnalysisGroupBox = new QGroupBox(centralwidget);
        realAnalysisGroupBox->setObjectName(QStringLiteral("realAnalysisGroupBox"));
        gridLayout_2 = new QGridLayout(realAnalysisGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        discountRateLabel = new QLabel(realAnalysisGroupBox);
        discountRateLabel->setObjectName(QStringLiteral("discountRateLabel"));

        gridLayout_2->addWidget(discountRateLabel, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 1, 1, 2);

        discountRateDoubleSpinBox = new QDoubleSpinBox(realAnalysisGroupBox);
        discountRateDoubleSpinBox->setObjectName(QStringLiteral("discountRateDoubleSpinBox"));

        gridLayout_2->addWidget(discountRateDoubleSpinBox, 0, 3, 1, 1);

        piCheckBox = new QCheckBox(realAnalysisGroupBox);
        piCheckBox->setObjectName(QStringLiteral("piCheckBox"));

        gridLayout_2->addWidget(piCheckBox, 1, 0, 1, 2);

        horizontalSpacer_6 = new QSpacerItem(217, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 2, 1, 2);

        npvCheckBox = new QCheckBox(realAnalysisGroupBox);
        npvCheckBox->setObjectName(QStringLiteral("npvCheckBox"));

        gridLayout_2->addWidget(npvCheckBox, 2, 0, 1, 2);

        horizontalSpacer_7 = new QSpacerItem(217, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 2, 2, 1, 2);

        irrCheckBox = new QCheckBox(realAnalysisGroupBox);
        irrCheckBox->setObjectName(QStringLiteral("irrCheckBox"));

        gridLayout_2->addWidget(irrCheckBox, 3, 0, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(217, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 3, 2, 1, 2);

        dppCheckBox = new QCheckBox(realAnalysisGroupBox);
        dppCheckBox->setObjectName(QStringLiteral("dppCheckBox"));

        gridLayout_2->addWidget(dppCheckBox, 4, 0, 1, 2);

        horizontalSpacer_9 = new QSpacerItem(217, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 4, 2, 1, 2);


        gridLayout_4->addWidget(realAnalysisGroupBox, 0, 1, 1, 2);

        invRisksGroupBox = new QGroupBox(centralwidget);
        invRisksGroupBox->setObjectName(QStringLiteral("invRisksGroupBox"));
        gridLayout_3 = new QGridLayout(invRisksGroupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        invRisksCheckBox = new QCheckBox(invRisksGroupBox);
        invRisksCheckBox->setObjectName(QStringLiteral("invRisksCheckBox"));

        gridLayout_3->addWidget(invRisksCheckBox, 0, 0, 1, 2);

        horizontalSpacer_10 = new QSpacerItem(545, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 0, 2, 1, 4);

        sensetivityAnalysisCheckBox = new QCheckBox(invRisksGroupBox);
        sensetivityAnalysisCheckBox->setObjectName(QStringLiteral("sensetivityAnalysisCheckBox"));

        gridLayout_3->addWidget(sensetivityAnalysisCheckBox, 1, 0, 1, 2);

        horizontalSpacer_11 = new QSpacerItem(545, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 1, 2, 1, 4);

        horizontalSpacer_12 = new QSpacerItem(179, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_12, 2, 0, 1, 1);

        sensetivityAnalysisFactorsLabel = new QLabel(invRisksGroupBox);
        sensetivityAnalysisFactorsLabel->setObjectName(QStringLiteral("sensetivityAnalysisFactorsLabel"));

        gridLayout_3->addWidget(sensetivityAnalysisFactorsLabel, 2, 1, 1, 2);

        horizontalSpacer_13 = new QSpacerItem(257, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_13, 2, 3, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(179, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_14, 3, 0, 1, 1);

        sensetivityIntervalLabel = new QLabel(invRisksGroupBox);
        sensetivityIntervalLabel->setObjectName(QStringLiteral("sensetivityIntervalLabel"));

        gridLayout_3->addWidget(sensetivityIntervalLabel, 3, 1, 1, 2);

        horizontalSpacer_15 = new QSpacerItem(388, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_15, 3, 3, 1, 2);

        sensetivityIntervaDoubleSpinBox = new QDoubleSpinBox(invRisksGroupBox);
        sensetivityIntervaDoubleSpinBox->setObjectName(QStringLiteral("sensetivityIntervaDoubleSpinBox"));

        gridLayout_3->addWidget(sensetivityIntervaDoubleSpinBox, 3, 5, 1, 1);

        bepCheckBox = new QCheckBox(invRisksGroupBox);
        bepCheckBox->setObjectName(QStringLiteral("bepCheckBox"));

        gridLayout_3->addWidget(bepCheckBox, 4, 0, 1, 2);

        horizontalSpacer_16 = new QSpacerItem(545, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_16, 4, 2, 1, 4);

        scenarioAnalysisPushButton = new QPushButton(invRisksGroupBox);
        scenarioAnalysisPushButton->setObjectName(QStringLiteral("scenarioAnalysisPushButton"));

        gridLayout_3->addWidget(scenarioAnalysisPushButton, 5, 0, 1, 2);

        horizontalSpacer_17 = new QSpacerItem(545, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_17, 5, 2, 1, 4);

        monteKarloAnalysisPushButton = new QPushButton(invRisksGroupBox);
        monteKarloAnalysisPushButton->setObjectName(QStringLiteral("monteKarloAnalysisPushButton"));

        gridLayout_3->addWidget(monteKarloAnalysisPushButton, 6, 0, 1, 2);

        horizontalSpacer_18 = new QSpacerItem(545, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_18, 6, 2, 1, 4);

        sensetivityAnalysisFactorsPlainTextEdit = new QPlainTextEdit(invRisksGroupBox);
        sensetivityAnalysisFactorsPlainTextEdit->setObjectName(QStringLiteral("sensetivityAnalysisFactorsPlainTextEdit"));

        gridLayout_3->addWidget(sensetivityAnalysisFactorsPlainTextEdit, 2, 4, 1, 2);


        gridLayout_4->addWidget(invRisksGroupBox, 1, 0, 1, 3);

        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 2, 0, 1, 3);

        horizontalSpacer_19 = new QSpacerItem(619, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_19, 3, 0, 1, 2);

        singleInvProjAnalysePushButton = new QPushButton(centralwidget);
        singleInvProjAnalysePushButton->setObjectName(QStringLiteral("singleInvProjAnalysePushButton"));

        gridLayout_4->addWidget(singleInvProjAnalysePushButton, 3, 2, 1, 1);

        SingleInvProjAnalysisModule->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SingleInvProjAnalysisModule);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SingleInvProjAnalysisModule->setMenuBar(menubar);
        statusbar = new QStatusBar(SingleInvProjAnalysisModule);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SingleInvProjAnalysisModule->setStatusBar(statusbar);

        retranslateUi(SingleInvProjAnalysisModule);

        QMetaObject::connectSlotsByName(SingleInvProjAnalysisModule);
    } // setupUi

    void retranslateUi(QMainWindow *SingleInvProjAnalysisModule)
    {
        SingleInvProjAnalysisModule->setWindowTitle(QApplication::translate("SingleInvProjAnalysisModule", "MainWindow", 0));
        theoreticalAnalysisGroupBox->setTitle(QApplication::translate("SingleInvProjAnalysisModule", "GroupBox", 0));
        theoreticalAnalysisCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        ppCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        arrCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        restCostValueLabel->setText(QApplication::translate("SingleInvProjAnalysisModule", "TextLabel", 0));
        realAnalysisGroupBox->setTitle(QApplication::translate("SingleInvProjAnalysisModule", "GroupBox", 0));
        discountRateLabel->setText(QApplication::translate("SingleInvProjAnalysisModule", "TextLabel", 0));
        piCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        npvCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        irrCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        dppCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        invRisksGroupBox->setTitle(QApplication::translate("SingleInvProjAnalysisModule", "GroupBox", 0));
        invRisksCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        sensetivityAnalysisCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        sensetivityAnalysisFactorsLabel->setText(QApplication::translate("SingleInvProjAnalysisModule", "TextLabel", 0));
        sensetivityIntervalLabel->setText(QApplication::translate("SingleInvProjAnalysisModule", "TextLabel", 0));
        bepCheckBox->setText(QApplication::translate("SingleInvProjAnalysisModule", "CheckBox", 0));
        scenarioAnalysisPushButton->setText(QApplication::translate("SingleInvProjAnalysisModule", "PushButton", 0));
        monteKarloAnalysisPushButton->setText(QApplication::translate("SingleInvProjAnalysisModule", "PushButton", 0));
        singleInvProjAnalysePushButton->setText(QApplication::translate("SingleInvProjAnalysisModule", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class SingleInvProjAnalysisModule: public Ui_SingleInvProjAnalysisModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEINVPROJANALYSISMODULE_H
