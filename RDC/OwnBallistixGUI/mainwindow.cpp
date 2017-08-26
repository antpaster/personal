#include <math.h>

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QList>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../930mBallist/ballist_pi.h"

#include "../gentypes.h"
#include "ballcalcresults.h"
#include "../OwnVersion/typesnconstants.h"
#include "../OwnVersion/generalcalc.h"
#include "../OwnVersion/atmosph.h"
#include "../OwnVersion/ballarchive.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Basic ballistics");

    this->resize(1050, 744);

//    this->statusBar()->showMessage("UI is working!", 5000);

    /// Labels' captions' assignment

    /// Shell parameters
    ui->shellParamsGroupBox->setTitle("Parameters of the shell for "
        "calculation");
    ui->shellNameLabel->setText("Shell name:");
    ui->separationSpeedValueLabel->setText("Carrier separation speed [m/s]:");
        ui->separationSpeedValueLabel->setEnabled(false);
    /// Characteristic speeds
    ui->firstStageCharSpeedValueLabel->setText("The 1st stage characteristic "
        "speed [m/s]:");
    ui->secondStageCharSpeedValueLabel->setText("The 2nd stage "
        "characteristic speed [m/s]:");
    ui->thirdStageCharSpeedValueLabel->setText("The 3rd stage characteristic "
        "speed [m/s]:");
    ui->firstStageCharSpeedValueLabel->setEnabled(false);
    ui->secondStageCharSpeedValueLabel->setEnabled(false);
    ui->thirdStageCharSpeedValueLabel->setEnabled(false);
    /// Stages' complete parameters
    ui->firstStageCompleteParamLabel->setText("The 1st stage complete "
        "parameter:");
    ui->secondStageCompleteParamLabel->setText("The 2nd stage complete "
        "parameter:");
    ui->thirdStageCompleteParamLabel->setText("The 3rd stage complete "
        "parameter:");
    ui->userDefinedLastStageCompleteParamValueLabel->setText("The last stage "
        "complete parameter value:");
    ui->separationSpeedValueLineEdit->setEnabled(false);
    ui->firstStageCompleteParamLabel->setEnabled(false);
    ui->secondStageCompleteParamLabel->setEnabled(false);
    ui->thirdStageCompleteParamLabel->setEnabled(false);
    ui->userDefinedLastStageCompleteParamLabel->setText("The last stage "
        "complete parameter:");
    ui->userDefinedLastStageCompleteParamLabel->setEnabled(false);
    ui->userDefinedLastStageCompleteParamValueLabel->setEnabled(false);

    /// Apparatus parameters
    ui->appParamsGroupBox->setTitle("Apparatus parameters");
    ui->appAbsHeightLabel->setText("Absolute height [m]:");
    /// Velocities' values
    ui->appWvalueLabel->setText("Way speed [m/s]:");
    ui->appVvalueLabel->setText("True air speed [m/s]:");
    /// Angles' values
    ui->appPitchLabel->setText("Pitch [deg]:");
    ui->appRollLabel->setText("Roll [deg]:");
    ui->appWayAngleLabel->setText("Way angle [deg]:");
    ui->appAttackLabel->setText("Attack [deg]:");
    ui->appSlideLabel->setText("Slide [deg]:");

    /// Velocities in the Horizontal CS
    ui->velocitiesInHCSgroupBox->setTitle("Velocities in HCS [m/s]");
    /// Apparatus way velocity in the Horizontal CS
    ui->appWxCoordHCSlabel->setText("Apparatus way velocity HCS X coordinate:");
    ui->appWyCoordHCSlabel->setText("Apparatus way velocity HCS Y coordinate:");
    ui->appWzCoordHCSlabel->setText("Apparatus way velocity HCS Z coordinate:");
    ui->appWxCoordHCSlabel->setEnabled(false);
    ui->appWyCoordHCSlabel->setEnabled(false);
    ui->appWzCoordHCSlabel->setEnabled(false);
    /// Apparatus air velocity in the Horizontal CS
    ui->appVxCoordHCSlabel->setText("Apparatus air velocity HCS X coordinate:");
    ui->appVyCoordHCSlabel->setText("Apparatus air velocity HCS Y coordinate:");
    ui->appVzCoordHCSlabel->setText("Apparatus air velocity HCS Z coordinate:");
    ui->appVxCoordHCSlabel->setEnabled(false);
    ui->appVyCoordHCSlabel->setEnabled(false);
    ui->appVzCoordHCSlabel->setEnabled(false);
    /// Wind velocity in the Horizontal CS
    ui->UxCoordHCSlabel->setText("Wind velocity HCS X coordinate:");
    ui->UyCoordHCSlabel->setText("Wind velocity HCS Y coordinate:");
    ui->UzCoordHCSlabel->setText("Wind velocity HCS Z coordinate:");
    ui->UxCoordHCSlabel->setEnabled(false);
    ui->UyCoordHCSlabel->setEnabled(false);
    ui->UzCoordHCSlabel->setEnabled(false);

    /// Initial target position in Horizontal CS
    ui->initTargetPosHCSgroupBox->setTitle("Initial target position in HCS "
        "[m]");
    ui->initTargetXcoordHCSlabel->setText("Initial target HCS X coordinate:");
    ui->initTargetYcoordHCSlabel->setText("Initial target HCS Y coordinate:");

    /// Weapon angles in Installed CS
    ui->weaponAnglesICSgroupBox->setTitle("Weapon angles in ICS [deg]");
    ui->phiY0label->setText("PhiY0:");
    ui->phiZ0label->setText("PhiZ0:");

    /// Initial integration step value
    ui->integrSteplabel->setText("Integration step value (negative value sets "
        "its automatic correction during the calculation) [s]:");

    ui->calculatePushButton->setText("Calculate...");


    /// Interface class fields explicit assignment

    /// Shell parameters
    ui->shellNameComboBox->setCurrentIndex(-1);
    /// Characteristic speeds
    ui->firstStageCharSpeedValueLineEdit->setEnabled(false);
    ui->secondStageCharSpeedValueLineEdit->setEnabled(false);
    ui->thirdStageCharSpeedValueLineEdit->setEnabled(false);
    /// Stages' complete parameters
    ui->firstStageCompleteParamLineEdit->setEnabled(false);
    ui->secondStageCompleteParamLineEdit->setEnabled(false);
    ui->thirdStageCompleteParamLineEdit->setEnabled(false);
    ui->userDefinedLastStageCompleteParamComboBox->setCurrentIndex(-1);
    ui->userDefinedLastStageCompleteParamComboBox->setEnabled(false);
    ui->userDefinedLastStageCompleteParamValueLineEdit->setEnabled(false);

    /// Apparatus parameters
    ui->appAbsHeightLineEdit->setText(QString::number(499.75/*1000.0*/));
    /// Velocities' values
    ui->appWvalueLineEdit->setText(QString::number(69.975/*200.0*/));
    ui->appVvalueLineEdit->setText(QString::number(69.996/*200.0*/));
    /// Angles' values
    ui->appPitchLineEdit->setText(QString::number(0.0/*, 'g', 5*/));
    ui->appRollLineEdit->setText(QString::number(0.0));
    ui->appWayAngleLineEdit->setText(QString::number(0.0));
    ui->appAttackLineEdit->setText(QString::number(0.0));
    ui->appSlideLineEdit->setText(QString::number(0.0));

    /// Velocities in the Horizontal CS
    /// Apparatus way velocity in the Horizontal CS
    ui->appWxCoordHCSlineEdit->setEnabled(false);
    ui->appWyCoordHCSlineEdit->setEnabled(false);
    ui->appWzCoordHCSlineEdit->setEnabled(false);

    /// Apparatus air velocity in the Horizontal CS
    ui->appVxCoordHCSlineEdit->setEnabled(false);
    ui->appVyCoordHCSlineEdit->setEnabled(false);
    ui->appVzCoordHCSlineEdit->setEnabled(false);

    /// Wind velocity in the Horizontal CS
    ui->UxCoordHCSlineEdit->setEnabled(false);
    ui->UyCoordHCSlineEdit->setEnabled(false);
    ui->UzCoordHCSlineEdit->setEnabled(false);

    /// Initial target position in the Horizontal CS
    ui->initTargetXcoordHCSlineEdit->setText(QString::number(5000.0));
    ui->initTargetYcoordHCSlineEdit->setText(QString::number(-499.75/*1000.0*/));

    /// Weapon angles in the Installed CS
    ui->phiY0lineEdit->setText(QString::number(2.522/*0.0*/));
    ui->phiZ0lineEdit->setText(QString::number(0.0));

    /// Initial integration step value
    ui->integrStepLineEdit->setText(QString::number(-0.01));

    this->appParamUIassignment();


    /// Menu elements activation
    connect(ui->actionCalculate, SIGNAL(triggered(bool)), this,
        SLOT(checkInputData()));
    connect(ui->actionCalculate_S8_KL_2nd_stage_activity_time,
        SIGNAL(triggered(bool)), this, SLOT(openS8KLadjustResultsDialog()));
    ui->actionCompare_the_atmospheric_calculations->setEnabled(false);
    connect(ui->actionCompare_the_atmospheric_calculations,
        SIGNAL(triggered(bool)), this, SLOT(openAtmosphCalcComparisonDialog()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));

    /// Window UI elements activation
    connect(ui->shellNameComboBox, SIGNAL(currentIndexChanged(int)), this,
        SLOT(chooseShellName()));

    connect(ui->appWvalueLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));
    connect(ui->appVvalueLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));
    connect(ui->appPitchLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));
    connect(ui->appRollLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));
    connect(ui->appWayAngleLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));
    connect(ui->appAttackLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));
    connect(ui->appSlideLineEdit, SIGNAL(editingFinished()), this,
        SLOT(showVelocitiesInHCS()));

    connect(ui->calculatePushButton, SIGNAL(clicked(bool)), this,
        SLOT(checkInputData()));

    _pMyBallist = new TTotalBallData;
    _pBALLIST = new TBALLIST;

