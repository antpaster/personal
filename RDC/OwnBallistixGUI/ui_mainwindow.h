/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCalculate;
    QAction *actionCompare_the_atmospheric_calculations;
    QAction *actionExit;
    QAction *actionCalculate_S8_KL_2nd_stage_activity_time;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGroupBox *shellParamsGroupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_8;
    QLabel *shellNameLabel;
    QComboBox *shellNameComboBox;
    QLabel *separationSpeedValueLabel;
    QLineEdit *separationSpeedValueLineEdit;
    QGridLayout *gridLayout_10;
    QLabel *firstStageCharSpeedValueLabel;
    QLineEdit *firstStageCharSpeedValueLineEdit;
    QLabel *firstStageCompleteParamLabel;
    QLineEdit *firstStageCompleteParamLineEdit;
    QLabel *secondStageCharSpeedValueLabel;
    QLineEdit *secondStageCharSpeedValueLineEdit;
    QLabel *secondStageCompleteParamLabel;
    QLineEdit *secondStageCompleteParamLineEdit;
    QLabel *thirdStageCharSpeedValueLabel;
    QLineEdit *thirdStageCharSpeedValueLineEdit;
    QLabel *thirdStageCompleteParamLabel;
    QLineEdit *thirdStageCompleteParamLineEdit;
    QLabel *userDefinedLastStageCompleteParamLabel;
    QComboBox *userDefinedLastStageCompleteParamComboBox;
    QLabel *userDefinedLastStageCompleteParamValueLabel;
    QLineEdit *userDefinedLastStageCompleteParamValueLineEdit;
    QGroupBox *appParamsGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *appAbsHeightLabel;
    QLineEdit *appAbsHeightLineEdit;
    QLabel *appWayAngleLabel;
    QLineEdit *appWayAngleLineEdit;
    QLabel *appWvalueLabel;
    QLineEdit *appWvalueLineEdit;
    QLabel *appPitchLabel;
    QLineEdit *appPitchLineEdit;
    QLabel *appAttackLabel;
    QLineEdit *appAttackLineEdit;
    QLabel *appVvalueLabel;
    QLineEdit *appVvalueLineEdit;
    QLabel *appRollLabel;
    QLineEdit *appRollLineEdit;
    QLabel *appSlideLabel;
    QLineEdit *appSlideLineEdit;
    QGroupBox *velocitiesInHCSgroupBox;
    QGridLayout *gridLayout;
    QLabel *appWxCoordHCSlabel;
    QLineEdit *appWxCoordHCSlineEdit;
    QLabel *appVxCoordHCSlabel;
    QLineEdit *appVxCoordHCSlineEdit;
    QLabel *UxCoordHCSlabel;
    QLineEdit *UxCoordHCSlineEdit;
    QLabel *appWyCoordHCSlabel;
    QLineEdit *appWyCoordHCSlineEdit;
    QLabel *appVyCoordHCSlabel;
    QLineEdit *appVyCoordHCSlineEdit;
    QLabel *UyCoordHCSlabel;
    QLineEdit *UyCoordHCSlineEdit;
    QLabel *appWzCoordHCSlabel;
    QLineEdit *appWzCoordHCSlineEdit;
    QLabel *appVzCoordHCSlabel;
    QLineEdit *appVzCoordHCSlineEdit;
    QLabel *UzCoordHCSlabel;
    QLineEdit *UzCoordHCSlineEdit;
    QGroupBox *initTargetPosHCSgroupBox;
    QGridLayout *gridLayout_6;
    QLabel *initTargetXcoordHCSlabel;
    QLineEdit *initTargetXcoordHCSlineEdit;
    QLabel *initTargetYcoordHCSlabel;
    QLineEdit *initTargetYcoordHCSlineEdit;
    QGroupBox *weaponAnglesICSgroupBox;
    QGridLayout *gridLayout_3;
    QLabel *phiY0label;
    QLineEdit *phiY0lineEdit;
    QLabel *phiZ0label;
    QLineEdit *phiZ0lineEdit;
    QGridLayout *gridLayout_4;
    QLabel *integrSteplabel;
    QLineEdit *integrStepLineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *calculatePushButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(792, 785);
        actionCalculate = new QAction(MainWindow);
        actionCalculate->setObjectName(QStringLiteral("actionCalculate"));
        actionCompare_the_atmospheric_calculations = new QAction(MainWindow);
        actionCompare_the_atmospheric_calculations->setObjectName(QStringLiteral("actionCompare_the_atmospheric_calculations"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCalculate_S8_KL_2nd_stage_activity_time = new QAction(MainWindow);
        actionCalculate_S8_KL_2nd_stage_activity_time->setObjectName(QStringLiteral("actionCalculate_S8_KL_2nd_stage_activity_time"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        shellParamsGroupBox = new QGroupBox(centralWidget);
        shellParamsGroupBox->setObjectName(QStringLiteral("shellParamsGroupBox"));
        verticalLayout = new QVBoxLayout(shellParamsGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        shellNameLabel = new QLabel(shellParamsGroupBox);
        shellNameLabel->setObjectName(QStringLiteral("shellNameLabel"));

        gridLayout_8->addWidget(shellNameLabel, 0, 0, 1, 1);

        shellNameComboBox = new QComboBox(shellParamsGroupBox);
        shellNameComboBox->setObjectName(QStringLiteral("shellNameComboBox"));

        gridLayout_8->addWidget(shellNameComboBox, 0, 1, 1, 1);

        separationSpeedValueLabel = new QLabel(shellParamsGroupBox);
        separationSpeedValueLabel->setObjectName(QStringLiteral("separationSpeedValueLabel"));

        gridLayout_8->addWidget(separationSpeedValueLabel, 1, 0, 1, 1);

        separationSpeedValueLineEdit = new QLineEdit(shellParamsGroupBox);
        separationSpeedValueLineEdit->setObjectName(QStringLiteral("separationSpeedValueLineEdit"));

        gridLayout_8->addWidget(separationSpeedValueLineEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_8);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        firstStageCharSpeedValueLabel = new QLabel(shellParamsGroupBox);
        firstStageCharSpeedValueLabel->setObjectName(QStringLiteral("firstStageCharSpeedValueLabel"));

        gridLayout_10->addWidget(firstStageCharSpeedValueLabel, 0, 0, 1, 1);

        firstStageCharSpeedValueLineEdit = new QLineEdit(shellParamsGroupBox);
        firstStageCharSpeedValueLineEdit->setObjectName(QStringLiteral("firstStageCharSpeedValueLineEdit"));

        gridLayout_10->addWidget(firstStageCharSpeedValueLineEdit, 0, 2, 1, 1);

        firstStageCompleteParamLabel = new QLabel(shellParamsGroupBox);
        firstStageCompleteParamLabel->setObjectName(QStringLiteral("firstStageCompleteParamLabel"));

        gridLayout_10->addWidget(firstStageCompleteParamLabel, 0, 3, 1, 1);

        firstStageCompleteParamLineEdit = new QLineEdit(shellParamsGroupBox);
        firstStageCompleteParamLineEdit->setObjectName(QStringLiteral("firstStageCompleteParamLineEdit"));

        gridLayout_10->addWidget(firstStageCompleteParamLineEdit, 0, 4, 1, 1);

        secondStageCharSpeedValueLabel = new QLabel(shellParamsGroupBox);
        secondStageCharSpeedValueLabel->setObjectName(QStringLiteral("secondStageCharSpeedValueLabel"));

        gridLayout_10->addWidget(secondStageCharSpeedValueLabel, 1, 0, 1, 1);

        secondStageCharSpeedValueLineEdit = new QLineEdit(shellParamsGroupBox);
        secondStageCharSpeedValueLineEdit->setObjectName(QStringLiteral("secondStageCharSpeedValueLineEdit"));

        gridLayout_10->addWidget(secondStageCharSpeedValueLineEdit, 1, 2, 1, 1);

        secondStageCompleteParamLabel = new QLabel(shellParamsGroupBox);
        secondStageCompleteParamLabel->setObjectName(QStringLiteral("secondStageCompleteParamLabel"));

        gridLayout_10->addWidget(secondStageCompleteParamLabel, 1, 3, 1, 1);

        secondStageCompleteParamLineEdit = new QLineEdit(shellParamsGroupBox);
        secondStageCompleteParamLineEdit->setObjectName(QStringLiteral("secondStageCompleteParamLineEdit"));

        gridLayout_10->addWidget(secondStageCompleteParamLineEdit, 1, 4, 1, 1);

        thirdStageCharSpeedValueLabel = new QLabel(shellParamsGroupBox);
        thirdStageCharSpeedValueLabel->setObjectName(QStringLiteral("thirdStageCharSpeedValueLabel"));

        gridLayout_10->addWidget(thirdStageCharSpeedValueLabel, 2, 0, 1, 1);

        thirdStageCharSpeedValueLineEdit = new QLineEdit(shellParamsGroupBox);
        thirdStageCharSpeedValueLineEdit->setObjectName(QStringLiteral("thirdStageCharSpeedValueLineEdit"));

        gridLayout_10->addWidget(thirdStageCharSpeedValueLineEdit, 2, 2, 1, 1);

        thirdStageCompleteParamLabel = new QLabel(shellParamsGroupBox);
        thirdStageCompleteParamLabel->setObjectName(QStringLiteral("thirdStageCompleteParamLabel"));

        gridLayout_10->addWidget(thirdStageCompleteParamLabel, 2, 3, 1, 1);

        thirdStageCompleteParamLineEdit = new QLineEdit(shellParamsGroupBox);
        thirdStageCompleteParamLineEdit->setObjectName(QStringLiteral("thirdStageCompleteParamLineEdit"));

        gridLayout_10->addWidget(thirdStageCompleteParamLineEdit, 2, 4, 1, 1);

        userDefinedLastStageCompleteParamLabel = new QLabel(shellParamsGroupBox);
        userDefinedLastStageCompleteParamLabel->setObjectName(QStringLiteral("userDefinedLastStageCompleteParamLabel"));

        gridLayout_10->addWidget(userDefinedLastStageCompleteParamLabel, 3, 0, 1, 1);

        userDefinedLastStageCompleteParamComboBox = new QComboBox(shellParamsGroupBox);
        userDefinedLastStageCompleteParamComboBox->setObjectName(QStringLiteral("userDefinedLastStageCompleteParamComboBox"));

        gridLayout_10->addWidget(userDefinedLastStageCompleteParamComboBox, 3, 1, 1, 2);

        userDefinedLastStageCompleteParamValueLabel = new QLabel(shellParamsGroupBox);
        userDefinedLastStageCompleteParamValueLabel->setObjectName(QStringLiteral("userDefinedLastStageCompleteParamValueLabel"));

        gridLayout_10->addWidget(userDefinedLastStageCompleteParamValueLabel, 3, 3, 1, 1);

        userDefinedLastStageCompleteParamValueLineEdit = new QLineEdit(shellParamsGroupBox);
        userDefinedLastStageCompleteParamValueLineEdit->setObjectName(QStringLiteral("userDefinedLastStageCompleteParamValueLineEdit"));

        gridLayout_10->addWidget(userDefinedLastStageCompleteParamValueLineEdit, 3, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_10);


        gridLayout_5->addWidget(shellParamsGroupBox, 0, 0, 1, 2);

        appParamsGroupBox = new QGroupBox(centralWidget);
        appParamsGroupBox->setObjectName(QStringLiteral("appParamsGroupBox"));
        gridLayout_2 = new QGridLayout(appParamsGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        appAbsHeightLabel = new QLabel(appParamsGroupBox);
        appAbsHeightLabel->setObjectName(QStringLiteral("appAbsHeightLabel"));

        gridLayout_2->addWidget(appAbsHeightLabel, 0, 0, 1, 1);

        appAbsHeightLineEdit = new QLineEdit(appParamsGroupBox);
        appAbsHeightLineEdit->setObjectName(QStringLiteral("appAbsHeightLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(appAbsHeightLineEdit->sizePolicy().hasHeightForWidth());
        appAbsHeightLineEdit->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(appAbsHeightLineEdit, 0, 1, 1, 1);

        appWayAngleLabel = new QLabel(appParamsGroupBox);
        appWayAngleLabel->setObjectName(QStringLiteral("appWayAngleLabel"));

        gridLayout_2->addWidget(appWayAngleLabel, 0, 4, 1, 1);

        appWayAngleLineEdit = new QLineEdit(appParamsGroupBox);
        appWayAngleLineEdit->setObjectName(QStringLiteral("appWayAngleLineEdit"));

        gridLayout_2->addWidget(appWayAngleLineEdit, 0, 5, 1, 1);

        appWvalueLabel = new QLabel(appParamsGroupBox);
        appWvalueLabel->setObjectName(QStringLiteral("appWvalueLabel"));

        gridLayout_2->addWidget(appWvalueLabel, 1, 0, 1, 1);

        appWvalueLineEdit = new QLineEdit(appParamsGroupBox);
        appWvalueLineEdit->setObjectName(QStringLiteral("appWvalueLineEdit"));

        gridLayout_2->addWidget(appWvalueLineEdit, 1, 1, 1, 1);

        appPitchLabel = new QLabel(appParamsGroupBox);
        appPitchLabel->setObjectName(QStringLiteral("appPitchLabel"));

        gridLayout_2->addWidget(appPitchLabel, 1, 2, 1, 1);

        appPitchLineEdit = new QLineEdit(appParamsGroupBox);
        appPitchLineEdit->setObjectName(QStringLiteral("appPitchLineEdit"));

        gridLayout_2->addWidget(appPitchLineEdit, 1, 3, 1, 1);

        appAttackLabel = new QLabel(appParamsGroupBox);
        appAttackLabel->setObjectName(QStringLiteral("appAttackLabel"));

        gridLayout_2->addWidget(appAttackLabel, 1, 4, 1, 1);

        appAttackLineEdit = new QLineEdit(appParamsGroupBox);
        appAttackLineEdit->setObjectName(QStringLiteral("appAttackLineEdit"));

        gridLayout_2->addWidget(appAttackLineEdit, 1, 5, 1, 1);

        appVvalueLabel = new QLabel(appParamsGroupBox);
        appVvalueLabel->setObjectName(QStringLiteral("appVvalueLabel"));

        gridLayout_2->addWidget(appVvalueLabel, 2, 0, 1, 1);

        appVvalueLineEdit = new QLineEdit(appParamsGroupBox);
        appVvalueLineEdit->setObjectName(QStringLiteral("appVvalueLineEdit"));

        gridLayout_2->addWidget(appVvalueLineEdit, 2, 1, 1, 1);

        appRollLabel = new QLabel(appParamsGroupBox);
        appRollLabel->setObjectName(QStringLiteral("appRollLabel"));

        gridLayout_2->addWidget(appRollLabel, 2, 2, 1, 1);

        appRollLineEdit = new QLineEdit(appParamsGroupBox);
        appRollLineEdit->setObjectName(QStringLiteral("appRollLineEdit"));

        gridLayout_2->addWidget(appRollLineEdit, 2, 3, 1, 1);

        appSlideLabel = new QLabel(appParamsGroupBox);
        appSlideLabel->setObjectName(QStringLiteral("appSlideLabel"));

        gridLayout_2->addWidget(appSlideLabel, 2, 4, 1, 1);

        appSlideLineEdit = new QLineEdit(appParamsGroupBox);
        appSlideLineEdit->setObjectName(QStringLiteral("appSlideLineEdit"));

        gridLayout_2->addWidget(appSlideLineEdit, 2, 5, 1, 1);


        gridLayout_5->addWidget(appParamsGroupBox, 1, 0, 1, 2);

        velocitiesInHCSgroupBox = new QGroupBox(centralWidget);
        velocitiesInHCSgroupBox->setObjectName(QStringLiteral("velocitiesInHCSgroupBox"));
        gridLayout = new QGridLayout(velocitiesInHCSgroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        appWxCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        appWxCoordHCSlabel->setObjectName(QStringLiteral("appWxCoordHCSlabel"));

        gridLayout->addWidget(appWxCoordHCSlabel, 0, 0, 1, 1);

        appWxCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        appWxCoordHCSlineEdit->setObjectName(QStringLiteral("appWxCoordHCSlineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(appWxCoordHCSlineEdit->sizePolicy().hasHeightForWidth());
        appWxCoordHCSlineEdit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(appWxCoordHCSlineEdit, 0, 1, 1, 1);

        appVxCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        appVxCoordHCSlabel->setObjectName(QStringLiteral("appVxCoordHCSlabel"));

        gridLayout->addWidget(appVxCoordHCSlabel, 0, 2, 1, 1);

        appVxCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        appVxCoordHCSlineEdit->setObjectName(QStringLiteral("appVxCoordHCSlineEdit"));

        gridLayout->addWidget(appVxCoordHCSlineEdit, 0, 3, 1, 1);

        UxCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        UxCoordHCSlabel->setObjectName(QStringLiteral("UxCoordHCSlabel"));

        gridLayout->addWidget(UxCoordHCSlabel, 0, 4, 1, 1);

        UxCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        UxCoordHCSlineEdit->setObjectName(QStringLiteral("UxCoordHCSlineEdit"));

        gridLayout->addWidget(UxCoordHCSlineEdit, 0, 5, 2, 1);

        appWyCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        appWyCoordHCSlabel->setObjectName(QStringLiteral("appWyCoordHCSlabel"));

        gridLayout->addWidget(appWyCoordHCSlabel, 1, 0, 2, 1);

        appWyCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        appWyCoordHCSlineEdit->setObjectName(QStringLiteral("appWyCoordHCSlineEdit"));

        gridLayout->addWidget(appWyCoordHCSlineEdit, 1, 1, 2, 1);

        appVyCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        appVyCoordHCSlabel->setObjectName(QStringLiteral("appVyCoordHCSlabel"));

        gridLayout->addWidget(appVyCoordHCSlabel, 2, 2, 1, 1);

        appVyCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        appVyCoordHCSlineEdit->setObjectName(QStringLiteral("appVyCoordHCSlineEdit"));

        gridLayout->addWidget(appVyCoordHCSlineEdit, 2, 3, 1, 1);

        UyCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        UyCoordHCSlabel->setObjectName(QStringLiteral("UyCoordHCSlabel"));

        gridLayout->addWidget(UyCoordHCSlabel, 2, 4, 1, 1);

        UyCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        UyCoordHCSlineEdit->setObjectName(QStringLiteral("UyCoordHCSlineEdit"));

        gridLayout->addWidget(UyCoordHCSlineEdit, 2, 5, 2, 1);

        appWzCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        appWzCoordHCSlabel->setObjectName(QStringLiteral("appWzCoordHCSlabel"));

        gridLayout->addWidget(appWzCoordHCSlabel, 3, 0, 2, 1);

        appWzCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        appWzCoordHCSlineEdit->setObjectName(QStringLiteral("appWzCoordHCSlineEdit"));

        gridLayout->addWidget(appWzCoordHCSlineEdit, 3, 1, 2, 1);

        appVzCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        appVzCoordHCSlabel->setObjectName(QStringLiteral("appVzCoordHCSlabel"));

        gridLayout->addWidget(appVzCoordHCSlabel, 4, 2, 1, 1);

        appVzCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        appVzCoordHCSlineEdit->setObjectName(QStringLiteral("appVzCoordHCSlineEdit"));

        gridLayout->addWidget(appVzCoordHCSlineEdit, 4, 3, 1, 1);

        UzCoordHCSlabel = new QLabel(velocitiesInHCSgroupBox);
        UzCoordHCSlabel->setObjectName(QStringLiteral("UzCoordHCSlabel"));

        gridLayout->addWidget(UzCoordHCSlabel, 4, 4, 1, 1);

        UzCoordHCSlineEdit = new QLineEdit(velocitiesInHCSgroupBox);
        UzCoordHCSlineEdit->setObjectName(QStringLiteral("UzCoordHCSlineEdit"));

        gridLayout->addWidget(UzCoordHCSlineEdit, 4, 5, 1, 1);


        gridLayout_5->addWidget(velocitiesInHCSgroupBox, 2, 0, 1, 2);

        initTargetPosHCSgroupBox = new QGroupBox(centralWidget);
        initTargetPosHCSgroupBox->setObjectName(QStringLiteral("initTargetPosHCSgroupBox"));
        gridLayout_6 = new QGridLayout(initTargetPosHCSgroupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        initTargetXcoordHCSlabel = new QLabel(initTargetPosHCSgroupBox);
        initTargetXcoordHCSlabel->setObjectName(QStringLiteral("initTargetXcoordHCSlabel"));

        gridLayout_6->addWidget(initTargetXcoordHCSlabel, 0, 0, 1, 1);

        initTargetXcoordHCSlineEdit = new QLineEdit(initTargetPosHCSgroupBox);
        initTargetXcoordHCSlineEdit->setObjectName(QStringLiteral("initTargetXcoordHCSlineEdit"));

        gridLayout_6->addWidget(initTargetXcoordHCSlineEdit, 0, 1, 1, 1);

        initTargetYcoordHCSlabel = new QLabel(initTargetPosHCSgroupBox);
        initTargetYcoordHCSlabel->setObjectName(QStringLiteral("initTargetYcoordHCSlabel"));

        gridLayout_6->addWidget(initTargetYcoordHCSlabel, 1, 0, 1, 1);

        initTargetYcoordHCSlineEdit = new QLineEdit(initTargetPosHCSgroupBox);
        initTargetYcoordHCSlineEdit->setObjectName(QStringLiteral("initTargetYcoordHCSlineEdit"));

        gridLayout_6->addWidget(initTargetYcoordHCSlineEdit, 1, 1, 1, 1);


        gridLayout_5->addWidget(initTargetPosHCSgroupBox, 3, 0, 1, 1);

        weaponAnglesICSgroupBox = new QGroupBox(centralWidget);
        weaponAnglesICSgroupBox->setObjectName(QStringLiteral("weaponAnglesICSgroupBox"));
        gridLayout_3 = new QGridLayout(weaponAnglesICSgroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        phiY0label = new QLabel(weaponAnglesICSgroupBox);
        phiY0label->setObjectName(QStringLiteral("phiY0label"));

        gridLayout_3->addWidget(phiY0label, 0, 0, 1, 1);

        phiY0lineEdit = new QLineEdit(weaponAnglesICSgroupBox);
        phiY0lineEdit->setObjectName(QStringLiteral("phiY0lineEdit"));

        gridLayout_3->addWidget(phiY0lineEdit, 0, 1, 1, 1);

        phiZ0label = new QLabel(weaponAnglesICSgroupBox);
        phiZ0label->setObjectName(QStringLiteral("phiZ0label"));

        gridLayout_3->addWidget(phiZ0label, 1, 0, 1, 1);

        phiZ0lineEdit = new QLineEdit(weaponAnglesICSgroupBox);
        phiZ0lineEdit->setObjectName(QStringLiteral("phiZ0lineEdit"));

        gridLayout_3->addWidget(phiZ0lineEdit, 1, 1, 1, 1);


        gridLayout_5->addWidget(weaponAnglesICSgroupBox, 3, 1, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        integrSteplabel = new QLabel(centralWidget);
        integrSteplabel->setObjectName(QStringLiteral("integrSteplabel"));

        gridLayout_4->addWidget(integrSteplabel, 0, 0, 1, 1);

        integrStepLineEdit = new QLineEdit(centralWidget);
        integrStepLineEdit->setObjectName(QStringLiteral("integrStepLineEdit"));

        gridLayout_4->addWidget(integrStepLineEdit, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(658, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 0, 1, 1);

        calculatePushButton = new QPushButton(centralWidget);
        calculatePushButton->setObjectName(QStringLiteral("calculatePushButton"));

        gridLayout_4->addWidget(calculatePushButton, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 4, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        shellParamsGroupBox->raise();
        appParamsGroupBox->raise();
        initTargetPosHCSgroupBox->raise();
        velocitiesInHCSgroupBox->raise();
        weaponAnglesICSgroupBox->raise();
        integrSteplabel->raise();
        calculatePushButton->raise();
        integrStepLineEdit->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 792, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionCalculate);
        menuFile->addAction(actionCalculate_S8_KL_2nd_stage_activity_time);
        menuFile->addAction(actionCompare_the_atmospheric_calculations);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCalculate->setText(QApplication::translate("MainWindow", "Calculate...", 0));
        actionCompare_the_atmospheric_calculations->setText(QApplication::translate("MainWindow", "Compare the atmospheric calculations...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionCalculate_S8_KL_2nd_stage_activity_time->setText(QApplication::translate("MainWindow", "Calculate S8-KL 2nd stage activity time...", 0));
        shellParamsGroupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        shellNameLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        shellNameComboBox->clear();
        shellNameComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "736 - \320\236\320\244\320\227-2\320\22042-30 \320\227\320\243\320\236\320\244-8 (1-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "37 - \320\244\320\220\320\221-500\320\242 (\320\242\320\220, \320\220\320\242) (1-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "46 - \320\244\320\220\320\221 500 \320\234-54 \321\201 \320\242\320\243 (2-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "381 - \320\240\320\221\320\232-500 \320\241\320\237\320\221\320\255 (2-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "472 - \320\241-8 (2-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "3472 - \320\241-8\320\234 (2-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "999 - \320\241-8\320\232\320\233 (3-\321\201\321\202\321\203\320\277)", 0)
         << QApplication::translate("MainWindow", "3475 - \320\241-8\320\241\320\241 (3-\321\201\321\202\321\203\320\277)", 0)
        );
        separationSpeedValueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        firstStageCharSpeedValueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        firstStageCompleteParamLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        secondStageCharSpeedValueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        secondStageCompleteParamLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        thirdStageCharSpeedValueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        thirdStageCompleteParamLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        userDefinedLastStageCompleteParamLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        userDefinedLastStageCompleteParamComboBox->clear();
        userDefinedLastStageCompleteParamComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "On height", 0)
         << QApplication::translate("MainWindow", "On time", 0)
         << QApplication::translate("MainWindow", "On range", 0)
         << QApplication::translate("MainWindow", "On speed pressure", 0)
         << QApplication::translate("MainWindow", "On trajectory peak", 0)
        );
        userDefinedLastStageCompleteParamValueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appParamsGroupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        appAbsHeightLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appWayAngleLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appWvalueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appPitchLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appAttackLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appVvalueLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appRollLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appSlideLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        velocitiesInHCSgroupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        appWxCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appVxCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        UxCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appWyCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appVyCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        UyCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appWzCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        appVzCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        UzCoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        initTargetPosHCSgroupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        initTargetXcoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        initTargetYcoordHCSlabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        weaponAnglesICSgroupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        phiY0label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        phiZ0label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        integrSteplabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        calculatePushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