//    this->statusBar()->showMessage(QString::number(sizeof(*_pMyBallist)) + " "
//        + QString::number(sizeof(*_pBALLIST)));
    this->statusBar()->showMessage(QString::number(sizeof(*this)));
}

MainWindow::~MainWindow()
{
//    delete _pMyBallist->IntBD.pShellAbsHeightList;
//    delete _pMyBallist->IntBD.pCxList;
//    delete _pMyBallist->IntBD.pMlist;

    delete _pMyBallist;
    delete _pBALLIST;

    delete ui;
}

/// Assigning data for ballistic calculation
void MainWindow::assignBallData(
    TInputBallData *pInpBD
) {
    /// Ballistic structures' fields assignment

    /// Apparatus way velocity in the Normal (Horizontal) CS assignment
    equVect(pInpBD->appWvect, this->_appWvectUI);

    /// Apparatus air velocity in the Normal (Horizontal) CS assignment
    equVect(pInpBD->appVvect, this->_appVvectUI);

    /// Wind velocity in the Normal (Horizontal) CS assignment
    equVect(pInpBD->initUvect, this->_initUvectUI);

    /// Apparatus absolute height assignment
    pInpBD->appAbsHeight = ui->appAbsHeightLineEdit->text().toDouble();

    /// Initial target position in the Horizontal CS assignment
    pInpBD->initTargetPosVect[AXIS_X] =
        ui->initTargetXcoordHCSlineEdit->text().toDouble();
    pInpBD->initTargetPosVect[AXIS_Y] =
        ui->initTargetYcoordHCSlineEdit->text().toDouble();
    pInpBD->initTargetPosVect[AXIS_Z] = 0.0;

    /// Shell assignment
    pInpBD->pSingleStageShell = this->_pSingleStageShellUI;
    pInpBD->pDoubleStageShell = this->_pDoubleStageShellUI;
    pInpBD->pTripleStageShell = this->_pTripleStageShellUI;

    /// The last stage complete condition assignment
    pInpBD->lastStageCompleteCondition = this->_lastStageCompleteConditionUI;
    pInpBD->lastStageCompleteParam = this->_lastStageCompleteParamUI;

    /// Apparatus angles' assignment
    pInpBD->appWayAngle = this->_appWayAngleUI;
    pInpBD->appYaw = this->_appYawUI;
    pInpBD->appPitch = this->_appPitchUI;
    pInpBD->appRoll = this->_appRollUI;
    pInpBD->appAttack = this->_appAttackUI;
    pInpBD->appSlide = this->_appSlideUI;

    /// Weapon angles in the Installed CS assignment
    pInpBD->phiY0 = ui->phiY0lineEdit->text().toDouble() * M_PI / 180.0;
    pInpBD->phiZ0 = ui->phiZ0lineEdit->text().toDouble() * M_PI / 180.0;

    /// Integration step value assignment
    pInpBD->initIntegrStep = ui->integrStepLineEdit->text().toDouble();
}


/*! Метод Формирующий исходные данные для БВ
********************************************************************************
** \return код выполнения операции:
**  - OPER_SUCCESS - успешное завершение операции
**  - OPER_FAILURE - операция не может быть выполнена
*/
TOPER_RESULT MainWindow::ballist_930m_lInputData (
        TBalInputData	*pInputData,	/*!< Адрес входных данных			*/
        TCREW_MEMBER	crewId			/*!< Идентификатор члена экипажа	*/
) {
    //**************************************************************************
    /// 930m ballistics integration
    /// Apparatus absolute height assignment
    pInputData->hAbs = ui->appAbsHeightLineEdit->text().toDouble();
    /// Initial target height in the Horizontal CS assignment
    pInputData->relTrgHh = ui->initTargetYcoordHCSlineEdit->text().toDouble();
    /// Weapon position considering drift correction
    pInputData->dvrGrDelt[AXIS_X] = 0.0;
    pInputData->dvrGrDelt[AXIS_Y] = 0.0;
    pInputData->dvrGrDelt[AXIS_Z] = 0.0;
    /// User complete condition assignment
    pInputData->userCompleteReady = 1;
    pInputData->userCompleteType = ON_HEIGHT;
    pInputData->userCompletePar = pInputData->relTrgHh;

    if (pInputData->relTrgHh >= 0.0) {
        pInputData->userCompleteType = ON_RANGE;
        if (vValue(_pMyBallist->InpBD.initTargetPosVect) > 0.25) {
            pInputData->userCompletePar =
                vValue(_pMyBallist->InpBD.initTargetPosVect);
        }
        else {
            pInputData->userCompleteReady = 0;
        }
    }

    /// Apparatus way velocity in the Normal (Horizontal) CS assignment
    equVect(pInputData->waySpeedHSC, this->_appWvectUI);
    /// Apparatus air velocity value assignment
    pInputData->trueAirspeed = pInputData->indicatedAirspeed =
        ui->appVvalueLineEdit->text().toDouble();
    /// Apparatus air velocity Connected CS coordinates assignment
    equVect(pInputData->airSpeedCSC, this->_appVvectCCS930m);
    /// Wind velocity in the Normal (Horizontal) CS assignment
    equVect(pInputData->windSpeedHSC, this->_initUvectUI);
    /// Air temperature calculation
    pInputData->aerTerm = /*15.0*/0.0/*TfH(pInputData->hAbs) - 273.15*/;
    /// Type of the chosen avia weapon assignment
    pInputData->armControlSystemPower = REGIME_ON;
    if (this->_pSingleStageShellUI) {
        if (this->_pSingleStageShellUI->type == GUN) {
            pInputData->typeOfChosenNasp = BAL_ASP_VPU;
            pInputData->gunType = BAL_GUN_BR; // defined by force
//            pInputData->inpType = BAL_INP_ENUM;
            pInputData->inpType = BAL_INP_CODE;
            pInputData->gunCode = this->_pSingleStageShellUI->code;

            pInputData->narType = BAL_NAR_NOT;
            pInputData->narCode = 0;

            pInputData->bombType = BAL_ABSP_NOT;
            pInputData->bombCode = 0;
        }
        else if (this->_pSingleStageShellUI->type == MISSILE) {
            if (this->_pSingleStageShellUI->calibre == C_8) {
                pInputData->typeOfChosenNasp = BAL_ASP_C_8;
            }
            else if (this->_pSingleStageShellUI->calibre == C_13) {
                pInputData->typeOfChosenNasp = BAL_ASP_C_13;
            }
            pInputData->inpType = BAL_INP_CODE;
            pInputData->narCode = this->_pSingleStageShellUI->code;

            pInputData->gunType = BAL_GUN_SIZE;
            pInputData->gunCode = 0;

            pInputData->bombType = BAL_ABSP_NOT;
            pInputData->bombCode = 0;
        }
        else if ((this->_pSingleStageShellUI->type == BOMB)
            || (this->_pSingleStageShellUI->type == BOMB_ENTER_TIME)) {
            pInputData->typeOfChosenNasp = BAL_ASP_ABSP_AB;
            pInputData->inpType = BAL_INP_CODE;
            pInputData->bombCode = this->_pSingleStageShellUI->code;

            pInputData->gunType = BAL_GUN_SIZE;
            pInputData->gunCode = 0;

            pInputData->narType = BAL_NAR_NOT;
            pInputData->narCode = 0;
        }
    }
    else if (this->_pDoubleStageShellUI) {
/*        if (this->_pDoubleStageShellUI->type == GUN) {
            pInputData->typeOfChosenNasp = BAL_ASP_VPU;
            pInputData->gunType = BAL_GUN_BR; // defined by force
//            pInputData->inpType = BAL_INP_ENUM;
            pInputData->inpType = BAL_INP_CODE;
            pInputData->gunCode = this->_pDoubleStageShellUI->code;

            pInputData->narType = BAL_NAR_NOT;
            pInputData->narCode = 0;

            pInputData->bombType = BAL_ABSP_NOT;
            pInputData->bombCode = 0;
        }
        else*/ if (this->_pDoubleStageShellUI->type == MISSILE) {
            if (this->_pDoubleStageShellUI->calibre == C_8) {
                pInputData->typeOfChosenNasp = BAL_ASP_C_8;
            }
            else if (this->_pDoubleStageShellUI->calibre == C_13) {
                pInputData->typeOfChosenNasp = BAL_ASP_C_13;
            }
            pInputData->inpType = BAL_INP_CODE;
            pInputData->narCode = this->_pDoubleStageShellUI->code;

            pInputData->gunType = BAL_GUN_SIZE;
            pInputData->gunCode = 0;

            pInputData->bombType = BAL_ABSP_NOT;
            pInputData->bombCode = 0;
        }
        else if ((this->_pDoubleStageShellUI->type == BOMB)
            || (this->_pDoubleStageShellUI->type == BOMB_ENTER_TIME)) {
            pInputData->typeOfChosenNasp = BAL_ASP_ABSP_AB;
            pInputData->inpType = BAL_INP_CODE;
            pInputData->bombCode = this->_pDoubleStageShellUI->code;

            pInputData->gunType = BAL_GUN_SIZE;
            pInputData->gunCode = 0;

            pInputData->narType = BAL_NAR_NOT;
            pInputData->narCode = 0;
        }
    }
    else if (this->_pTripleStageShellUI) {
/*        if (this->_pTripleStageShellUI->type == GUN) {
            pInputData->typeOfChosenNasp = BAL_ASP_VPU;
            pInputData->gunType = BAL_GUN_BR; // defined by force
//            pInputData->inpType = BAL_INP_ENUM;
            pInputData->inpType = BAL_INP_CODE;
            pInputData->gunCode = this->_pTripleStageShellUI->code;

            pInputData->narType = BAL_NAR_NOT;
            pInputData->narCode = 0;

            pInputData->bombType = BAL_ABSP_NOT;
            pInputData->bombCode = 0;
        }
        else*/ if (this->_pTripleStageShellUI->type == MISSILE) {
            if (this->_pTripleStageShellUI->calibre == C_8) {
                pInputData->typeOfChosenNasp = BAL_ASP_C_8;
            }
            else if (this->_pTripleStageShellUI->calibre == C_13) {
                pInputData->typeOfChosenNasp = BAL_ASP_C_13;
            }
            pInputData->inpType = BAL_INP_CODE;
            pInputData->narCode = this->_pTripleStageShellUI->code;
            if (pInputData->narCode == 999) {
                /// S-8KL
                pInputData->userCompleteType = ON_TIME;
                pInputData->userCompletePar = 3.94;
            }

            pInputData->gunType = BAL_GUN_SIZE;
            pInputData->gunCode = 0;

            pInputData->bombType = BAL_ABSP_NOT;
            pInputData->bombCode = 0;
        }
        else if ((this->_pTripleStageShellUI->type == BOMB)
            || (this->_pTripleStageShellUI->type == BOMB_ENTER_TIME)) {
            pInputData->typeOfChosenNasp = BAL_ASP_ABSP_AB;
            pInputData->inpType = BAL_INP_CODE;
            pInputData->bombCode = this->_pTripleStageShellUI->code;

            pInputData->gunType = BAL_GUN_SIZE;
            pInputData->gunCode = 0;

            pInputData->narType = BAL_NAR_NOT;
            pInputData->narCode = 0;
        }
    }
    else {
        pInputData->typeOfChosenNasp = BAL_ASP_NOT;
        pInputData->armControlSystemPower = REGIME_OFF;
    }

    /// Weapon unit vectors assignment
    equVect(pInputData->aspEvectCSC, this->_aspEvectCCS930m);
    equVect(pInputData->aspEvectHSC, this->_aspEvectHCS930m);

    _pBALLIST->workMode[crewId] = REGIME_ON;
    _pBALLIST->modification = BALLIST_MODIF_930M/*modification*/;
    _pBALLIST->modifCheck = BALLIST_MODIF_930M/*modification*/;

    return OPER_SUCCESS;
}


/// Getting the calculation results
void MainWindow::getBallCalcResults(
    BallCalcResults *pBCR,
    const TInputBallData *pInpBD,
    const TInternalBallData *pIntBD,
    TOutputBallData *pOutBD
) {
    /// Shell drift vector
    pOutBD->driftVect[AXIS_X] = pIntBD->currDESSV[3];
    pOutBD->driftVect[AXIS_Y] = pIntBD->currDESSV[4] - pInpBD->appAbsHeight;
    pOutBD->driftVect[AXIS_Z] = pIntBD->currDESSV[5];

    /// Impact point angles' values relative to the shell separation point
    double XOZdrift;
    XOZdrift = sqrt(pOutBD->driftVect[AXIS_X] * pOutBD->driftVect[AXIS_X] +
                    pOutBD->driftVect[AXIS_Z] * pOutBD->driftVect[AXIS_Z]);

    pOutBD->impactPointElevationAngle = atan2(pOutBD->driftVect[AXIS_Y],
        XOZdrift);
    pOutBD->impactPointAzimuthAngle = atan2(pOutBD->driftVect[AXIS_Z],
        pOutBD->driftVect[AXIS_X]);

    /// Shell fall time value
    pOutBD->fallTime = pIntBD->currTime;

    /// Shell impact way velocity
    pOutBD->impactVelocityVect[AXIS_X] = pIntBD->currDESSV[0];
    pOutBD->impactVelocityVect[AXIS_Y] = pIntBD->currDESSV[1];
    pOutBD->impactVelocityVect[AXIS_Z] = pIntBD->currDESSV[2];


//    /// Writing output data to file
//    QFile resultsFile("basic_ballCalcResults.txt");
//    if (resultsFile.open(QIODevice::Append | QIODevice::Text)) {
//        QTextStream resultsFileStream(&resultsFile);
//        resultsFileStream << "Initial conditions (appYaw, appPitch, appRoll, "
//            << "phiY, phiZ, ux, uy, uz, appWx, appWy, appWz, appXg, appYg, "
//            << "appZg, targetXg, targetYg, targetZg):\n" << _vYaw << ' '
//            << _vPitch << ' ' << _vRoll << ' ' << _phiY0 << ' ' << _phiZ0 << ' '
//            << _currUHCS[AXIS_X] << ' ' << _currUHCS[AXIS_Y] << ' '
//            << _currUHCS[AXIS_Z] << ' ' << _appWHCS[AXIS_X] << ' '
//            << _appWHCS[AXIS_Y] << ' ' << _appWHCS[AXIS_Z] << ' '
//            << _initAppPosHCS[AXIS_X] << ' ' << _initAppPosHCS[AXIS_Y] << ' '
//            << _initAppPosHCS[AXIS_Z] << ' ' << _initTargetPosHCS[AXIS_X] << ' '
//            << _initTargetPosHCS[AXIS_Y] << ' ' << _initTargetPosHCS[AXIS_Z]
//            << "\nBallistic calculation results (shellVxg, shellVyg, shellVzg, "
//            << "shellXg, shellYg, shellZg, 2ndStageActivityTime, "
//            << "shellFlightTime, stepsNumber, shellIncidenceAngleY):\n"
//            << _DESSVcurrStep[0] << ' ' << _DESSVcurrStep[1] << ' '
//            << _DESSVcurrStep[2] << ' ' << _DESSVcurrStep[3] << ' '
//            << _DESSVcurrStep[4] << ' ' << _DESSVcurrStep[5] << ' '
//            << _pTripleStageShell->stageBallCharact[1].completePar  << ' '
//            << _vtCurr << ' ' << _integrStepCount << ' ' << incidenceAngleY()
//            << "\n\n";
//        resultsFile.close();
//    }


    /// Giving calculation results as a MessageBox
    QMessageBox *pQMB = new QMessageBox(pBCR);
    pQMB->setWindowTitle(pBCR->getShellName() + " calculation results");
    pQMB->setText("Integration is completed.\n\nImpact point elevation "
        "angle " + QString::number(pOutBD->impactPointElevationAngle
        * 180.0 / M_PI) + " deg\nImpact point azimuth angle "
        + QString::number(pOutBD->impactPointAzimuthAngle * 180.0 / M_PI)
        + " deg\nShell fall time " + QString::number(pOutBD->fallTime)
        + " s\nShell drift vector {"
        + QString::number(pOutBD->driftVect[AXIS_X]) + "; "
        + QString::number(pOutBD->driftVect[AXIS_Y]) + "; "
        + QString::number(pOutBD->driftVect[AXIS_Z]) + "} m\nShell impact "
        "way velocity value " + QString::number(vValue(
        pOutBD->impactVelocityVect)) + " m/s\nSlope distance to the "
        "impact point " + QString::number(pOutBD->driftVect[AXIS_Y]
        / sin(pOutBD->impactPointElevationAngle)) + " m\nStep number "
        + QString::number(pIntBD->integrStepCounter)

        + "\n\n930m ballistics results (NAVIG):\nimpactPointHSC {"
        + QString::number(_pBALLIST->output[0].impactPointHSC[AXIS_X]) + "; "
        + QString::number(_pBALLIST->output[0].impactPointHSC[AXIS_Y]) + "; "
        + QString::number(_pBALLIST->output[0].impactPointHSC[AXIS_Z])
        + "} m\ndistance " + QString::number(_pBALLIST->output[0].distance)
        + " m\nfallTime " + QString::number(_pBALLIST->output[0].fallTime)
        + " s"

        + "\n\n930m ballistics results (PILOT):\nimpactPointHSC {"
        + QString::number(_pBALLIST->output[1].impactPointHSC[AXIS_X]) + "; "
        + QString::number(_pBALLIST->output[1].impactPointHSC[AXIS_Y]) + "; "
        + QString::number(_pBALLIST->output[1].impactPointHSC[AXIS_Z])
        + "} m\ndistance " + QString::number(_pBALLIST->output[1].distance)
        + " m\nfallTime " + QString::number(_pBALLIST->output[1].fallTime)
        + " s");
    pQMB->setIcon(QMessageBox::Information);
    pQMB->setStandardButtons(QMessageBox::Ok);

    connect(pBCR, SIGNAL(accepted()), pQMB, SLOT(open()));

    connect(pQMB, SIGNAL(finished(int)), pBCR, SLOT(deleteLater()));
}

double MainWindow::s8_kl_getAdjustParamArg(
    BallCalcResults* pBCR,
    const double adjustParamArg
) {
//    /// 2nd stage activity time adjusting
//    cTripleStageBallArchive.stageBallCharact[1].completePar = secondStageTime;

//    pbcr->ballCalculation();

//    TDVect3 driftVect;
//    driftImpactPointHCS(driftVect);

//    return driftVect[AXIS_Y];


    /// Initial apparatus height adjusting
    ui->appAbsHeightLineEdit->setText(QString::number(adjustParamArg));
    /// Considering target absolute height == 0.0 (sea alt target)
    ui->initTargetYcoordHCSlineEdit->setText(QString::number(-adjustParamArg));

    ballCalcCircle(pBCR);

    /// Shell impact point absolute height
    return _pMyBallist->InpBD.appAbsHeight
        + _pMyBallist->OutBD.driftVect[AXIS_Y];
}

/// Half division method for getting the required launch parameter value
/// (2nd stage activity time for S8-KL missile)
void MainWindow::s8_kl_adjustParamByHalfDivision(
    BallCalcResults* pBCR
) {
//    /// 2nd stage activity time adjusting
//    double intervalBegin = 0.0, intervalEnd = 40.0, intervalCenter, eps = 0.01;
//    int i = 0;
//    TDVect3 initAppPos, initAppW;
//    QMessageBox *pqmb = new QMessageBox;
//    pqmb->setWindowTitle("S8-KL second stage flight time");
//    pqmb->setIcon(QMessageBox::Information);
//    pqmb->setStandardButtons(QMessageBox::Ok);

//    appPosHCS(initAppPos);
//    appWHCS(initAppW);

//    if (s8_kl_getEndCalcShellHeight(pbcr, intervalBegin)
//        * s8_kl_getEndCalcShellHeight(pbcr, intervalEnd) < 0.0) {
//        do {
//            intervalCenter = 0.5 * (intervalBegin + intervalEnd);

//            if (s8_kl_getEndCalcShellHeight(pbcr, intervalBegin)
//                * s8_kl_getEndCalcShellHeight(pbcr, intervalCenter) < 0.0) {
//                intervalEnd = intervalCenter;
//            }
//            else {
//                intervalBegin = intervalCenter;
//            }
//            i++;
//        } while ((intervalEnd - intervalBegin) > eps);

//        pqmb->setText("Result value is " + QString::number(0.5 * (intervalBegin
//            + intervalEnd)) + " s\n\nunder the following conditions:\nInitial "
//            "apparatus height " + QString::number(initAppPos[AXIS_Y])
//            + " m\nInitial apparatus velocity " + QString::number(
//            initAppW[AXIS_X]) + " m/s\nInitial apparatus pitch angle "
//            + QString::number(pitchAngle()) + " rad\nNumber of iterations "
//            + QString::number(i));
//    }
//    else {
//        pqmb->setText("Error: result cannot be reached!");
//    }

//    connect(pbcr, SIGNAL(accepted()), pqmb, SLOT(open()));


    /// Initial apparatus height adjusting
    double intervalBegin = -50000.0, intervalEnd = 50000.0, intervalCenter,
        eps = 1.0;
    int i = 0;
    QMessageBox *pQMB = new QMessageBox(pBCR);
    pQMB->setWindowTitle("Initial apparatus height for S8-KL utilizing");
    pQMB->setIcon(QMessageBox::Information);
    pQMB->setStandardButtons(QMessageBox::Ok);

    if (s8_kl_getAdjustParamArg(pBCR, intervalBegin)
        * s8_kl_getAdjustParamArg(pBCR, intervalEnd) < 0.0) {
        do {
            intervalCenter = 0.5 * (intervalBegin + intervalEnd);

            if (s8_kl_getAdjustParamArg(pBCR, intervalBegin)
                * s8_kl_getAdjustParamArg(pBCR, intervalCenter) < 0.0) {
                intervalEnd = intervalCenter;
            }
            else {
                intervalBegin = intervalCenter;
            }
            i++;
        } while ((intervalEnd - intervalBegin) > eps);

        pQMB->setText("Result value is " + QString::number(0.5 * (intervalBegin
            + intervalEnd)) + " m\n\nunder the following conditions:\n2nd "
            "stage flight time " + QString::number(
            _pMyBallist->InpBD.pTripleStageShell->stageBallCharact[1].completePar)
            + " s\nShell incidence angle Y "
            + QString::number(_pMyBallist->OutBD.impactPointElevationAngle * 180.0
            / M_PI) + " grad\nSlope distance to the impact point "
            + QString::number((_pMyBallist->IntBD.currDESSV[4]
            - _pMyBallist->InpBD.appAbsHeight)
            / sin(_pMyBallist->OutBD.impactPointElevationAngle)) + " m\nInitial "
            "apparatus velocity " + QString::number(
            _pMyBallist->InpBD.appWvect[AXIS_X]) + " m/s\nInitial apparatus "
            "pitch angle " + QString::number(_pMyBallist->InpBD.appPitch)
            + " rad\nNumber of iterations " + QString::number(i));
    }
    else {
        pQMB->setText("Error: result cannot be reached!");
    }

    connect(pBCR, SIGNAL(accepted()), pQMB, SLOT(open()));

    connect(pQMB, SIGNAL(finished(int)), pBCR, SLOT(deleteLater()));
}

/// Whole ballistic calculation circle
void MainWindow::ballCalcCircle(
    BallCalcResults* pBCR
) {
    assignBallData(&_pMyBallist->InpBD);
    ballist_930m_lInputData(&_pBALLIST->input[NAVIG], NAVIG);
    ballist_930m_lInputData(&_pBALLIST->input[PILOT], PILOT);
//    ballist_hInit(BALLIST_MODIF_930M, &/*MainWindow::*/ballist_930m_lInputData);

//    _pBALLIST->state[NAVIG].calcControl.p930mBallDataList->clear();
    ballist_Monitor(QWC);
    pBCR->setP930mBallDataList(
        _pBALLIST->state[NAVIG].calcControl.p930mBallDataList);

    pBCR->ballCalculation(&_pMyBallist->InpBD, &_pMyBallist->IntBD);

    delete _pBALLIST->state[NAVIG].calcControl.p930mBallDataList;
    delete _pBALLIST->state[PILOT].calcControl.p930mBallDataList;

    getBallCalcResults(pBCR, &_pMyBallist->InpBD, &_pMyBallist->IntBD,
        &_pMyBallist->OutBD);

//    if (BALLIST.state[NAVIG].calcControl.pAirRoList) {
//        delete BALLIST.state[NAVIG].calcControl.pAirRoList;
//    }
//    if (BALLIST.state[NAVIG].calcControl.pSoundSpeedInvList) {
//        delete BALLIST.state[NAVIG].calcControl.pSoundSpeedInvList;
//    }
//    if (BALLIST.state[PILOT].calcControl.pAirRoList) {
//        delete BALLIST.state[PILOT].calcControl.pAirRoList;
//    }
//    if (BALLIST.state[PILOT].calcControl.pSoundSpeedInvList) {
//        delete BALLIST.state[PILOT].calcControl.pSoundSpeedInvList;
//    }
}

void MainWindow::appParamUIassignment() {
    /// Apparatus angles' values
    this->_appWayAngleUI = ui->appWayAngleLineEdit->text().toDouble() * M_PI
        / 180.0;
    /// That makes the Normal CS equal to the Horizontal one
    this->_appYawUI = 0.0;
    this->_appPitchUI = ui->appPitchLineEdit->text().toDouble() * M_PI / 180.0;
    this->_appRollUI = ui->appRollLineEdit->text().toDouble() * M_PI / 180.0;
    this->_appAttackUI = ui->appAttackLineEdit->text().toDouble() * M_PI
        / 180.0;
    this->_appSlideUI = ui->appSlideLineEdit->text().toDouble() * M_PI / 180.0;

    /// Apparatus way velocity Trajectory CS coordinates assignment
    this->_appWvectUI[AXIS_X] = ui->appWvalueLineEdit->text().toDouble();
    this->_appWvectUI[AXIS_Y] = 0.0;
    this->_appWvectUI[AXIS_Z] = 0.0;

    /// Apparatus air velocity Speed CS coordinates assignment
    this->_appVvectUI[AXIS_X] = ui->appVvalueLineEdit->text().toDouble();
    this->_appVvectUI[AXIS_Y] = 0.0;
    this->_appVvectUI[AXIS_Z] = 0.0;

    /// Velocities conversion to the Horizontal CS
    TDMatr3 convMatrix;
    /// Apparatus way velocity conversion from the Trajectory CS to the
    /// Normal (Horizontal) one
    speedCStoConnectedCS(this->_appAttackUI - this->_appPitchUI,
        this->_appWayAngleUI, convMatrix);
    csVectConversion(this->_appWvectUI, convMatrix);
    /// Apparatus air velocity conversion from the Speed CS to the Connected
    /// one
    speedCStoConnectedCS(this->_appAttackUI, this->_appSlideUI, convMatrix);
    csVectConversion(this->_appVvectUI, convMatrix);


    equVect(this->_appVvectCCS930m, this->_appVvectUI);

    TDVect3 unitVect = {1.0, 0.0, 0.0};
    equVect(this->_aspEvectCCS930m, unitVect);
    speedCStoConnectedCS(ui->phiY0lineEdit->text().toDouble() * M_PI / 180.0,
        ui->phiZ0lineEdit->text().toDouble() * M_PI / 180.0, convMatrix);
    csVectConversion(this->_aspEvectCCS930m, convMatrix);

    equVect(this->_aspEvectHCS930m, this->_aspEvectCCS930m);
    connectedCStoNormalCS(this->_appYawUI, this->_appPitchUI, this->_appRollUI,
        convMatrix);
    csVectConversion(this->_aspEvectHCS930m, convMatrix);


    /// Apparatus air velocity conversion from the Connected CS to the
    /// Normal (Horizontal) one
    connectedCStoNormalCS(this->_appYawUI, this->_appPitchUI, this->_appRollUI,
        convMatrix);
    csVectConversion(this->_appVvectUI, convMatrix);

    /// Wind velocity in the Normal (Horizontal) CS calculation
    subtract2vect(this->_appWvectUI, this->_appVvectUI, this->_initUvectUI);

    ui->appWxCoordHCSlineEdit->setText(QString::number(
        this->_appWvectUI[AXIS_X]));
    ui->appWyCoordHCSlineEdit->setText(QString::number(
        this->_appWvectUI[AXIS_Y]));
    ui->appWzCoordHCSlineEdit->setText(QString::number(
        this->_appWvectUI[AXIS_Z]));

    ui->appVxCoordHCSlineEdit->setText(QString::number(
        this->_appVvectUI[AXIS_X]));
    ui->appVyCoordHCSlineEdit->setText(QString::number(
        this->_appVvectUI[AXIS_Y]));
    ui->appVzCoordHCSlineEdit->setText(QString::number(
        this->_appVvectUI[AXIS_Z]));

    ui->UxCoordHCSlineEdit->setText(QString::number(
        this->_initUvectUI[AXIS_X]));
    ui->UyCoordHCSlineEdit->setText(QString::number(
        this->_initUvectUI[AXIS_Y]));
    ui->UzCoordHCSlineEdit->setText(QString::number(
        this->_initUvectUI[AXIS_Z]));
}

void MainWindow::showVelocitiesInHCS() {
    if (!ui->appWvalueLineEdit->text().isEmpty()
            && !ui->appVvalueLineEdit->text().isEmpty()
            && !ui->appPitchLineEdit->text().isEmpty()
        && !ui->appRollLineEdit->text().isEmpty()
        && !ui->appWayAngleLineEdit->text().isEmpty()
        && !ui->appAttackLineEdit->text().isEmpty()
        && !ui->appSlideLineEdit->text().isEmpty()) {

        appParamUIassignment();
    }
}

void MainWindow::chooseShellName() {
    ui->actionCalculate_S8_KL_2nd_stage_activity_time->setEnabled(false);

    /// Shell assignment
    this->_pSingleStageShellUI = 0;
    this->_pDoubleStageShellUI = 0;
    this->_pTripleStageShellUI = 0;

    ui->separationSpeedValueLabel->setEnabled(true);
    ui->separationSpeedValueLineEdit->setEnabled(true);

    ui->firstStageCharSpeedValueLabel->setEnabled(true);
    ui->firstStageCharSpeedValueLineEdit->setEnabled(true);
    ui->firstStageCompleteParamLabel->setEnabled(true);
    ui->firstStageCompleteParamLineEdit->setEnabled(true);

    /// ComboBox index accumulators array for retrieving different shells from
    /// the ballistic archive depending on stage number
    int shellNumberAccumulator[2] = {cSingleStageShellNumber,
        cSingleStageShellNumber + cDoubleStageShellNumber};
    if ((ui->shellNameComboBox->currentIndex() >= 0)
        && (ui->shellNameComboBox->currentIndex()
        < shellNumberAccumulator[0])) {
        /// Single stage shell
        this->_pSingleStageShellUI = const_cast<TSingleStageBallCharact*>
            (&cSingleStageBallArchive[
            ui->shellNameComboBox->currentIndex()]);

        ui->separationSpeedValueLineEdit->setText(QString::number(
            this->_pSingleStageShellUI->stageBallCharact.separationSpeed));

        /// The first stage parameters showing
        ui->firstStageCharSpeedValueLineEdit->setText(QString::number(
            this->_pSingleStageShellUI->stageBallCharact.charactSpeed));
        ui->firstStageCompleteParamLabel->setText("Shell destination height "
            "relative to the absolute target's one [m]:");
        ui->firstStageCompleteParamLineEdit->setText(QString::number(
            this->_pSingleStageShellUI->stageBallCharact.completePar));

        /// The second stage parameters clearing
        ui->secondStageCharSpeedValueLabel->setEnabled(false);
        ui->secondStageCharSpeedValueLineEdit->setEnabled(false);
        ui->secondStageCharSpeedValueLineEdit->clear();
        ui->secondStageCompleteParamLabel->setEnabled(false);
        ui->secondStageCompleteParamLabel->setText("The 2nd stage complete "
            "parameter:");
        ui->secondStageCompleteParamLineEdit->setEnabled(false);
        ui->secondStageCompleteParamLineEdit->clear();

        /// The third stage parameters clearing
        ui->thirdStageCharSpeedValueLabel->setEnabled(false);
        ui->thirdStageCharSpeedValueLineEdit->setEnabled(false);
        ui->thirdStageCharSpeedValueLineEdit->clear();
        ui->thirdStageCompleteParamLabel->setEnabled(false);
        ui->thirdStageCompleteParamLabel->setText("The 3rd stage complete "
            "parameter:");
        ui->thirdStageCompleteParamLineEdit->setEnabled(false);
        ui->thirdStageCompleteParamLineEdit->clear();

        /// Setting the last stage complete parameter if the user chooses none
        this->_lastStageCompleteConditionUI =
            this->_pSingleStageShellUI->stageBallCharact.completeType;
        this->_lastStageCompleteParamUI =
            this->_pSingleStageShellUI->stageBallCharact.completePar;
    }
    else if ((ui->shellNameComboBox->currentIndex()
        >= shellNumberAccumulator[0]) && (ui->shellNameComboBox->currentIndex()
        < shellNumberAccumulator[1])) {
        /// Double stage shell
        this->_pDoubleStageShellUI = const_cast<TDoubleStageBallCharact*>
            (&cDoubleStageBallArchive[
            ui->shellNameComboBox->currentIndex() - shellNumberAccumulator[0]]);

        ui->separationSpeedValueLineEdit->setText(QString::number(
            this->_pDoubleStageShellUI->stageBallCharact[0].separationSpeed));

        /// The first stage parameters showing
        ui->firstStageCharSpeedValueLineEdit->setText(QString::number(
            this->_pDoubleStageShellUI->stageBallCharact[0].charactSpeed));
        if (this->_pDoubleStageShellUI->stageBallCharact[0].specialType
            == JET_ENGINE) {
            ui->firstStageCompleteParamLabel->setText("Jet engine activity "
                "duration [s]:");
        }
        else {
            ui->firstStageCompleteParamLabel->setText("The 1st stage activity "
                "duration [s]:");
        }
        ui->firstStageCompleteParamLineEdit->setText(QString::number(
            this->_pDoubleStageShellUI->stageBallCharact[0].completePar));

        /// The second stage parameters showing
        ui->secondStageCharSpeedValueLabel->setEnabled(true);
        ui->secondStageCharSpeedValueLineEdit->setEnabled(true);
        ui->secondStageCharSpeedValueLineEdit->setText(QString::number(
            this->_pDoubleStageShellUI->stageBallCharact[1].charactSpeed));
        ui->secondStageCompleteParamLabel->setEnabled(true);
        ui->secondStageCompleteParamLabel->setText("Shell destination height "
            "relative to the absolute target's one [m]:");
        ui->secondStageCompleteParamLineEdit->setEnabled(true);
        ui->secondStageCompleteParamLineEdit->setText(QString::number(
            this->_pDoubleStageShellUI->stageBallCharact[1].completePar));

        /// The third stage parameters clearing
        ui->thirdStageCharSpeedValueLabel->setEnabled(false);
        ui->thirdStageCharSpeedValueLineEdit->setEnabled(false);
        ui->thirdStageCharSpeedValueLineEdit->clear();
        ui->thirdStageCompleteParamLabel->setEnabled(false);
        ui->thirdStageCompleteParamLabel->setText("The 3rd stage complete "
            "parameter:");
        ui->thirdStageCompleteParamLineEdit->setEnabled(false);
        ui->thirdStageCompleteParamLineEdit->clear();

        /// Setting the last stage complete parameter if the user chooses none
        this->_lastStageCompleteConditionUI =
            this->_pDoubleStageShellUI->stageBallCharact[1].completeType;
        this->_lastStageCompleteParamUI =
            this->_pDoubleStageShellUI->stageBallCharact[1].completePar;
    }
    else if ((ui->shellNameComboBox->currentIndex()
        >= shellNumberAccumulator[1]) && (ui->shellNameComboBox->currentIndex()
        < shellNumberAccumulator[1] + cTripleStageShellNumber)) {
        /// Triple stage shell
        this->_pTripleStageShellUI = //const_cast<TTripleStageBallCharact*>
            (&cTripleStageBallArchive[
            ui->shellNameComboBox->currentIndex() - shellNumberAccumulator[1]]);

        ui->separationSpeedValueLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[0].
            separationSpeed));

        /// The first stage parameters showing
        ui->firstStageCharSpeedValueLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[0].
            charactSpeed));
        if (this->_pTripleStageShellUI->stageBallCharact[0].specialType
            == JET_ENGINE) {
            ui->firstStageCompleteParamLabel->setText("Jet engine activity "
                "duration [s]:");
        }
        else {
            ui->firstStageCompleteParamLabel->setText("The 1st stage activity "
                "duration [s]:");
        }
        ui->firstStageCompleteParamLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[0].completePar));

        /// The second stage parameters showing
        ui->secondStageCharSpeedValueLabel->setEnabled(true);
        ui->secondStageCharSpeedValueLineEdit->setEnabled(true);
        ui->secondStageCharSpeedValueLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[1].
            charactSpeed));
        ui->secondStageCompleteParamLabel->setEnabled(true);
        ui->secondStageCompleteParamLabel->setText("The 2nd stage activity "
            "duration [s]:");
        ui->secondStageCompleteParamLineEdit->setEnabled(true);
        ui->secondStageCompleteParamLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[1].completePar));

        /// The third stage parameters showing
        ui->thirdStageCharSpeedValueLabel->setEnabled(true);
        ui->thirdStageCharSpeedValueLineEdit->setEnabled(true);
        ui->thirdStageCharSpeedValueLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[2].
            charactSpeed));
        ui->thirdStageCompleteParamLabel->setEnabled(true);
        if (this->_pTripleStageShellUI->code == 999) {
            /// S8-KL
            ui->actionCalculate_S8_KL_2nd_stage_activity_time->setEnabled(true);
            ui->thirdStageCompleteParamLabel->setText("The 3rd stage activity "
                "duration [s]:");
        }
        else {
            ui->thirdStageCompleteParamLabel->setText("Shell destination "
                "height relative to the absolute target's one [m]:");
        }
        ui->thirdStageCompleteParamLineEdit->setEnabled(true);
        ui->thirdStageCompleteParamLineEdit->setText(QString::number(
            this->_pTripleStageShellUI->stageBallCharact[2].completePar));

        /// Setting the last stage complete parameter if the user chooses none
        this->_lastStageCompleteConditionUI =
            this->_pTripleStageShellUI->stageBallCharact[2].completeType;
        this->_lastStageCompleteParamUI =
            this->_pTripleStageShellUI->stageBallCharact[2].completePar;
    }

//    this->statusBar()->showMessage(QString::number(
//        this->_lastStageCompleteConditionUI) + ' '
//        + QString::number(this->_lastStageCompleteParamUI));

    ui->userDefinedLastStageCompleteParamLabel->setEnabled(true);
    ui->userDefinedLastStageCompleteParamComboBox->setEnabled(true);
    ui->userDefinedLastStageCompleteParamComboBox->setCurrentIndex(-1);
    ui->userDefinedLastStageCompleteParamValueLabel->setEnabled(false);
    ui->userDefinedLastStageCompleteParamValueLineEdit->setEnabled(false);

    connect(ui->userDefinedLastStageCompleteParamComboBox,
        SIGNAL(currentIndexChanged(int)), this,
        SLOT(enterLastStageCompleteParam()));
}

void MainWindow::enterLastStageCompleteParam() {
    ui->userDefinedLastStageCompleteParamValueLabel->setEnabled(true);
    ui->userDefinedLastStageCompleteParamValueLineEdit->setEnabled(true);
    ui->userDefinedLastStageCompleteParamValueLineEdit->clear();

    connect(ui->userDefinedLastStageCompleteParamValueLineEdit,
        SIGNAL(editingFinished()), this, SLOT(setLastStageCompleteParam()));
}

void MainWindow::setLastStageCompleteParam() {
    if (!ui->userDefinedLastStageCompleteParamValueLineEdit->text().isEmpty()) {
        switch (ui->userDefinedLastStageCompleteParamComboBox->currentIndex()) {
        case 0:
            this->_lastStageCompleteConditionUI = ON_HEIGHT;
            break;
        case 1:
            this->_lastStageCompleteConditionUI = ON_TIME;
            break;
        case 2:
            this->_lastStageCompleteConditionUI = ON_RANGE;
            break;
        case 3:
            this->_lastStageCompleteConditionUI = ON_SPEED_PRESS;
            break;
        case 4:
            this->_lastStageCompleteConditionUI = ON_TRAJECTORY_PEAK;
            break;
        }
        this->_lastStageCompleteParamUI =
            ui->userDefinedLastStageCompleteParamValueLineEdit->text().
            toDouble();
    }
}

void MainWindow::checkInputData()
{
    QMessageBox *pQMB = new QMessageBox(this);
    pQMB->setWindowTitle("Input is not completed");
    pQMB->setIcon(QMessageBox::Warning);
    pQMB->setStandardButtons(QMessageBox::Ok);

    if (!ui->shellNameComboBox->currentText().isEmpty()
        && (ui->userDefinedLastStageCompleteParamValueLineEdit->isEnabled()
        && ui->userDefinedLastStageCompleteParamValueLineEdit->text().
        isEmpty())) {
        pQMB->setText("Please enter the last stage complete parameter value.");
        pQMB->show();

        connect(pQMB, SIGNAL(accepted()), this, SLOT(openCalcResultsDialog()));
        return;
    }
    else if (ui->shellNameComboBox->currentText().isEmpty()) {
        pQMB->setText("Please choose the shell for calculation.");
        pQMB->show();

        connect(pQMB, SIGNAL(accepted()), this, SLOT(openCalcResultsDialog()));
        return;
    }
    this->openCalcResultsDialog();

    connect(pQMB, SIGNAL(finished(int)), pQMB, SLOT(deleteLater()));
}

void MainWindow::openCalcResultsDialog() {

    BallCalcResults* pBCR = new BallCalcResults(this);
    pBCR->setShellName(ui->shellNameComboBox->currentText());

    /// Whole ballistic calculation circle
    ballCalcCircle(pBCR);

    ui->actionCompare_the_atmospheric_calculations->setEnabled(true);

//    this->statusBar()->showMessage(QString::number(sizeof(*_pMyBallist)) + " "
//        + QString::number(sizeof(*_pBALLIST)));
    this->statusBar()->showMessage(QString::number(sizeof(*this)));
}

void MainWindow::openS8KLadjustResultsDialog() {

    BallCalcResults* pBCR = new BallCalcResults(this);
    pBCR->setShellName(ui->shellNameComboBox->currentText());

    if (ui->actionCalculate_S8_KL_2nd_stage_activity_time->isEnabled()) {
        s8_kl_adjustParamByHalfDivision(pBCR);
    }

    ui->actionCompare_the_atmospheric_calculations->setEnabled(true);
}


/*! Головной менеджер балистического вычислителя
********************************************************************************
* \return код выполнения операции:
*  - OPER_SUCCESS - успешное завершение операции
*  - OPER_FAILURE - операция не может быть выполнена
*/
TOPER_RESULT MainWindow::ballist_hInit (
        T_BALLIST_MODIF	modification,		/*!< Модификация модуля			*/
        TOPER_RESULT	(*(pInputData))(TBalInputData *, TCREW_MEMBER)
)
{
    memset(_pBALLIST, 0, sizeof(TBALLIST));
    _pBALLIST->workMode[NAVIG] = REGIME_ON;
    _pBALLIST->workMode[PILOT] = REGIME_ON;
    _pBALLIST->modification = modification;
    _pBALLIST->modifCheck   = modification;

    if (pInputData)		_pBALLIST->pInputData = pInputData;
    else				return OPER_FAILURE;

    return OPER_SUCCESS;
}

/*! Функция формирования параметров, определяющих
**  баллистические характеристики НАСП
********************************************************************************
**  \return
*/
void MainWindow::ballist_lFormAspData (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{
    /* Единицный вектор установки АСП в связанной с.к. @dd	*/
    dv3InitDv3(_pBALLIST->input[crewId].aspEvectCSC,
            _pBALLIST->state[crewId].aspData.aspEvectCSC);
    /* Единицный вектор установки АСП в горизонт  с.к. @dd	*/
    dv3InitDv3(_pBALLIST->input[crewId].aspEvectHSC,
            _pBALLIST->state[crewId].aspData.aspEvectHSC);
    /* Тип выбранного НАСП*/
    _pBALLIST->state[crewId].aspData.typeOfChosenNasp =
            _pBALLIST->input[crewId].typeOfChosenNasp;
}

/*!  Функция формирования навигационных параметров
********************************************************************************
** \return
*/
void MainWindow::ballist_lFormNvgData (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{
    /*! Термодинамическая температура Кельвина для точки таяния льда
     * при давлении 101325 Па*/
    const double cIceThawingKelvinTemperature = 273.15;
    /*! Температура, близкая к нулевой*/
    const double cNullTemperature = 0.01;

    const double cAirFactor = 20.046796;
    /*! Число Маха, близкое к нулевому*/
    const double cNullMach = 0.01;

    /* Высота ЛА	*/
    _pBALLIST->state[crewId].nvgData.trueHeight = _pBALLIST->input[crewId].hAbs;
    /* истинная воздушная скорость полета*/
    _pBALLIST->state[crewId].nvgData.trueAirspeed = _pBALLIST->input[crewId].trueAirspeed;
    /* приборная воздушная скорость полета*/
    _pBALLIST->state[crewId].nvgData.indicatedAirspeed = _pBALLIST->input[crewId].indicatedAirspeed;
    /* температура воздуха на текущей высоте полета [град.К]*/
    _pBALLIST->state[crewId].nvgData.airTemperature = cIceThawingKelvinTemperature + _pBALLIST->input[crewId].aerTerm;
    /* число Маха*/
    if (_pBALLIST->state[crewId].nvgData.airTemperature > cNullTemperature)
    {
        _pBALLIST->state[crewId].nvgData.mach = fabs(_pBALLIST->state[crewId].nvgData.trueAirspeed /
                (cAirFactor * sqrt(_pBALLIST->state[crewId].nvgData.airTemperature)));
        if (_pBALLIST->state[crewId].nvgData.mach < cNullMach)
            _pBALLIST->state[crewId].nvgData.mach = cNullMach;
    }
    else
        _pBALLIST->state[crewId].nvgData.mach = cNullMach;
    /* Высота цели относительно ЛА	*/
    _pBALLIST->state[crewId].nvgData.relTrgHh = _pBALLIST->input[crewId].relTrgHh;
    /* вектор скорости ЛА в горизонтированной СК, @dd*/
    dv3InitDv3(_pBALLIST->input[crewId].waySpeedHSC,  _pBALLIST->state[crewId].nvgData.waySpeedHSC);

    /* Скорость ветра в горизонт  С.К @dd	*/
    dv3InitDv3(_pBALLIST->input[crewId].windSpeedHSC, _pBALLIST->state[crewId].nvgData.windSpeedHSC);
    /* V воздушная скорость ЛА        в связанной с.к. @dd	*/
    dv3InitDv3(_pBALLIST->input[crewId].airSpeedCSC, _pBALLIST->state[crewId].nvgData.airSpeedCSC);
}

/*!	Функция формирования выходной информации
********************************************************************************
**	\return
*/
void MainWindow::ballist_lFormOutputData (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{
    const double	slideCorr=0.5;
    double	driftImpactPointZ_corr;
    /* Время падения НАСП*/
    _pBALLIST->output[crewId].fallTime = _pBALLIST->state[crewId].calcControl.fallTime;
    /* Вектор координат точки падения НАСП в ГорСК*/
    if (BAL_ASP_C_8 == _pBALLIST->input[crewId].typeOfChosenNasp)	/* @dd Изменено по согласованию с Пашей	*/
        driftImpactPointZ_corr = _pBALLIST->state[crewId].calcControl.driftImpactPoint[Z]*slideCorr;
    else
        driftImpactPointZ_corr = _pBALLIST->state[crewId].calcControl.driftImpactPoint[Z];
    dv3Init(_pBALLIST->state[crewId].calcControl.driftImpactPoint[X],
            _pBALLIST->state[crewId].calcControl.driftImpactPoint[Y],
            driftImpactPointZ_corr,
            _pBALLIST->output[crewId].impactPointHSC);

#if 0 /*def KBO	Вероятнее всего это ошибочная гипотеза и ничего учитывать в
конечном векторе не стоит, но можно подумать как скорректировать начальное
положение АСП с учетом размещения пушки на объекте	*/
    {	/* Поправка к вектору относа в горизонтированной с.к,
     сформированная в связи с выносом оси ИЛС относительно оси ствола АСП	*/
        int i;
        for (i=0; i<3; i++)
            this->impactPointHSC[i] += suoStateData.dvrGrDelt[i];
    }
#endif

    /* Дальность до ПМ	*/
    _pBALLIST->output[crewId].distance =
            dv3ModGet(_pBALLIST->output[crewId].impactPointHSC);

//    delete BALLIST.state[crewId].calcControl.pAirRoList;
//    delete BALLIST.state[crewId].calcControl.pSoundSpeedInvList;
}

/*!	Функция баллистического вычислителя
********************************************************************************
**	\return
*/
void MainWindow::ballist_lCompute (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{
    /* Ввод и проверка корректности задания значений кодов НАСП*/
    bal_hInCodeNaspCheck(&_pBALLIST->state[crewId].aspData, &_pBALLIST->input[crewId]);
    /* Формирование баллистических характеристик НАСП*/
    bal_hFormCharNasp(&_pBALLIST->state[crewId].aspData, &_pBALLIST->state[crewId].switchOfBallist);
    if ( ( 1 == _pBALLIST->state[crewId].switchOfBallist) &&
         (1 == _pBALLIST->state[crewId].calcControl.userCompleteReady) &&
         (REGIME_ON == _pBALLIST->workMode[crewId]) &&
         (_pBALLIST->state[crewId].nvgData.relTrgHh < 2000.0) && /* Цель выше нас не более 2000.0 метров*/
         (_pBALLIST->state[crewId].nvgData.trueHeight > -750.0) )	/* Абсолютная высота больше -750 метров */
    {	 /* Управлениe баллистическим расчетом*/
        bal_calc_hControl(&_pBALLIST->state[crewId].calcControl, &_pBALLIST->state[crewId].aspData, &_pBALLIST->state[crewId].nvgData);
    }
    else
    {
#if 0	/* Для отладки	*/
        pdprint6("\n switcher=%i, compReady=%i, execTrg=%f, trueH=%f, operMode=%i, rdHAbs=%i \n",
                BALLIST.state[crewId].switchOfBallist, BALLIST.state[crewId].calcControl.userCompleteReady,
                BALLIST.state[crewId].nvgData.relTrgHh, BALLIST.state[crewId].nvgData.trueHeight,
                FPO.ARM.AIM.operMode, FPO.NVG.SVS.data.ready.r.hAbs);
#endif
        /* Вектор относа НАСП*/
         dv3Init (.02, .01, 0.0, _pBALLIST->state[crewId].calcControl.driftImpactPoint);
         /* Вектор скорости НАСП в точке падения*/
         dv3Init (0.02, 0.02, 0.02, _pBALLIST->state[crewId].calcControl.speedImpactPoint);
         /* Скорость встречи НАСП с целью (поверхностью)*/
         _pBALLIST->state[crewId].calcControl.incidenceSpeed = 0.0;
         /* Угол встречи НАСП с целью (поверхностью)*/
         _pBALLIST->state[crewId].calcControl.incidenceAngle = -90*DEG_TO_RAD;
         /* Время падения НАСП*/
         _pBALLIST->state[crewId].calcControl.fallTime = 0.0;
         /* Коэффициент поправки к СА-81 по температуре*/
         _pBALLIST->state[crewId].calcControl.temperatureCorrect = 1.0;
         /* Коэффициент поправки к СА-81 по плотности воздуха*/
         _pBALLIST->state[crewId].calcControl.airDensityCorrect = 1.0;
         /* Число шагов интегрирования*/
         _pBALLIST->state[crewId].calcControl.integratStepsAmount = 0;
    }
}

/*! Головной менеджер балистического вычислителя
********************************************************************************
* \return код выполнения операции:
*  - OPER_SUCCESS - успешное завершение операции
*  - OPER_FAILURE - операция не может быть выполнена
*/
TOPER_RESULT MainWindow::ballist_Monitor (
        TCircleThread	circle	/*!< Признак потока	вызова 					*/
)
{	/* ballist_Monitor	*/
    if (FLAG_FALSE == ballist_lCheckThis(1))
        return OPER_FAILURE;

    if      (circle == QWC)
    {	/* Формирование входов для баллистики	*/
        TCREW_MEMBER	iCrew;
        if (BALLIST_MODIF_KBO == _pBALLIST->modification)
        {
            if (_pBALLIST->pInputData)
                (*(_pBALLIST->pInputData))(&_pBALLIST->input[PILOT], PILOT);
            /*Формирование параметров, определяющих баллистические характеристики НАСП*/
            ballist_lFormAspData(PILOT);
            /* Формирование навигационных параметров*/
            ballist_lFormNvgData(PILOT);
            /* Формирование предварительных данных для БВ	*/
            bal_calc_hPrepareData(&_pBALLIST->state[PILOT].calcControl,
                    &_pBALLIST->input[PILOT]);
            /* Выполнить расчет баллистических поправок	*/
            ballist_lCompute(PILOT);
            /* Формирование выходной информации*/
            ballist_lFormOutputData(PILOT);
        }
        else
        {
            for (int i = 0; i < ALL_CREW; i++
//                iCrew = NAVIG; iCrew < ALL_CREW; iCrew += PILOT
                )
            {
//                if (!i) {
                    _pBALLIST->state[i].calcControl.p930mBallDataList =
                        new QList<QList<double>*>;
                    for (int j = 0; j < 11; j++) {
                        _pBALLIST->state[i].calcControl.p930mBallDataList->
                            append(new QList<double>);
                    }
//                }
//                if (pBALLIST->pInputData)
//                    (*(pBALLIST->pInputData))(&pBALLIST->input[i/*iCrew*/], (TCREW_MEMBER)i/*iCrew*/);
                /*Формирование параметров, определяющих баллистические характеристики НАСП*/
                ballist_lFormAspData((TCREW_MEMBER)i/*iCrew*/);
                /* Формирование навигационных параметров*/
                ballist_lFormNvgData((TCREW_MEMBER)i/*iCrew*/);
                /* Формирование предварительных данных для БВ	*/
                bal_calc_hPrepareData(&_pBALLIST->state[i/*iCrew*/].calcControl,
                        &_pBALLIST->input[i/*iCrew*/]);
                /* Выполнить расчет баллистических поправок	*/
                ballist_lCompute((TCREW_MEMBER)i/*iCrew*/);
                /* Формирование выходной информации*/
                ballist_lFormOutputData((TCREW_MEMBER)i/*iCrew*/);
            }
        }
    }

//    delete _pBALLIST->state[NAVIG].calcControl.p930mBallDataList;

    return OPER_SUCCESS;
}	/* ballist_Monitor	*/

/*! Функция возвращает дальность до падения боеприпаса
********************************************************************************
** \return Результат вычисления
*/
TDouble MainWindow::ballist_GetDistance (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{	/* ballist_GetDistance	*/
    TDouble returnValue=0.0;

    if (FLAG_FALSE == ballist_lCheckThis(2))
        return returnValue;

    returnValue = _pBALLIST->output[crewId].distance;
    return returnValue;
}	/* ballist_GetDistance	*/

/*! Функция возвращает время падения боеприпаса
********************************************************************************
** \return Результат вычисления
*/
TDouble MainWindow::ballist_GetFallTime (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{	/* ballist_GetFallTime	*/
    TDouble returnValue=0.0;

    if (FLAG_FALSE == ballist_lCheckThis(3))
        return returnValue;

    returnValue = _pBALLIST->output[crewId].fallTime;
    return returnValue;
}	/* ballist_GetFallTime	*/

/*! Функция возвращает вектор относа боеприпаса
********************************************************************************
** \return Результат вычисления
*/
TOPER_RESULT MainWindow::ballist_GetImpactPointHSC (
        TDVect3 impactPointHSC,	/*!< вектор относа НАСП в ГорСК */
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{	/* ballist_GetImpactPointHSC	*/
    TOPER_RESULT returnValue=OPER_FAILURE;

    if (FLAG_FALSE == ballist_lCheckThis(4))
        return returnValue;

    memcpy(impactPointHSC, _pBALLIST->output[crewId].impactPointHSC,
            sizeof(TDVect3));
    if (_pBALLIST->output[crewId].distance > 10.0)
        returnValue=OPER_SUCCESS;

    return returnValue;
}	/* ballist_GetImpactPointHSC	*/

/*! Метод реализующий
********************************************************************************
** \return код выполнения операции:
**  - OPER_SUCCESS - успешное завершение операции
**  - OPER_FAILURE - операция не может быть выполнена
*/
TDouble MainWindow::ballist_GetInpRelTrgHh (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{	/* ballist_GetInpRelTrgHh	*/
    TDouble returnValue=0.0;

    if (FLAG_FALSE == ballist_lCheckThis(5))
        return returnValue;

    if (crewId < ANYONE)
    {
        returnValue = _pBALLIST->input[crewId].relTrgHh;
    }
    else
    {
        returnValue = _pBALLIST->input[PILOT].relTrgHh;
    }
    return returnValue;
}	/* ballist_GetInpRelTrgHh	*/

/*! Метод реализующий проеверку наличия ручного выключения балитики из работы
********************************************************************************
** \return код выполнения операции:
**  - OPER_SUCCESS - успешное завершение операции
**  - OPER_FAILURE - операция не может быть выполнена
*/
TREGIME_MODE MainWindow::ballist_GetWorkMode (
        TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
)
{	/* ballist_GetWorkMode	*/
    TREGIME_MODE	operResult=REGIME_OFF;

    if (FLAG_FALSE == ballist_lCheckThis(1))
        return operResult;

    if (crewId < ANYONE)
    {
        if (REGIME_ON == _pBALLIST->workMode[crewId])
            operResult = REGIME_ON;
    }
    else
    {
        if ((REGIME_ON == _pBALLIST->workMode[PILOT]) &&
            (REGIME_ON == _pBALLIST->workMode[NAVIG]))
            operResult = REGIME_ON;
    }

    return operResult;
}	/* ballist_GetWorkMode	*/

/*! Метод реализующий задания режима работы баллистики
********************************************************************************
** \return код выполнения операции:
**  - OPER_SUCCESS - успешное завершение операции
**  - OPER_FAILURE - операция не может быть выполнена
*/
TOPER_RESULT MainWindow::ballist_SetWorkMode (
    TREGIME_MODE	workMode,	/*!< Включение оперативного режима работы	*/
    TCREW_MEMBER	crewId,	/*!< Идентификатор члена экипажа	*/
    TUInt16			idCall		/*!< Идентификатор вызова					*/
)
{	/* ballist_SetWorkMode	*/
    TOPER_RESULT	operResult=OPER_FAILURE;

    if (FLAG_FALSE == ballist_lCheckThis(2))
        return operResult;

#ifdef BAL_DBG
    if (REGIME_ON == workMode)
    {
        if (REGIME_OFF == BALLIST.workMode)
            pdprint1("\n ballist_SetWorkMode: REGIM_ON,  idCall=%i \n",
                    idCall);
    }
    else
    {
        if (REGIME_ON == BALLIST.workMode)
            pdprint1("\n ballist_SetWorkMode: REGIM_OFF, idCall=%i \n",
                    idCall);
    }
#endif
    if (REGIME_ON == workMode)
        _pBALLIST->workMode[crewId] = REGIME_ON;
    else
        _pBALLIST->workMode[crewId] = REGIME_OFF;

    operResult = OPER_SUCCESS;
    return operResult;
}	/* ballist_SetWorkMode	*/

/*! Метод реализующий задание типа расчета атомсферы для БВ
********************************************************************************
** \return код выполнения операции:
**  - OPER_SUCCESS - успешное завершение операции
**  - OPER_FAILURE - операция не может быть выполнена
*/
TOPER_RESULT MainWindow::ballist_SetAtmosphCalcType (
        T_BALLIST_ATMOSPH		atmCalcType	/*!< [in] Задаваемое значение */
)
{	/* ballist_SetAtmosphCalcType	*/
    TOPER_RESULT	operResult=OPER_FAILURE;

    if (atmCalcType < BALLIST_ATM_ALL)
    {
        _pBALLIST->atmosphCalcType = atmCalcType;
        operResult = OPER_SUCCESS;
    }

    return operResult;
}	/* ballist_SetAtmosphCalcType	*/

/*! Метод возвращающий тип расчета атмосферы для БВ
********************************************************************************
** \return Запрашиваемое значение
*/
T_BALLIST_ATMOSPH MainWindow::ballist_GetAtmosphCalcType ( void )
{	/* ballist_GetAtmosphCalcType	*/
    return _pBALLIST->atmosphCalcType;
}	/* ballist_GetAtmosphCalcType   */


void MainWindow::openAtmosphCalcComparisonDialog() {
    QDialog *pAtmosphCalcComparisonDialog = new QDialog(this);
    pAtmosphCalcComparisonDialog->setWindowTitle("Atmospheric calculations "
        "comparison");
    pAtmosphCalcComparisonDialog->resize(1920, 720);

    QTableWidget *pqtw = new QTableWidget(pAtmosphCalcComparisonDialog);
    pqtw->setRowCount(_pMyBallist->IntBD.pShellAbsHeightList->size());
    pqtw->setColumnCount(14);
    pqtw->resize(pAtmosphCalcComparisonDialog->size());

    QList<QString> *pqls = new QList<QString>;
    pqls->append("Height");
    pqls->append("Calculated Ro");
    pqls->append("Table defined Ro");
    pqls->append("Delta Ro");
    pqls->append("Calculated aN");
    pqls->append("Table defined aN");
    pqls->append("Delta aN");
    pqls->append("Calculated Ro correction");
    pqls->append("Table defined Ro correction");
    pqls->append("Calculated & corrected Ro");
    pqls->append("Table defined & corrected Ro");
    pqls->append("Delta corrected Ro");
    pqls->append("Calculated T correction");
    pqls->append("Table defined T correction");

    pqtw->setHorizontalHeaderLabels(*pqls);

    delete pqls;

    double calcTcorr, tableTcorr, calcRoCorrVal, tableRoCorrVal;

//    double machVal = 0.5;
//    for (int i = 0; i <= 20000; i += 500) {
//        pqtw->setItem(i / 500, 0, new QTableWidgetItem(QString::number(i)));
//        pqtw->setItem(i / 500, 1, new QTableWidgetItem(QString::number(
//            rofH(i))));
//        pqtw->setItem(i / 500, 2, new QTableWidgetItem(QString::number(
//            tableRo(i))));
//        pqtw->setItem(i / 500, 3, new QTableWidgetItem(QString::number(
//            fabs(100.0 * (rofH(i) - tableRo(i)) / rofH(i))) + " %"));
//        pqtw->setItem(i / 500, 4, new QTableWidgetItem(QString::number(
//            afH(i))));
//        pqtw->setItem(i / 500, 5, new QTableWidgetItem(QString::number(
//            tableA(i))));
//        pqtw->setItem(i / 500, 6, new QTableWidgetItem(QString::number(
//            fabs(100.0 * (afH(i) - tableA(i)) / afH(i))) + " %"));
//        calcRoCorrVal = calcRoCorr(i, machVal, 273.15, calcTcorr, machVal
//            * afH(i), machVal * afH(i));
//        pqtw->setItem(i / 500, 7, new QTableWidgetItem(QString::number(
//            calcRoCorrVal)));

//        tableRoCorrVal = tableRoCorr(i, machVal, 273.15, tableTcorr, machVal
//            * tableA(i), machVal * tableA(i));
//        pqtw->setItem(i / 500, 8, new QTableWidgetItem(QString::number(
//            tableRoCorrVal)));
//        pqtw->setItem(i / 500, 9, new QTableWidgetItem(QString::number(
//            calcRoCorrVal * rofH(i))));
//        pqtw->setItem(i / 500, 10, new QTableWidgetItem(QString::number(
//            tableRoCorrVal * tableRo(i))));
//        pqtw->setItem(i / 500, 11, new QTableWidgetItem(QString::number(
//            fabs(100.0 * (calcRoCorrVal * rofH(i) - tableRoCorrVal * tableRo(i))
//            / (calcRoCorrVal * rofH(i)))) + " %"));
//        pqtw->setItem(i / 500, 12, new QTableWidgetItem(QString::number(
//            calcTcorr)));
//        pqtw->setItem(i / 500, 13, new QTableWidgetItem(QString::number(
//            tableTcorr)));
//    }

    int i = 0;
    do {
        pqtw->setItem(i, 0, new QTableWidgetItem(QString::number(
            _pMyBallist->IntBD.pShellAbsHeightList->at(i))));
        pqtw->setItem(i, 1, new QTableWidgetItem(QString::number(
            rofH(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))));
        pqtw->setItem(i, 2, new QTableWidgetItem(QString::number(
            tableRo(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))));
        pqtw->setItem(i, 3, new QTableWidgetItem(QString::number(
            fabs(100.0 * (rofH(_pMyBallist->IntBD.pShellAbsHeightList->at(i))
            - tableRo(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))
            / rofH(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))) + " %"));
        pqtw->setItem(i, 4, new QTableWidgetItem(QString::number(
            afH(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))));
        pqtw->setItem(i, 5, new QTableWidgetItem(QString::number(
            tableA(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))));
        pqtw->setItem(i, 6, new QTableWidgetItem(QString::number(
            fabs(100.0 * (afH(_pMyBallist->IntBD.pShellAbsHeightList->at(i))
            - tableA(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))
            / afH(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))) + " %"));

        calcRoCorrVal = calcRoCorr(_pMyBallist->IntBD.pShellAbsHeightList->at(i),
            _pMyBallist->IntBD.pMlist->at(i),
            _pBALLIST->state[0].nvgData.airTemperature, calcTcorr,
            _pMyBallist->IntBD.pMlist->at(i)
            * afH(_pMyBallist->IntBD.pShellAbsHeightList->at(i)),
            _pMyBallist->IntBD.pMlist->at(i)
            * afH(_pMyBallist->IntBD.pShellAbsHeightList->at(i))/* + 10.0*/);
        pqtw->setItem(i, 7, new QTableWidgetItem(QString::number(
            calcRoCorrVal)));

        tableRoCorrVal = tableRoCorr(i, _pMyBallist->IntBD.pMlist->at(i),
            _pBALLIST->state[0].nvgData.airTemperature,
            tableTcorr, _pMyBallist->IntBD.pMlist->at(i)
            * tableA(_pMyBallist->IntBD.pShellAbsHeightList->at(i)),
            _pMyBallist->IntBD.pMlist->at(i)
            * tableA(_pMyBallist->IntBD.pShellAbsHeightList->at(i))/* + 10.0*/);
        pqtw->setItem(i, 8, new QTableWidgetItem(QString::number(
            tableRoCorrVal)));

        pqtw->setItem(i, 9, new QTableWidgetItem(QString::number(calcRoCorrVal
            * rofH(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))));
        pqtw->setItem(i, 10, new QTableWidgetItem(QString::number(tableRoCorrVal
            * tableRo(_pMyBallist->IntBD.pShellAbsHeightList->at(i)))));
        pqtw->setItem(i, 11, new QTableWidgetItem(QString::number(fabs(100.0
            * (calcRoCorrVal * rofH(_pMyBallist->IntBD.pShellAbsHeightList->at(i))
            - tableRoCorrVal
            * tableRo(_pMyBallist->IntBD.pShellAbsHeightList->at(i))) /
            (calcRoCorrVal
            * rofH(_pMyBallist->IntBD.pShellAbsHeightList->at(i))))) + " %"));
        pqtw->setItem(i, 12, new QTableWidgetItem(QString::number(calcTcorr)));
        pqtw->setItem(i, 13, new QTableWidgetItem(QString::number(tableTcorr)));

        i++;
    } while (i < _pMyBallist->IntBD.pShellAbsHeightList->size());

    pqtw->resizeColumnsToContents();

    pAtmosphCalcComparisonDialog->show();

    connect(pAtmosphCalcComparisonDialog, SIGNAL(finished(int)),
        pAtmosphCalcComparisonDialog, SLOT(deleteLater()));
}
