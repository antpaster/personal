#include <math.h>
#include <QList>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QFile>

//#include <QPen>
//#include <QPainter>
#include <QGraphicsSimpleTextItem>

#include "ballcalcresults.h"
#include "ui_ballcalcresults.h"
#include "../OwnVersion/typesnconstants.h"
#include "../OwnVersion/generalcalc.h"
#include "../OwnVersion/ballarchive.h"
#include "../OwnVersion/ballcharacts.h"
#include "../OwnVersion/atmosph.h"
#include "../OwnVersion/basic_diffequ.h"
#include "../OwnVersion/basic_draglaw.h"
#include "../OwnVersion/butchertables.h"
#include "../OwnVersion/VVAballistix/vva_constants.h"
#include "../OwnVersion/VVAballistix/vva_diffequ.h"
#include "../OwnVersion/S8_KLballistix/s8_kl_constants.h"
#include "../OwnVersion/S8_KLballistix/s8_kl_diffequ.h"

#define CYCLE_BALLIST 0


BallCalcResults::BallCalcResults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BallCalcResults)
{
    ui->setupUi(this);
}

BallCalcResults::~BallCalcResults()
{
    delete _pAxList;
    delete _pAyList;
    delete _pAzList;

    delete ui;
}

/// Stage ballistic parameters calculation for S8-KL missile
void BallCalcResults::s8_kl_stageBallistParamsCalc(
    const int stageNumber,
    const double M,
    const double tCurr,
    const double prevStageDuration,
    const double massConsumption,
    double &cx,
    double &cyAlpha,
    double &minusMzAlpha,
    double &minusMzOmegaLineZ,
    double &mx,
    double &minusMxOmegaLineX,
    double &d,
    double &l,
    double &m,
    double &Jx,
    double &Jz
) {
    switch (stageNumber) {
    case 0:
        /// Ballistic and drag law assignments (1st (active) stage)
        cx = arrValLinInterpol(M, s8_kl_cMachArr, s8_kl_cCx0activePartArr,
            s8_kl_cArrSize);
        cyAlpha = arrValLinInterpol(M, s8_kl_cMachArr, s8_kl_cCyAlphaArr,
            s8_kl_cArrSize);
        minusMzAlpha = arrValLinInterpol(M, s8_kl_cMachArr,
            s8_kl_cMinusMzAlphaActivePartArr, s8_kl_cArrSize);
        minusMzOmegaLineZ = arrValLinInterpol(M, s8_kl_cMachArr,
            s8_kl_cMinusMzOmegaLineZactivePartArr, s8_kl_cArrSize);
        mx = arrValLinInterpol(M, s8_kl_cMachArr, s8_kl_cMxArr, s8_kl_cArrSize);
        minusMxOmegaLineX = arrValLinInterpol(M, s8_kl_cMachArr,
            s8_kl_cMinusMxOmegaLineXarr, s8_kl_cArrSize);

        d = s8_kl_cd;
        l = s8_kl_cl;
        m = s8_kl_cm - massConsumption * (tCurr - prevStageDuration);
        Jx = s8_kl_cJxActiveStage;
        Jz = s8_kl_cJzActiveStage;
        break;

    case 1:
        /// Ballistic and drag law assignments (2nd (passive) stage)
        cx = arrValLinInterpol(M, s8_kl_cMachArr, s8_kl_cCx0passivePartArr,
            s8_kl_cArrSize);
        cyAlpha = arrValLinInterpol(M, s8_kl_cMachArr, s8_kl_cCyAlphaArr,
            s8_kl_cArrSize);
        minusMzAlpha = arrValLinInterpol(M, s8_kl_cMachArr,
            s8_kl_cMinusMzAlphaPassivePartArr, s8_kl_cArrSize);
        minusMzOmegaLineZ = arrValLinInterpol(M, s8_kl_cMachArr,
            s8_kl_cMinusMzOmegaLineZpassivePartArr, s8_kl_cArrSize);
        mx = arrValLinInterpol(M, s8_kl_cMachArr, s8_kl_cMxArr, s8_kl_cArrSize);
        minusMxOmegaLineX = arrValLinInterpol(M, s8_kl_cMachArr,
            s8_kl_cMinusMxOmegaLineXarr, s8_kl_cArrSize);

        d = s8_kl_cd;
        l = s8_kl_cl;
        m = s8_kl_cm - s8_kl_cFuelMass;
        Jx = s8_kl_cJxPassiveStage;
        Jz = s8_kl_cJzPassiveStage;
        break;

    case 2:
        /// Ballistic and drag law assignments (3rd stage (element))
        cx = arrValLinInterpol(M, s8_kl_cMachArrElem, s8_kl_cCx0arrElem,
            s8_kl_cArrSizeElem);
        cyAlpha = arrValLinInterpol(M, s8_kl_cMachArrElem,
            s8_kl_cCyAlphaArrElem, s8_kl_cArrSizeElem);
        minusMzAlpha = arrValLinInterpol(M, s8_kl_cMachArrElem,
            s8_kl_cMinusMzAlphaArrElem, s8_kl_cArrSizeElem);
        minusMzOmegaLineZ = arrValLinInterpol(M, s8_kl_cMachArrElem,
            s8_kl_cMinusMzOmegaLineZarrElem, s8_kl_cArrSizeElem);
        mx = arrValLinInterpol(M, s8_kl_cMachArrElem, s8_kl_cMxArrElem,
            s8_kl_cArrSizeElem);
        minusMxOmegaLineX = arrValLinInterpol(M, s8_kl_cMachArrElem,
            s8_kl_cMinusMxOmegaLineXarrElem, s8_kl_cArrSizeElem);

        d = s8_kl_cdElem;
        l = s8_kl_clElem;
        m = s8_kl_cmElem;
        Jx = s8_kl_cJxElem;
        Jz = s8_kl_cJzElem;
        break;

    default:
        break;
    }
}

/// Filling the ballistic calculation table string by current calculation step
/// data
void BallCalcResults::fillBallCalcResTableString(
    int itemRowNumber,
    const TInternalBallData *pIntBD
) {
//    for (int i = 0; i < 11; i++) {
//        ui->ballCalcResTableWidget->setItem(itemRowNumber, i,
//            new QTableWidgetItem(QString::number(
//            _p930mBallDataList->at(i)->at(pIntBD->integrStepCounter))));
//    }

    /// Way velocity value
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 0,
        new QTableWidgetItem(QString::number(vValue(pIntBD->Wvect))));
    /// X axis way velocity projection in Normal CS
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 1,
        new QTableWidgetItem(QString::number(pIntBD->Wvect[AXIS_X])));
    /// Y axis way velocity projection in Normal CS
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 2,
        new QTableWidgetItem(QString::number(pIntBD->Wvect[AXIS_Y])));
    /// Z axis way velocity projection in Normal CS
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 3,
        new QTableWidgetItem(QString::number(pIntBD->Wvect[AXIS_Z])));
    /// Wind velocity value
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 4,
        new QTableWidgetItem(QString::number(vValue(pIntBD->Uvect))));
    /// X axis coordinate projection in Normal CS
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 5,
        new QTableWidgetItem(QString::number(pIntBD->currDESSV[3])));
    /// Absolute height
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 6,
        new QTableWidgetItem(QString::number(pIntBD->currDESSV[4])));
    /// Z axis coordinate projection in Normal CS
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 7,
        new QTableWidgetItem(QString::number(pIntBD->currDESSV[5])));
    /// Basic drag law coefficient
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 8,
        new QTableWidgetItem(QString::number(pIntBD->cx)));
    /// Integration step value
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 9,
        new QTableWidgetItem(QString::number(pIntBD->hCurr)));
    /// Operating time
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 10,
        new QTableWidgetItem(QString::number(pIntBD->currTime)));
}

/// Main ballistic calculation function
bool BallCalcResults::ballCalculation(
    const TInputBallData *pInpBD,
    TInternalBallData *pIntBD
) {
    setWindowTitle(_shellName + " ballistic calculation results (Normal CS)");

#if CYCLE_BALLIST
    pIntBD->_maxStepNumberPerCycle = 30;
    pIntBD->_maxStepNumber = 3000;
#else
    pIntBD->maxStepNumber = 100000;
#endif

    ui->ballCalcResTableWidget->setRowCount(pIntBD->maxStepNumber);
    ui->ballCalcResTableWidget->setColumnCount(
#if CYCLE_BALLIST
        13
#else
        11
#endif
        );

    QList<QString>* pqls = new QList<QString>;
    pqls->append("Wval");
    pqls->append("Wx");
    pqls->append("Wy");
    pqls->append("Wz");
    pqls->append("Uval");
    pqls->append("x");
    pqls->append("Habs");
    pqls->append("z");
    pqls->append("cx");
    pqls->append("h");
    pqls->append("t");
#if CYCLE_BALLIST
    pqls->append("Cycle counter");
    pqls->append("Step counter in cycle");
#endif

    ui->ballCalcResTableWidget->setHorizontalHeaderLabels(*pqls);
    this->resize(1250, 1000);
    ui->ballCalcResTableWidget->clearContents();
    delete pqls;

    pIntBD->ballistReliability = true;

    if (pInpBD->pSingleStageShell) {
        pIntBD->pStageBallCharact =
            &pInpBD->pSingleStageShell->stageBallCharact;
        pIntBD->shellType = pInpBD->pSingleStageShell->type;
        pIntBD->stageNumber = 1;
    }
    else if (pInpBD->pDoubleStageShell) {
        pIntBD->pStageBallCharact =
            &pInpBD->pDoubleStageShell->stageBallCharact[0];
        pIntBD->shellType = pInpBD->pDoubleStageShell->type;
        pIntBD->stageNumber = 2;
    }
    else if (pInpBD->pTripleStageShell) {
        pIntBD->pStageBallCharact =
            &pInpBD->pTripleStageShell->stageBallCharact[0];
        pIntBD->shellType = pInpBD->pTripleStageShell->type;
        pIntBD->stageNumber = 3;
    }

    /// Shell way velocity in installed CS assignment without wind yet
    pIntBD->Wvect[AXIS_X] = pIntBD->pStageBallCharact->separationSpeed;
    pIntBD->Wvect[AXIS_Y] = 0.0;
    pIntBD->Wvect[AXIS_Z] = 0.0;

//    /// Partial atmospheric assignments
//    pIntBD->_g = gfH(pInpBD->_appAbsHeight)/*cg0*/;
//    pIntBD->_airRo = rofH(pInpBD->_appAbsHeight); // formula calculated
////    pIntBD->_airRo = tableRo(pInpBD->_appAbsHeight); // table defined
////    atmosphereSA_81(pInpBD->_appAbsHeight, pIntBD->_airRo, 1.0 / pIntBD->_a);

    /// Shell flight time assignment
    pIntBD->prevTime = pIntBD->currTime = pIntBD->prevStageDuration = 0.0;

    /// Initial integration condititions definition
    initCondNaspStart(pInpBD, pIntBD);

//    pIntBD->_shellAbsHeight = pInpBD->_appAbsHeight + pIntBD->_currDESSV[4];
    pIntBD->pShellAbsHeightList = new QList<double>;
    pIntBD->pShellAbsHeightList->append(pIntBD->currDESSV[4]/*pIntBD->_shellAbsHeight*/);

    /// Wind hypothesis consideration
    equVect(pIntBD->Uvect, pInpBD->initUvect);
    windHypothesis(pInpBD, pIntBD);

    /// Initial wind calculation
    gertmansWindModel(pIntBD);

    /// Full atmospheric reassignments
    pIntBD->airT = TfH(pIntBD->currDESSV[4]/*pIntBD->_shellAbsHeight*/);
    pIntBD->g = gfH(pIntBD->currDESSV[4]/*pIntBD->_shellAbsHeight*/)/*cg0*/;
    pIntBD->airRo = rofH(pIntBD->currDESSV[4]/*pIntBD->_shellAbsHeight*/); // formula calculated
//    pIntBD->_airRo = tableRo(pIntBD->_currDESSV[4]/*pIntBD->_shellAbsHeight*/); // table defined
    pIntBD->a = afH(pIntBD->currDESSV[4]/*pIntBD->_shellAbsHeight*/); // formula calculated
//    pIntBD->_a = tableA(pIntBD->_currDESSV[4]/*pIntBD->_shellAbsHeight*/); // table defined
//    atmosphereSA_81(pIntBD->_currDESSV[4]/*pIntBD->_shellAbsHeight*/, pIntBD->_airRo, 1.0 / pIntBD->_a);

    /// Integration step values assignment
    pIntBD->hMin = pIntBD->hMax = pIntBD->hPrev = pIntBD->hCurr
        = pInpBD->initIntegrStep;

    pIntBD->integrStepCounter = pIntBD->stageCounter = 0;

    _pAxList = new QList<double>;
    _pAyList = new QList<double>;
    _pAzList = new QList<double>;

    _pAxList->append(pIntBD->currDESSV[3]);
    _pAyList->append(pIntBD->currDESSV[4]);
    _pAzList->append(pIntBD->currDESSV[5]);

//    _pAxList->append(_p930mBallDataList->at(5)->at(pIntBD->integrStepCounter));
//    _pAyList->append(_p930mBallDataList->at(6)->at(pIntBD->integrStepCounter));
//    _pAzList->append(_p930mBallDataList->at(7)->at(pIntBD->integrStepCounter));

#if CYCLE_BALLIST
    pIntBD->_cycleCounter = pIntBD->_cycleIntegrStepCounter = 0;
#endif

    int itemRowNumber = pIntBD->integrStepCounter;

//    /// Atmosphere correction coefficients
//    double Tcorr, roCorr;
//    Tcorr = roCorr = 1.0;


    //**************************************************************************
    /// Basic calculation

    /// Shell way velocity setting
    pIntBD->Wvect[AXIS_X] = pIntBD->currDESSV[0];
    pIntBD->Wvect[AXIS_Y] = pIntBD->currDESSV[1];
    pIntBD->Wvect[AXIS_Z] = pIntBD->currDESSV[2];

    /// Shell air velocity calculation
    subtract2vect(pIntBD->Wvect, pIntBD->Uvect, pIntBD->Vvect);

    /// Mach value calculation
    pIntBD->M = vValue(pIntBD->Vvect) / pIntBD->a; // formula calculated
//    _vM = vValue(currShellVvect) * _vaInv; // table defined
    pIntBD->pMlist = new QList<double>;
    pIntBD->pMlist->append(pIntBD->M);

//    /// Atmosphere corrections
//    roCorr = calcRoCorr(_DESSVcurrStep[4], _vM, _vT, Tcorr,
//          vValue(currShellVvect), vValue(currShellVvect));

//    roCorr = tableRoCorr(_DESSVcurrStep[4], _vM, _vT, Tcorr,
//        vValue(currShellVvect), vValue(currShellVvect));

//    atmosphereCorrections(_DESSVcurrStep[4], _vM, vValue(currShellVvect),
//        vValue(currShellVvect), Tcorr, roCorr);

    /// Drag law coefficient assignment from normalized cx0 coefficient
    pIntBD->pCxList = new QList<double>;
    pIntBD->cx = genCx(pIntBD);

//    /// Drag law coefficient assignment from unnormalized cx0 coefficient
//    _vcx = genCx(//&_pSingleStageShell->stageBallCharact
//        //&_pDoubleStageShell->stageBallCharact[0]
//        &_pTripleStageShell->stageBallCharact[0]
//        , _vtPrevStageDuration, _vtCurr, arrValLinInterpol(_vM, s8_kl_cMachArr,
//        s8_kl_cCx0activePartArr, s8_kl_cArrSize), _vRo, vValue(_currWCS),
//        s8_kl_cd);

    /// Output data
    fillBallCalcResTableString(itemRowNumber, pIntBD);
#if CYCLE_BALLIST
    /// Cycle counter
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 11,
        new QTableWidgetItem(QString::number(pIntBD->_cycleCounter)));
    /// Intergration step counter in cycle
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 12,
        new QTableWidgetItem(QString::number(pIntBD->_cycleIntegrStepCounter)));
#endif


    /// Integration loop
    for (pIntBD->stageCounter = 0; pIntBD->stageCounter
        < pIntBD->stageNumber; pIntBD->stageCounter++) {

        itemRowNumber = pIntBD->integrStepCounter + pIntBD->stageCounter + 1;
        ui->ballCalcResTableWidget->setItem(itemRowNumber, 0,
            new QTableWidgetItem("Stage "
            + QString::number(pIntBD->stageCounter + 1)));

        /// Current stage ballistic characteristics copying
        if (pInpBD->pSingleStageShell) {
            pIntBD->pStageBallCharact =
                &pInpBD->pSingleStageShell->stageBallCharact;
        }
        else if (pInpBD->pDoubleStageShell) {
            pIntBD->pStageBallCharact =
                &pInpBD->pDoubleStageShell->stageBallCharact[
                pIntBD->stageCounter];
        }
        else if (pInpBD->pTripleStageShell) {
            pIntBD->pStageBallCharact =
                &pInpBD->pTripleStageShell->stageBallCharact[
                pIntBD->stageCounter];
        }

        if (pIntBD->stageCounter) {
            pIntBD->prevStageDuration = pIntBD->currTime;
        }

        if (pIntBD->pStageBallCharact->pusherSign) {
            pIntBD->currTime += pIntBD->pStageBallCharact->barrelTime;
        }

        /// Elements' detaching - for S8-KL only
        if ((pIntBD->stageCounter == 2)
            && pIntBD->pStageBallCharact->pusherSign) {
            /// Assuming elements' detach lengthwise X axis in missile Connected
            /// CS
            TDVect3 elemDetachVvect =
                {pIntBD->pStageBallCharact->separationSpeed, 0.0, 0.0};
            TDMatr3 convMatrix;

            double VvectXOZprojection = sqrt(pIntBD->Vvect[AXIS_X]
                * pIntBD->Vvect[AXIS_X] + pIntBD->Vvect[AXIS_Z]
                * pIntBD->Vvect[AXIS_Z]);
            /// Elements' detach velocity conversion from missile Connected CS
            /// to the Normal one
            connectedCStoNormalCS(asin(pIntBD->Vvect[AXIS_Z]
                / VvectXOZprojection), atan2(pIntBD->Vvect[AXIS_Y],
                VvectXOZprojection), asin(pIntBD->Vvect[AXIS_Z]
                / sqrt(pIntBD->Vvect[AXIS_Y] * pIntBD->Vvect[AXIS_Y]
                + pIntBD->Vvect[AXIS_Z] * pIntBD->Vvect[AXIS_Z])),
                convMatrix);
            csVectConversion(elemDetachVvect, convMatrix);

            /// Current missile air velocity in Normal CS recalculation
            pIntBD->Vvect[AXIS_X] += elemDetachVvect[AXIS_X];
            pIntBD->Vvect[AXIS_Y] += elemDetachVvect[AXIS_Y];
            pIntBD->Vvect[AXIS_Z] += elemDetachVvect[AXIS_Z];

            /// Getting missile way velocity back
            sum2vect(pIntBD->Vvect, pIntBD->Uvect, pIntBD->Wvect);
        }

        /// Initial integration step determination
        pIntBD->hCurr = integrStepCalc(pInpBD, pIntBD);

        /// Current stage begin DESSV memorizing
        equArr(pIntBD->currStageBeginDESSV, pIntBD->currDESSV,
            cDiffEquNumber);

        /// Stage proceeding
        while (!isStageCompleted(pInpBD, pIntBD)) {

#if CYCLE_BALLIST
        for (pIntBD->_cycleIntegrStepCounter = 0;
            pIntBD->_cycleIntegrStepCounter <
            pIntBD->_maxStepNumberPerCycle; pIntBD->_cycleIntegrStepCounter++) {
#endif
            /// Previous step's values memorizing
            equArr(pIntBD->prevDESSV, pIntBD->currDESSV, cDiffEquNumber);

            pIntBD->prevTime = pIntBD->currTime;
            pIntBD->hPrev = pIntBD->hCurr;

            pIntBD->prevCalcCompleteStageParam =
                pIntBD->currCalcCompleteStageParam;

            /// R-K integration
            /// ... for normalized cx0 coefficient
            basic_RK4integrRDC(pIntBD);
            _pAxList->append(pIntBD->currDESSV[3]);
            _pAyList->append(pIntBD->currDESSV[4]);
            _pAzList->append(pIntBD->currDESSV[5]);

//            _pAxList->append(
//                _p930mBallDataList->at(5)->at(pIntBD->integrStepCounter));
//            _pAyList->append(
//                _p930mBallDataList->at(6)->at(pIntBD->integrStepCounter));
//            _pAzList->append(
//                _p930mBallDataList->at(7)->at(pIntBD->integrStepCounter));

//            /// ... for unnormalized cx0 coefficient
//            if (stageNumber == 0) {
//                basic_RK4integrRDC(_DESSVprevStep, _DESSVcurrStep, pRPSV, _vT,
//                    _vg, _vRo, _vaN, _vM, _currUHCS,
//                    //&_pSingleStageShell->stageBallCharact
//                    //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                    &_pTripleStageShell->stageBallCharact[stageNumber]
//                    , _vtPrevStageDuration, _vtPrev, _vtCurr,
//                    arrValLinInterpol(_vM, s8_kl_cMachArr,
//                    s8_kl_cCx0activePartArr, s8_kl_cArrSize), s8_kl_cd,
//                    _equNumber, _k1, _k2, _k3, _k4, _hCurr);
//            }
//            else if (stageNumber == 1) {
//                basic_RK4integrRDC(_DESSVprevStep, _DESSVcurrStep, pRPSV, _vT,
//                    _vg, _vRo, _vaN, _vM, _currUHCS,
//                    //&_pSingleStageShell->stageBallCharact
//                    //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                    &_pTripleStageShell->stageBallCharact[stageNumber]
//                    , _vtPrevStageDuration, _vtPrev, _vtCurr,
//                    arrValLinInterpol(_vM, s8_kl_cMachArr,
//                    s8_kl_cCx0passivePartArr, s8_kl_cArrSize), s8_kl_cd,
//                    _equNumber, _k1, _k2, _k3, _k4, _hCurr);
//            }
//            else {
//                basic_RK4integrRDC(_DESSVprevStep, _DESSVcurrStep, pRPSV, _vT,
//                    _vg, _vRo, _vaN, _vM, _currUHCS,
//                    //&_pSingleStageShell->stageBallCharact
//                    //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                    &_pTripleStageShell->stageBallCharact[stageNumber]
//                    , _vtPrevStageDuration, _vtPrev, _vtCurr,
//                    arrValLinInterpol(_vM, s8_kl_cMachArrElem,
//                    s8_kl_cCx0arrElem, s8_kl_cArrSizeElem), s8_kl_cdElem,
//                    _equNumber, _k1, _k2, _k3, _k4, _hCurr);
//            }

//            basic_RKintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr,
//                _equNumber, _vcx, _vg, _currUHCS);

////            if (!_integrStepCount) {
////                basic_RKintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr,
////                    _equNumber, _vcx, _vg);
////            }
////            else {
////                basic_ARK4_4integr(_DESSVprevStep, _DESSVcurrStep, _k1, _k2,
////                    _k3, _k4, _hCurr, _equNumber, _vcx, _vg);
////            }

////            basic_RKmodifVarStepIntegr(_DESSVcurrStep, _hCurr, 50.0,
////                _equNumber, THE_5TH_ORDER, DORMAND_PRINCE, _vcx, _vg);

////            basic_RKMintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _hCurr,
////                0.00001, equNumber, _vcx, _vg);

////            basic_RKFintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _k6,
////                _hCurr, 10.0, _equNumber, _vcx, _vg);

//            /// Wind recalculation
//            gertmansWindModel(_DESSVcurrStep[4], _currUHCS);

//            /// Bullet way velocity in Normal CS vector
//            pIntBD->_Wvect[AXIS_X] = pIntBD->_currDESSV[0];
//            pIntBD->_Wvect[AXIS_Y] = pIntBD->_currDESSV[1];
//            pIntBD->_Wvect[AXIS_Z] = pIntBD->_currDESSV[2];

//            /// Getting shell air velocity
//            subtract2vect(_currWCS, _currUHCS, currShellVvect);

////            subtract2vect(_currWCS, _prevUHCS, _currWCS);
////            sum2Vect(_currWCS, _currUHCS, _currWCS);

////            _DESSVcurrStep[0] = _currWCS[AXIS_X];
////            _DESSVcurrStep[1] = _currWCS[AXIS_Y];
////            _DESSVcurrStep[2] = _currWCS[AXIS_Z];

//            currShellPosHCS[AXIS_X] = _DESSVcurrStep[3];
//            currShellPosHCS[AXIS_Y] = _DESSVcurrStep[4];
//            currShellPosHCS[AXIS_Z] = _DESSVcurrStep[5];

//            /// Atmosphere parameters recalculation
//            _vT = TfH(_DESSVcurrStep[4]);
//            _vg = gfH(_DESSVcurrStep[4]);
//            _vRo = rofH(_DESSVcurrStep[4]);
//            _vaN = aNfH(_DESSVcurrStep[4]);
//            _vM = vValue(currShellVvect) / _vaN;

//            /// Drag law coefficient recalculation from normalized cx0
//            /// coefficient
//            _vcx = genCx(//&_pSingleStageShell->stageBallCharact
//                //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                &_pTripleStageShell->stageBallCharact[stageNumber]
//                , _vtPrevStageDuration, _vtCurr, arrValLinInterpol(_vM,
//                cMachArr, cStandDragLawArr[0], cArrSize), _vRo,
//                roCorr, vValue(currShellVvect));

//            /// Drag law coefficient recalculation from unnormalized cx0
//            /// coefficient
//            if (stageNumber == 0) {
//                _vcx = genCx(//&_pSingleStageShell->stageBallCharact
//                    //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                    &_pTripleStageShell->stageBallCharact[stageNumber]
//                    , _vtPrevStageDuration, _vtCurr, arrValLinInterpol(_vM,
//                    s8_kl_cMachArr, s8_kl_cCx0activePartArr, s8_kl_cArrSize),
//                    _vRo, vValue(_currWCS), s8_kl_cd);
//            }
//            else if (stageNumber == 1) {
//                _vcx = genCx(//&_pSingleStageShell->stageBallCharact
//                    //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                    &_pTripleStageShell->stageBallCharact[stageNumber]
//                    , _vtPrevStageDuration, _vtCurr, arrValLinInterpol(_vM,
//                    s8_kl_cMachArr, s8_kl_cCx0passivePartArr, s8_kl_cArrSize),
//                    _vRo, vValue(_currWCS), s8_kl_cd);
//            }
//            else {
//                _vcx = genCx(//&_pSingleStageShell->stageBallCharact
//                    //&_pDoubleStageShell->stageBallCharact[stageNumber]
//                    &_pTripleStageShell->stageBallCharact[stageNumber]
//                    , _vtPrevStageDuration, _vtCurr, arrValLinInterpol(_vM,
//                    s8_kl_cMachArrElem, s8_kl_cCx0arrElem, s8_kl_cArrSizeElem),
//                    _vRo, vValue(_currWCS), s8_kl_cdElem);
//            }

            /// Output data
            itemRowNumber++;
            fillBallCalcResTableString(itemRowNumber, pIntBD);
#if CYCLE_BALLIST
            /// Cycle counter
            ui->ballCalcResTableWidget->setItem(itemRowNumber, 11,
                new QTableWidgetItem(QString::number(pIntBD->_cycleCounter)));
            /// Intergration step counter in cycle
            ui->ballCalcResTableWidget->setItem(itemRowNumber, 12,
                new QTableWidgetItem(QString::number(
                pIntBD->_cycleIntegrStepCounter)));

            if ((pIntBD->_maxStepNumberPerCycle * pIntBD->_cycleCounter
                + pIntBD->_cycleIntegrStepCounter > pIntBD->_maxStepNumber)
#else
            /// Step number exceeding checking
            if ((pIntBD->integrStepCounter > pIntBD->maxStepNumber)
#endif
                && (pInpBD->initIntegrStep <= 0.0)) {
                pIntBD->ballistReliability = false;
                break;
            }

            /// Going to the next integration step
            pIntBD->integrStepCounter++;

            /// Integration step value correction
            pIntBD->hCurr = postnikovIntegrStepCorr(pInpBD, pIntBD);

#if CYCLE_BALLIST
            if (isStageCompleted(pInpBD, pIntBD)) {
                break;
            }
        }
        pIntBD->_cycleCounter++;
#endif
        }

        if ((pIntBD->integrStepCounter <= pIntBD->maxStepNumber)
            || (pInpBD->initIntegrStep > 0.0)) {
            preciseStageCompleting(pInpBD, pIntBD);
            _pAxList->removeLast();
            _pAyList->removeLast();
            _pAzList->removeLast();

            _pAxList->append(pIntBD->currDESSV[3]);
            _pAyList->append(pIntBD->currDESSV[4]);
            _pAzList->append(pIntBD->currDESSV[5]);

//            _pAxList->append(
//                _p930mBallDataList->at(5)->at(pIntBD->integrStepCounter));
//            _pAyList->append(
//                _p930mBallDataList->at(6)->at(pIntBD->integrStepCounter));
//            _pAzList->append(
//                _p930mBallDataList->at(7)->at(pIntBD->integrStepCounter));
        }
    }

    /// Output data
    itemRowNumber++;
    fillBallCalcResTableString(itemRowNumber, pIntBD);
#if CYCLE_BALLIST
    /// Cycle counter
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 11,
        new QTableWidgetItem(QString::number(pIntBD->_cycleCounter)));
    /// Intergration step counter in cycle
    ui->ballCalcResTableWidget->setItem(itemRowNumber, 12,
        new QTableWidgetItem(QString::number(pIntBD->_cycleIntegrStepCounter)));
#endif


//    //**************************************************************************
//    /// VVA ballistics calculation

//    ui->ballCalcResTableWidget->setColumnCount(18);

//    QList<QString>* pqls = new QList<QString>;
//    pqls->append("v");
//    pqls->append("wx");
//    pqls->append("wy");
//    pqls->append("wz");
//    pqls->append("lambda");
//    pqls->append("phi");
//    pqls->append("x");
//    pqls->append("y");
//    pqls->append("z");
//    pqls->append("omegaX");
//    pqls->append("omegaY");
//    pqls->append("omegaZ");
//    pqls->append("alpha");
//    pqls->append("beta");
//    pqls->append("dBeta");
//    pqls->append("omegaXa");
//    pqls->append("vcx");
//    pqls->append("h");

//    ui->ballCalcResTableWidget->setHorizontalHeaderLabels(*pqls);
//    this->resize(1920, 720);

//    /// Ballistic and drag law assignments (VVA)
//    _vcx = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr, ccx0Arr,
//                             cVVAarrSize);

//    _vcxSqDelta = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                    ccxSqDeltaArr, cVVAarrSize);
//    _vcyDelta = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                  ccyDeltaArr, cVVAarrSize);
//    _vcMdelta = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                  ccMdeltaArr, cVVAarrSize);
//    _vmx1Omegax1 = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                     cmx1Omegax1Arr, cVVAarrSize);
//    _vmz1Omegaz1 = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                     cmz1Omegaz1Arr, cVVAarrSize);
//    _vmz1Delta = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                   cmz1DeltaArr, cVVAarrSize);
//    _vmMdelta = arrValLinInterpol(vValue(_prevWCS)/*_DESSVcurrStep[0]*/ / _vaN, cVVAmachArr,
//                                  cmMdeltaArr, cVVAarrSize);

//    currShellPosHCS[AXIS_X] = _DESSVcurrStep[3];
//    currShellPosHCS[AXIS_Y] = _DESSVcurrStep[4];
//    currShellPosHCS[AXIS_Z] = _DESSVcurrStep[5];

//    _currWCS[AXIS_X] = _DESSVcurrStep[0] * cos(_DESSVcurrStep[2]) *
//                       cos(_DESSVcurrStep[1]);
//    _currWCS[AXIS_Y] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[1]);
//    _currWCS[AXIS_Z] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[2]) *
//                       cos(_DESSVcurrStep[1]);
//    sum2Vect(_currWCS, _currUHCS, _currWCS);

//    _hCurr = _hPrev = 0.001;
//    _integrStepCount = 0;

//    /// Output data
//    /// Air velocity
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 0,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[0])));
//    /// X axis way velocity projection
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 1,
//        new QTableWidgetItem(QString::number(_currWCS[AXIS_X])));
//    /// Y axis way velocity projection
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 2,
//        new QTableWidgetItem(QString::number(_currWCS[AXIS_Y])));
//    /// Z axis way velocity projection
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 3,
//        new QTableWidgetItem(QString::number(_currWCS[AXIS_Z])));
//    /// Trajectory slope angle (lambda)
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 4,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[1])));
//    /// Way angle (phi)
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 5,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[2])));
//    /// X axis coordinate projection in Normal CS
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 6,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[3])));
//    /// Y axis coordinate projection in Normal CS
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 7,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[4])));
//    /// Z axis coordinate projection in Normal CS
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 8,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[5])));
//    /// X axis angle speed projection in Connected CS
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 9,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[6])));
//    /// Y axis angle speed projection in Connected CS
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 10,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[7])));
//    /// Z axis angle speed projection in Connected CS
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 11,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[8])));
//    /// Attack angle (alpha)
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 12,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[9])));
//    /// Slide angle (beta)
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 13,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[10])));
//    /// Slide angle derivative (dBeta)
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 14,
//        new QTableWidgetItem(QString::number(
//                                 vva_dBetaArticle(
//                                     _DESSVcurrStep[9], _DESSVcurrStep[7],
//                                     vva_dPhiArticle(_DESSVcurrStep[1],
//                                                     _vcyDelta, _vRo,
//                                                     _DESSVcurrStep[0],
//                                                     _DESSVcurrStep[10],
//                                                     _vcMdelta,
//                                                     _DESSVcurrStep[6],
//                                                     _DESSVcurrStep[9]),
//                                     _DESSVcurrStep[1], _DESSVcurrStep[10],
//                                     vva_dLambdaArticle(_vcyDelta, _vRo,
//                                                        _DESSVcurrStep[0],
//                                                        _DESSVcurrStep[9],
//                                                        _vcMdelta,
//                                                        _DESSVcurrStep[6],
//                                                        _DESSVcurrStep[10], _vg,
//                                                        _DESSVcurrStep[1])))));
//    /// OmegaXa
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 15,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[11])));
//    /// Basic drag law coefficient
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 16,
//        new QTableWidgetItem(QString::number(_vcx)));
////    ui->ballCalcResTableWidget->setItem(_integrStepCount, 11,
////        new QTableWidgetItem(QString::number(arrValLinInterpol(
////                                                 _DESSVcurrStep[0] / _vaN,
////                                                 cMachArr, cStandDragLawArr,
////                                                 cArrSize))));
//    /// Integration step value
//    ui->ballCalcResTableWidget->setItem(_integrStepCount, 17,
//        new QTableWidgetItem(QString::number(_hPrev)));

//    /// Integration loop
//    while (currShellPosHCS[AXIS_Y] > 0.0)
//    {
//        /// R-K integration
////        vva_RKintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr, _vcx,
////                    _vcxSqDelta, _vcyDelta, _vcMdelta, _vmx1Omegax1, _vmz1Delta,
////                    _vmz1Omegaz1, _vmMdelta, _vRo, _vg, 0.0, 0.0,
////                    _DESSVcurrStep[4]);

////        vva_RKintegrArticle(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr, _vcx,
////                            _vcxSqDelta, _vcyDelta, _vcMdelta, _vmx1Omegax1,
////                            _vmz1Delta, _vmz1Omegaz1, _vmMdelta, _vRo, _vg);

////        vva_RKMintegrArticle(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _hCurr,
////                             0.0001, 11, _vcx, _vcxSqDelta, _vcyDelta,
////                             _vcMdelta, _vmx1Omegax1,  _vmz1Delta, _vmz1Omegaz1,
////                             _vmMdelta, _vRo, _vg);

////        vva_RKFintegrArticle(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _k6,
////                             _hCurr, 0.000001, 11, _vcx, _vcxSqDelta, _vcyDelta,
////                             _vcMdelta, _vmx1Omegax1,  _vmz1Delta, _vmz1Omegaz1,
////                             _vmMdelta, _vRo, _vg);

////        vva_RKDPintegrArticle(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _k6, _k7,
////                              _hCurr, 0.00001, 11, _vcx, _vcxSqDelta, _vcyDelta,
////                              _vcMdelta, _vmx1Omegax1,  _vmz1Delta, _vmz1Omegaz1,
////                              _vmMdelta, _vRo, _vg);

////        vva_RKCKintegrArticle(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _k6,
////                              _hCurr, 0.0001, 11, _vcx, _vcxSqDelta, _vcyDelta,
////                              _vcMdelta, _vmx1Omegax1,  _vmz1Delta, _vmz1Omegaz1,
////                              _vmMdelta, _vRo, _vg);

//        vva_RKintegrMassCenter(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr, _vcx,
//                               _vRo, _vg, 0.0, 0.0);

////        vva_RKMintegrMassCenter(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _hCurr,
////                                0.00001, 6, _vcx, _vRo, _vg, 0.0, 0.0);

////        vva_RKFintegrMassCenter(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _k6,
////                                _hCurr, 0.00001, 6, _vcx, _vRo, _vg, 0.0, 0.0);

////        vva_RKDPintegrMassCenter(_DESSVcurrStep, _k1, _k2, _k3, _k4, _k5, _k6,
////                                 _k7, _hCurr, 0.001, 6, _vcx, _vRo, _vg, 0.0,
////                                 0.0);

//        /// Output data
//        /// Air velocity
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 0,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[0])));
//        /// X axis way velocity projection
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 1,
//            new QTableWidgetItem(QString::number(_currWCS[AXIS_X])));
//        /// Y axis way velocity projection
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 2,
//            new QTableWidgetItem(QString::number(_currWCS[AXIS_Y])));
//        /// Z axis way velocity projection
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 3,
//            new QTableWidgetItem(QString::number(_currWCS[AXIS_Z])));
//        /// Trajectory slope angle (lambda)
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 4,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[1])));
//        /// Way angle (phi)
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 5,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[2])));
//        /// X axis coordinate projection in Normal CS
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 6,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[3])));
//        /// Y axis coordinate projection in Normal CS
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 7,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[4])));
//        /// Z axis coordinate projection in Normal CS
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 8,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[5])));
//        /// X axis angle speed projection in Connected CS
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 9,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[6])));
//        /// Y axis angle speed projection in Connected CS
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 10,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[7])));
//        /// Z axis angle speed projection in Connected CS
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 11,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[8])));
//        /// Attack angle (alpha)
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 12,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[9])));
//        /// Slide angle (beta)
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 13,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[10])));
//        /// Slide angle derivative (dBeta)
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 14,
//            new QTableWidgetItem(QString::number(
//                                     vva_dBetaArticle(
//                                         _DESSVcurrStep[9], _DESSVcurrStep[7],
//                                         vva_dPhiArticle(_DESSVcurrStep[1],
//                                                         _vcyDelta, _vRo,
//                                                         _DESSVcurrStep[0],
//                                                         _DESSVcurrStep[10],
//                                                         _vcMdelta,
//                                                         _DESSVcurrStep[6],
//                                                         _DESSVcurrStep[9]),
//                                         _DESSVcurrStep[1], _DESSVcurrStep[10],
//                                         vva_dLambdaArticle(_vcyDelta, _vRo,
//                                                            _DESSVcurrStep[0],
//                                                            _DESSVcurrStep[9],
//                                                            _vcMdelta,
//                                                            _DESSVcurrStep[6],
//                                                            _DESSVcurrStep[10],
//                                                            _vg,
//                                                         _DESSVcurrStep[1])))));
//        /// OmegaXa
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 15,
//            new QTableWidgetItem(QString::number(_DESSVcurrStep[11])));
//        /// Basic drag law coefficient
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 16,
//            new QTableWidgetItem(QString::number(_vcx)));
//    //    ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 11,
//    //        new QTableWidgetItem(QString::number(arrValLinInterpol(
//    //                                                 _DESSVcurrStep[0] / _vaN,
//    //                                                 cMachArr, cStandDragLawArr,
//    //                                                 cArrSize))));
//        /// Integration step value
//        ui->ballCalcResTableWidget->setItem(_integrStepCount + 2, 17,
//            new QTableWidgetItem(QString::number(_hPrev)));

//        if (_integrStepCount >= maxStepCount())
//            break;

//        /// Current shell way velocity in HCS gaining
//        _currWCS[AXIS_X] = _DESSVcurrStep[0] * cos(_DESSVcurrStep[2]) *
//                           cos(_DESSVcurrStep[1]);
//        _currWCS[AXIS_Y] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[1]);
//        _currWCS[AXIS_Z] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[2]) *
//                           cos(_DESSVcurrStep[1]);
//        sum2Vect(_currWCS, _currUHCS, _currWCS);

//        /// Current shell position in HCS gaining
//        currShellPosHCS[AXIS_X] = _DESSVcurrStep[3];
//        currShellPosHCS[AXIS_Y] = _DESSVcurrStep[4];
//        currShellPosHCS[AXIS_Z] = _DESSVcurrStep[5];

//        /// Atmosphere parameters recalculation
//        _vT = TfH(currShellPosHCS[AXIS_Y]);
//        _vg = gfH(currShellPosHCS[AXIS_Y]);
//        _vRo = rofH(currShellPosHCS[AXIS_Y]);
//        _vaN = aNfH(currShellPosHCS[AXIS_Y]);

//        /// Ballistic and drag law parameters recalculation
//        _vcx = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr, ccx0Arr,
//                                 cVVAarrSize);
////        _vcx = genCx(&_pSingleStageShell->stageBallCharact, 0.0, _vtCurr,
////                     arrValLinInterpol(_DESSVcurrStep[0] / _vaN,
////                                       cMachArr, cStandDragLawArr, cArrSize), _vRo, _DESSVcurrStep[0]);
//        _vcxSqDelta = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                        ccxSqDeltaArr, cVVAarrSize);
//        _vcyDelta = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                      ccyDeltaArr, cVVAarrSize);
//        _vcMdelta = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                      ccMdeltaArr, cVVAarrSize);
//        _vmx1Omegax1 = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                         cmx1Omegax1Arr, cVVAarrSize);
//        _vmz1Omegaz1 = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                         cmz1Omegaz1Arr, cVVAarrSize);
//        _vmz1Delta = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                       cmz1DeltaArr, cVVAarrSize);
//        _vmMdelta = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, cVVAmachArr,
//                                      cmMdeltaArr, cVVAarrSize);

//        /// Going to the next integration step
//        equArr(_DESSVprevStep, _DESSVcurrStep, cDiffEquCount);
//        setDiffEquSystemStateVector(_DESSVcurrStep);
//        _vtCurr += _hCurr;
//        _vtPrev = _vtCurr;
//        _hPrev = _hCurr;

//        _integrStepCount++;
//    }


//    //**************************************************************************
//    /// S8-KL ballistics calculation

//    ui->ballCalcResTableWidget->setColumnCount(16);

//    QList<QString>* pqls = new QList<QString>;
//    pqls->append("v");
//    pqls->append("tetta");
//    pqls->append("psi");
//    pqls->append("x");
//    pqls->append("y");
//    pqls->append("z");
//    pqls->append("omegaX");
//    pqls->append("omegaY");
//    pqls->append("omegaZ");
//    pqls->append("pitch");
//    pqls->append("yaw");
//    pqls->append("roll");
//    pqls->append("alpha");
//    pqls->append("beta");
//    pqls->append("vcx");
//    pqls->append("h");

//    ui->ballCalcResTableWidget->setHorizontalHeaderLabels(*pqls);
//    this->resize(1920, 720);

//    /// Ballistic and drag law assignments (S8-KL)
//    _vcx = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, s8_kl_cMachArr,
//        s8_kl_cCx0activePartArr, s8_kl_cArrSize);
//    _vcyAlpha = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, s8_kl_cMachArr,
//        s8_kl_cCyAlphaArr, s8_kl_cArrSize);
//    _vMinusMzAlpha = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, s8_kl_cMachArr,
//        s8_kl_cMinusMzAlphaActivePartArr, s8_kl_cArrSize);
//    _vMinusMzOmegaLineZ = arrValLinInterpol(_DESSVcurrStep[0] / _vaN,
//        s8_kl_cMachArr, s8_kl_cMinusMzOmegaLineZactivePartArr, s8_kl_cArrSize);
//    _vmx = arrValLinInterpol(_DESSVcurrStep[0] / _vaN, s8_kl_cMachArr,
//        s8_kl_cMxArr, s8_kl_cArrSize);
//    _vMinusMxOmegaLineX = arrValLinInterpol(_DESSVcurrStep[0] / _vaN,
//        s8_kl_cMachArr, s8_kl_cMinusMxOmegaLineXarr, s8_kl_cArrSize);

//    currShellPosHCS[AXIS_X] = _DESSVcurrStep[3];
//    currShellPosHCS[AXIS_Y] = _DESSVcurrStep[4];
//    currShellPosHCS[AXIS_Z] = _DESSVcurrStep[5];

//    _currWCS[AXIS_X] = _DESSVcurrStep[0] * cos(_DESSVcurrStep[2]) *
//                       cos(_DESSVcurrStep[1]);
//    _currWCS[AXIS_Y] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[1]);
//    _currWCS[AXIS_Z] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[2]) *
//                       cos(_DESSVcurrStep[1]);
//    sum2Vect(_currWCS, _currUHCS, _currWCS);

//    _integrStepCount = 0;
//    itemRowNumber = _integrStepCount;
//    stageCount = 3;
//    _equNumber = 12;

//    /// Attack and slide angle equations without roll and X axis rotation
//    /// considering
//    double vAlpha = s8_kl_alpha(_DESSVcurrStep[9]);
//    double vBeta = s8_kl_beta(_DESSVcurrStep[10], _DESSVcurrStep[2]);

////    /// Attack and slide angle equations with roll and X axis rotation
////    /// considering
////    /// Equations 1 and 2
////    double vBeta = s8_kl_beta(_DESSVcurrStep[1], _DESSVcurrStep[2],
////        _DESSVcurrStep[10], _DESSVcurrStep[9], _DESSVcurrStep[11]);
////    double vAlpha = s8_kl_alpha(vBeta, _DESSVcurrStep[1], _DESSVcurrStep[9]);

////    /// Equations 1 and 3
////    double vAlpha = s8_kl_alpha(_DESSVcurrStep[9], _DESSVcurrStep[11],
////        _DESSVcurrStep[1]);
////    double vBeta = s8_kl_beta(_DESSVcurrStep[9], _DESSVcurrStep[11],
////        _DESSVcurrStep[1]);
//    double vq = s8_kl_q(_vRo, _DESSVcurrStep[0]);
//    double vdCurrStage = s8_kl_cd;
//    double vlCurrStage = s8_kl_cl;
//    double vmCurrStage = s8_kl_cm;
//    double vJxCurrStage = s8_kl_cJxActiveStage;
//    double vJzCurrStage = s8_kl_cJzActiveStage;
//    double vS = M_PI * vdCurrStage * vdCurrStage / 4.0;

//    /// Output data
//    /// Air velocity
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 0,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[0])));
//    /// Trajectory slope angle (tetta)
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 1,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[1])));
//    /// Way angle (psi)
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 2,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[2])));
//    /// X axis coordinate projection in Normal CS
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 3,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[3])));
//    /// Y axis coordinate projection in Normal CS
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 4,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[4])));
//    /// Z axis coordinate projection in Normal CS
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 5,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[5])));
//    /// X axis angle speed projection in Connected CS
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 6,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[6])));
//    /// Y axis angle speed projection in Connected CS
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 7,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[7])));
//    /// Z axis angle speed projection in Connected CS
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 8,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[8])));
//    /// Pitch angle
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 9,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[9])));
//    /// Yaw angle
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 10,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[10])));
//    /// Roll angle
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 11,
//        new QTableWidgetItem(QString::number(_DESSVcurrStep[11])));
//    /// Attack angle (alpha)
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 12,
//        new QTableWidgetItem(QString::number(vAlpha)));
//    /// Slide angle (beta)
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 13,
//        new QTableWidgetItem(QString::number(vBeta)));
//    /// Basic drag law coefficient
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 14,
//        new QTableWidgetItem(QString::number(_vcx)));
//    /// Integration step value
//    ui->ballCalcResTableWidget->setItem(itemRowNumber, 15,
//        new QTableWidgetItem(QString::number(_hPrev)));

//    /// Integration loop
//    for (int stageNumber = 0; stageNumber < stageCount; stageNumber++) {
//        itemRowNumber = _integrStepCount + stageNumber + 1;
//        ui->ballCalcResTableWidget->setItem(itemRowNumber, 0,
//            new QTableWidgetItem("Stage " + QString::number(stageNumber + 1)));

//        if (!stageNumber) {
//            _vtCurr = _pTripleStageShell->stageBallCharact[0].barrelTime;
//            _vtPrevStageDuration = 0.0;
//        }

//        if (stageNumber) {
//            _vtPrevStageDuration = _vtCurr;
//        }

//        s8_kl_stageBallistParamsCalc(stageNumber, _vM, _vtCurr,
//            _vtPrevStageDuration,
//            _pTripleStageShell->stageBallCharact[0].massConsumpt, _vcx,
//            _vcyAlpha, _vMinusMzAlpha, _vMinusMzOmegaLineZ, _vmx,
//            _vMinusMxOmegaLineX, vdCurrStage, vlCurrStage, vmCurrStage,
//            vJxCurrStage, vJzCurrStage);

//        while (!isStageCompleted(
//            &_pTripleStageShell->stageBallCharact[stageNumber],
//            _vtPrevStageDuration, _vtCurr, _initTargetPosHCS[AXIS_Y],
//            currShellPosHCS, _currWCS, _initAppPosHCS, _currUHCS,
//            _currCalcCompleteStagePar)) {

////            /// Integration step determination
////            _hCurr = integrStepCalc(
////                &_pTripleStageShell->stageBallCharact[stageNumber],
////                _pTripleStageShell->type, _DESSVcurrStep[4],
////                cPrecededDistance, _hDef, _hMin, _hMax);
////            _hCurr = postnikovIntegrStepCorr(
////                &_pTripleStageShell->stageBallCharact[stageNumber],
////                _vtPrevStageDuration, _vtPrev, _equNumber, _k1, _k3, _k4,
////                _hCurr, _hMin, _hMax);

////            /// R-K integration without roll and X axis rotation considering
////            s8_kl_RKintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr,
////                _equNumber,
////                _pTripleStageShell->stageBallCharact[stageNumber].enginePower,
////                s8_kl_X(_vcx, _vcyAlpha, vAlpha, vBeta, vq, vS),
////                s8_kl_Y(_vcyAlpha, vAlpha, vq, vS), s8_kl_Z(-_vcyAlpha, vBeta,
////                vq, vS), vAlpha, vBeta, -_vMinusMzOmegaLineZ,
////                s8_kl_omegaLine(_DESSVcurrStep[7], vlCurrStage,
////                _DESSVcurrStep[0]), s8_kl_omegaLine(_DESSVcurrStep[8],
////                vlCurrStage, _DESSVcurrStep[0]), -_vMinusMzAlpha,
////                -_vMinusMzAlpha, vS, vmCurrStage, vlCurrStage, vJzCurrStage,
////                _vg, _vRo, _currUHCS);

//            s8_kl_RKmodifVarStepIntegr(_DESSVcurrStep, _hCurr, 1.0, _equNumber,
//                THE_5TH_ORDER, FEHLBERG,
//                _pTripleStageShell->stageBallCharact[stageNumber].enginePower,
//                s8_kl_X(_vcx, _vcyAlpha, vAlpha, vBeta, vq, vS),
//                s8_kl_Y(_vcyAlpha, vAlpha, vq, vS), s8_kl_Z(-_vcyAlpha, vBeta,
//                vq, vS), vAlpha, vBeta, -_vMinusMzOmegaLineZ,
//                s8_kl_omegaLine(_DESSVcurrStep[7], vlCurrStage,
//                _DESSVcurrStep[0]), s8_kl_omegaLine(_DESSVcurrStep[8],
//                vlCurrStage, _DESSVcurrStep[0]), -_vMinusMzAlpha,
//                -_vMinusMzAlpha, vS, vmCurrStage, vlCurrStage, vJzCurrStage,
//                _vg, _vRo, _currUHCS);

////            s8_kl_LobattoIIIAintegr(_DESSVcurrStep, _hCurr, 100.0, _equNumber,
////                _pTripleStageShell->stageBallCharact[stageNumber].enginePower,
////                s8_kl_X(_vcx, _vcyAlpha, vAlpha, vBeta, vq, vS),
////                s8_kl_Y(_vcyAlpha, vAlpha, vq, vS), s8_kl_Z(-_vcyAlpha, vBeta,
////                vq, vS), vAlpha, vBeta, -_vMinusMzOmegaLineZ,
////                s8_kl_omegaLine(_DESSVcurrStep[7], vlCurrStage,
////                _DESSVcurrStep[0]), s8_kl_omegaLine(_DESSVcurrStep[8],
////                vlCurrStage, _DESSVcurrStep[0]), -_vMinusMzAlpha,
////                -_vMinusMzAlpha, vS, vmCurrStage, vlCurrStage, vJzCurrStage,
////                _vg, _vRo, _currUHCS);

////            /// R-K integration with roll and X axis rotation considering
////            s8_kl_RKintegr(_DESSVcurrStep, _k1, _k2, _k3, _k4, _hCurr,
////                _pTripleStageShell->stageBallCharact[stageNumber].enginePower,
////                s8_kl_X(_vcx, _vcyAlpha, vAlpha, vBeta, vq, vS),
////                s8_kl_Y(_vcyAlpha, vAlpha, vq, vS), s8_kl_Z(-_vcyAlpha, vBeta,
////                vq, vS), vAlpha, vBeta, _vmx, -_vMinusMxOmegaLineX,
////                -_vMinusMzOmegaLineZ, s8_kl_omegaLine(_DESSVcurrStep[6],
////                vlCurrStage, _DESSVcurrStep[0]),
////                s8_kl_omegaLine(_DESSVcurrStep[7], vlCurrStage,
////                _DESSVcurrStep[0]), s8_kl_omegaLine(_DESSVcurrStep[8],
////                vlCurrStage, _DESSVcurrStep[0]), -_vMinusMzAlpha,
////                -_vMinusMzAlpha, vS, vmCurrStage, vlCurrStage, vJxCurrStage,
////                vJzCurrStage, _vg, _vRo, _currUHCS);

////            s8_kl_RKmodifVarStepIntegr(_DESSVcurrStep, _hCurr, 1.0, _equNumber,
////                THE_5TH_RANK, MERSON,
////                _pTripleStageShell->stageBallCharact[stageNumber].enginePower,
////                s8_kl_X(_vcx, _vcyAlpha, vAlpha, vBeta, vq, vS),
////                s8_kl_Y(_vcyAlpha, vAlpha, vq, vS), s8_kl_Z(-_vcyAlpha, vBeta,
////                vq, vS), vAlpha, vBeta, _vmx, -_vMinusMxOmegaLineX,
////                -_vMinusMzOmegaLineZ, s8_kl_omegaLine(_DESSVcurrStep[6],
////                vlCurrStage, _DESSVcurrStep[0]),
////                s8_kl_omegaLine(_DESSVcurrStep[7], vlCurrStage,
////                _DESSVcurrStep[0]), s8_kl_omegaLine(_DESSVcurrStep[8],
////                vlCurrStage, _DESSVcurrStep[0]), -_vMinusMzAlpha,
////                -_vMinusMzAlpha, vS, vmCurrStage, vlCurrStage, vJxCurrStage,
////                vJzCurrStage, _vg, _vRo, _currUHCS);

//            itemRowNumber++;
//            /// Output data
//            /// Air velocity
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 0,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[0])));
//            /// Trajectory slope angle (tetta)
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 1,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[1])));
//            /// Way angle (psi)
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 2,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[2])));
//            /// X axis coordinate projection in Normal CS
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 3,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[3])));
//            /// Y axis coordinate projection in Normal CS
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 4,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[4])));
//            /// Z axis coordinate projection in Normal CS
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 5,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[5])));
//            /// X axis angle speed projection in Connected CS
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 6,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[6])));
//            /// Y axis angle speed projection in Connected CS
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 7,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[7])));
//            /// Z axis angle speed projection in Connected CS
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 8,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[8])));
//            /// Pitch angle
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 9,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[9])));
//            /// Yaw angle
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 10,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[10])));
//            /// Roll angle
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 11,
//                new QTableWidgetItem(QString::number(_DESSVcurrStep[11])));
//            /// Attack angle (alpha)
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 12,
//                new QTableWidgetItem(QString::number(vAlpha)));
//            /// Slide angle (beta)
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 13,
//                new QTableWidgetItem(QString::number(vBeta)));
//            /// Basic drag law coefficient
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 14,
//                new QTableWidgetItem(QString::number(_vcx)));
//            /// Integration step value
//            ui->ballCalcResTableWidget->setItem(itemRowNumber, 15,
//                new QTableWidgetItem(QString::number(_hPrev)));

//            /// Wind recalculation
//            windHypothesis(
//                _pTripleStageShell->stageBallCharact[stageNumber].charactSpeed,
//                _pTripleStageShell->stageBallCharact[stageNumber].enginePower,
//                _DESSVcurrStep[4], _DESSVcurrStep[4], _currUHCS);
//            gertmansWindModel(_DESSVcurrStep[4], _currUHCS);

//            /// Current shell way velocity in HCS gaining
//            _currWCS[AXIS_X] = _DESSVcurrStep[0] * cos(_DESSVcurrStep[2])
//                * cos(_DESSVcurrStep[1]);
//            _currWCS[AXIS_Y] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[1]);
//            _currWCS[AXIS_Z] = _DESSVcurrStep[0] * sin(_DESSVcurrStep[2])
//                * cos(_DESSVcurrStep[1]);

//            subtract2vect(_currWCS, _prevUHCS, _currWCS);
//            sum2Vect(_currWCS, _currUHCS, _currWCS);

//            _DESSVcurrStep[0] = vValue(_currWCS);

//            /// Current shell position in HCS gaining
//            currShellPosHCS[AXIS_X] = _DESSVcurrStep[3];
//            currShellPosHCS[AXIS_Y] = _DESSVcurrStep[4];
//            currShellPosHCS[AXIS_Z] = _DESSVcurrStep[5];

//            /// Atmosphere parameters recalculation
//            _vT = TfH(_DESSVcurrStep[4]);
//            _vg = gfH(_DESSVcurrStep[4]);
//            _vRo = rofH(_DESSVcurrStep[4]);
//            _vaN = aNfH(_DESSVcurrStep[4]);
//            _vM = _DESSVcurrStep[0] / _vaN;

//            s8_kl_stageBallistParamsCalc(stageNumber, _vM, _vtCurr,
//                _vtPrevStageDuration,
//                _pTripleStageShell->stageBallCharact[0].massConsumpt, _vcx,
//                _vcyAlpha, _vMinusMzAlpha, _vMinusMzOmegaLineZ, _vmx,
//                _vMinusMxOmegaLineX, vdCurrStage, vlCurrStage, vmCurrStage,
//                vJxCurrStage, vJzCurrStage);

//            /// Attack and slide angle equations without roll and X axis
//            /// rotation considering
//            vAlpha = s8_kl_alpha(_DESSVcurrStep[9]);
//            vBeta = s8_kl_beta(_DESSVcurrStep[10], _DESSVcurrStep[2]);

////            /// Attack and slide angle equations with roll and X axis rotation
////            /// considering
////            /// Equations 1 and 2
////            vBeta = s8_kl_beta(_DESSVcurrStep[1], _DESSVcurrStep[2],
////                _DESSVcurrStep[10], _DESSVcurrStep[9], _DESSVcurrStep[11]);
////            vAlpha = s8_kl_alpha(vBeta, _DESSVcurrStep[1], _DESSVcurrStep[9]);

////            /// Equations 1 and 3
////            vAlpha = s8_kl_alpha(_DESSVcurrStep[9], _DESSVcurrStep[11],
////                _DESSVcurrStep[1]);/*s8_kl_alpha(_DESSVcurrStep[9]/*, _DESSVcurrStep[1]);*/
////            vBeta = s8_kl_beta(_DESSVcurrStep[9], _DESSVcurrStep[11],
////                _DESSVcurrStep[1]);/*s8_kl_beta(_DESSVcurrStep[10], _DESSVcurrStep[2]);*/
//            vq = s8_kl_q(_vRo, _DESSVcurrStep[0]);
//            vS = M_PI * vdCurrStage * vdCurrStage / 4.0;

//            if (isStageCompleted(
//                &_pTripleStageShell->stageBallCharact[stageNumber],
//                _vtPrevStageDuration, _vtCurr, _initTargetPosHCS[AXIS_Y],
//                currShellPosHCS, _currWCS, _initAppPosHCS, _currUHCS,
//                _currCalcCompleteStagePar)
//                || (_integrStepCount >= maxStepCount())) {

//                _vtCurr += _hCurr;
//                _integrStepCount++;
//                break;
//            }

//            /// Going to the next integration step
//            equVect(_prevUHCS, _currUHCS);
//            equVect(_prevWCS, _currWCS);

//            equArr(_DESSVprevStep, _DESSVcurrStep, cDiffEquCount);
//            setDiffEquSystemStateVector(_DESSVcurrStep);

//            _vtCurr += _hCurr;
//            _vtPrev = _vtCurr;
//            _hPrev = _hCurr;
//            _prevCalcCompleteStagePar = _currCalcCompleteStagePar;

//            _integrStepCount++;
//        }
//        itemRowNumber++;
//    }


    ui->ballCalcResTableWidget->setRowCount(itemRowNumber + 1);
    ui->ballCalcResTableWidget->resizeColumnsToContents();
//    ui->ballCalcResTableWidget->adjustSize();
//    this->resize(ui->ballCalcResTableWidget->width(),
//        ui->ballCalcResTableWidget->height());

    drawResultsChart();

    this->show();

    return pIntBD->ballistReliability;
}

void BallCalcResults::drawResultsChart() {
    int xAxisRange = //ui->ballCalcGraphicsView->width() / 2 - 10
        this->width() / 3;
    int yAxisRange = //ui->ballCalcGraphicsView->height() / 2 - 10
        this->height() / 3; // == zAxisRange
//    this->setWindowTitle(QString::number(xAxisRange) + ' '
//        + QString::number(yAxisRange));

    double minAx, maxAx;
    minAx = maxAx = _pAxList->first();
    double minAy, maxAy;
    minAy = maxAy = _pAyList->first();
    double minAz, maxAz;
    minAz = maxAz = _pAzList->first();

    for (int i = 0; i < _pAxList->size(); i++) {
        if (minAx > _pAxList->at(i)) {
            minAx = _pAxList->at(i);
        }
        if (maxAx < _pAxList->at(i)) {
            maxAx = _pAxList->at(i);
        }
        if (minAy > _pAyList->at(i)) {
            minAy = _pAyList->at(i);
        }
        if (maxAy < _pAyList->at(i)) {
            maxAy = _pAyList->at(i);
        }
        if (minAz > _pAzList->at(i)) {
            minAz = _pAzList->at(i);
        }
        if (maxAz < _pAzList->at(i)) {
            maxAz = _pAzList->at(i);
        }
    }

    double xRange = maxAx;
//    xRange -= (minAx < 0.0) ? minAx : 0;
    double yRange = maxAy;
    yRange -= (minAy < 0.0) ? minAy : 0;
    double zRange = maxAz - minAz;
    double xScalingCoeff = xAxisRange, yScalingCoeff/* = yAxisRange / yRange,
        zScalingCoeff*/;
//    if (xRange /*!= 0.0*/ > cZeroTolerance) {
        xScalingCoeff = xAxisRange / xRange;
//    }
//    if (zRange != 0.0/* > cZeroTolerance*/) {
//        zScalingCoeff = yAxisRange / zRange;
//    }
    yScalingCoeff = (yRange > zRange) ? yAxisRange / yRange : yAxisRange
        / zRange;

    QGraphicsScene *pChartScene = new QGraphicsScene(ui->ballCalcGraphicsView);
    QPen pen(Qt::cyan);
//    pen.setWidth(2);

    int XOYxOffset = 0;
    int XOYyOffset = yAxisRange;
    XOYyOffset -= (minAy < 0.0) ? fabs(minAy) * yScalingCoeff : 0;
    /// X axis XOY plane drawing
    pChartScene->addLine(XOYxOffset, XOYyOffset, XOYxOffset + xAxisRange,
        XOYyOffset, pen);
    /// Y axis XOY plane drawing
    pChartScene->addLine(XOYxOffset, yAxisRange, XOYxOffset, 0, pen);

    int XOZxOffset = xAxisRange + 100;
    int XOZzOffset = fabs(minAz) * /*zScalingCoeff*/yScalingCoeff;
    /// X axis XOZ plane drawing
    pChartScene->addLine(XOZxOffset, XOZzOffset, 2 * XOZxOffset - 100,
        XOZzOffset, pen);
    /// Z axis XOZ plane drawing
    pChartScene->addLine(XOZxOffset, 0, XOZxOffset, yAxisRange, pen);

    /// Writings setting
    QGraphicsSimpleTextItem *pYaxisXOYtext = new QGraphicsSimpleTextItem;
    pYaxisXOYtext->setPen(pen);
    pYaxisXOYtext->setText("Y");
    if ((yRange > zRange) && (maxAy == 0.0)) {
        pYaxisXOYtext->moveBy(XOYxOffset - 10, yAxisRange/* - 15*/);
    }
    else {
        pYaxisXOYtext->moveBy(XOYxOffset - 10, 0);
    }
//    pYaxisXOYtext->moveBy(XOYxOffset - 10, 0);
    pChartScene->addItem(pYaxisXOYtext);

    QGraphicsSimpleTextItem *pYinitXOYtext = new QGraphicsSimpleTextItem;
    pYinitXOYtext->setPen(pen);
    pYinitXOYtext->setText(QString::number(_pAyList->first()));
    pYinitXOYtext->moveBy(XOYxOffset + 5, XOYyOffset - _pAyList->first()
        * yScalingCoeff);
    pChartScene->addItem(pYinitXOYtext);

//    QGraphicsSimpleTextItem *pYmaxXOYtext = new QGraphicsSimpleTextItem;
//    pYmaxXOYtext->setPen(pen);
//    pYmaxXOYtext->setText(QString::number(maxAy));
//    pYmaxXOYtext->moveBy(XOYxOffset + 5, XOYyOffset - maxAy * /*zScalingCoeff*/yScalingCoeff);
//    pChartScene->addItem(pYmaxXOYtext);

//    QGraphicsSimpleTextItem *pYminXOYtext = new QGraphicsSimpleTextItem;
//    pYminXOYtext->setPen(pen);
//    pYminXOYtext->setText(QString::number(minAy));
//    pYminXOYtext->moveBy(XOYxOffset + 5, XOYyOffset
//        - pAyList->at(pAyList->size() - 1) * yScalingCoeff);
//    pChartScene->addItem(pYminXOYtext);

    QGraphicsSimpleTextItem *pYfinalXOYtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::green);
    pYfinalXOYtext->setPen(pen);
    pYfinalXOYtext->setText(QString::number(_pAyList->last()));
    pYfinalXOYtext->moveBy(XOYxOffset + 5, XOYyOffset - _pAyList->last()
        * yScalingCoeff);
    pChartScene->addItem(pYfinalXOYtext);
    pen.setStyle(Qt::DashLine);
    pChartScene->addLine(XOYxOffset + xAxisRange, XOYyOffset - _pAyList->last()
        * yScalingCoeff, XOYxOffset, XOYyOffset - _pAyList->last()
        * yScalingCoeff, pen);

    QGraphicsSimpleTextItem *pXaxisXOYtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::cyan);
    pen.setStyle(Qt::SolidLine);
    pXaxisXOYtext->setPen(pen);
    pXaxisXOYtext->setText("X");
    pXaxisXOYtext->moveBy(XOYxOffset + xAxisRange + 5, XOYyOffset);
    pChartScene->addItem(pXaxisXOYtext);

    QGraphicsSimpleTextItem *pXmaxXOYtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::green);
    pXmaxXOYtext->setPen(pen);
    pXmaxXOYtext->setText(QString::number(maxAx));
    pXmaxXOYtext->moveBy(XOYxOffset + xAxisRange + 5/* - pXmaxXOYtext->boundingRect().width() / 2*/,
        XOYyOffset - 15/*pXmaxXOYtext->boundingRect().height() / 2*/);
    pChartScene->addItem(pXmaxXOYtext);
    pen.setStyle(Qt::DashLine);
    pChartScene->addLine(XOYxOffset + xAxisRange, XOYyOffset - _pAyList->last()
        * yScalingCoeff, XOYxOffset + xAxisRange, XOYyOffset, pen);


    QGraphicsSimpleTextItem *pZaxisXOZtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::cyan);
    pen.setStyle(Qt::SolidLine);
    pZaxisXOZtext->setPen(pen);
    pZaxisXOZtext->setText("Z");
    if ((yRange < zRange) && (maxAz == 0.0)) {
        pZaxisXOZtext->moveBy(XOZxOffset - 10, 0);
    }
    else {
        pZaxisXOZtext->moveBy(XOZxOffset - 10, yAxisRange/* - 15*/);
    }
    pChartScene->addItem(pZaxisXOZtext);

    QGraphicsSimpleTextItem *pZinitXOZtext = new QGraphicsSimpleTextItem;
    pZinitXOZtext->setPen(pen);
    pZinitXOZtext->setText(QString::number(_pAzList->first()));
    pZinitXOZtext->moveBy(XOZxOffset + 5, XOZzOffset + _pAzList->first()
        * yScalingCoeff);
    pChartScene->addItem(pZinitXOZtext);

//    QGraphicsSimpleTextItem *pZmaxXOZtext = new QGraphicsSimpleTextItem;
//    pZmaxXOZtext->setPen(pen);
//    pZmaxXOZtext->setText(QString::number(maxAz));

//    QGraphicsSimpleTextItem *pZminXOZtext = new QGraphicsSimpleTextItem;
//    pZminXOZtext->setPen(pen);
//    pZminXOZtext->setText(QString::number(minAz));

//    if (zRange != 0.0/* > cZeroTolerance*/) {
//        pZminXOZtext->moveBy(XOZxOffset + 5,
//            /*yAxisRange - 16*/XOZzOffset + minAz * /*zScalingCoeff*/yScalingCoeff);
//        pChartScene->addItem(pZminXOZtext);
//        pZmaxXOZtext->moveBy(XOZxOffset + 5,
//            /*yAxisRange - 16*/XOZzOffset + maxAz * /*zScalingCoeff*/yScalingCoeff);
//        pChartScene->addItem(pZmaxXOZtext);
//    }

    QGraphicsSimpleTextItem *pZfinalXOZtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::green);
    pZfinalXOZtext->setPen(pen);
    pZfinalXOZtext->setText(QString::number(_pAzList->last()));
    pZfinalXOZtext->moveBy(XOZxOffset + 5, XOZzOffset + _pAzList->last()
        * yScalingCoeff);
    pChartScene->addItem(pZfinalXOZtext);
    pen.setStyle(Qt::DashLine);
    pChartScene->addLine(XOZxOffset + xAxisRange, XOZzOffset + _pAzList->last()
        * yScalingCoeff, XOZxOffset, XOZzOffset + _pAzList->last()
        * yScalingCoeff, pen);

    QGraphicsSimpleTextItem *pXaxisXOZtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::cyan);
    pen.setStyle(Qt::SolidLine);
    pXaxisXOZtext->setPen(pen);
    pXaxisXOZtext->setText("X");
    pXaxisXOZtext->moveBy(XOZxOffset + xAxisRange + 5, XOZzOffset);
    pChartScene->addItem(pXaxisXOZtext);

    QGraphicsSimpleTextItem *pXmaxXOZtext = new QGraphicsSimpleTextItem;
    pen.setColor(Qt::green);
    pXmaxXOZtext->setPen(pen);
    pXmaxXOZtext->setText(QString::number(maxAx));
    pXmaxXOZtext->moveBy(XOZxOffset + xAxisRange + 5, XOZzOffset - 15);
    pChartScene->addItem(pXmaxXOZtext);
    pen.setStyle(Qt::DashLine);
    pChartScene->addLine(XOZxOffset + xAxisRange, XOZzOffset + _pAzList->last()
        * yScalingCoeff, XOZxOffset + xAxisRange, XOZzOffset, pen);

    /// Charts drawing
    int drawIndex = 0;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    do {
//        if (xRange/* != 0.0*/ > cZeroTolerance) {
            pChartScene->addLine(XOYxOffset + _pAxList->at(drawIndex)
                * xScalingCoeff, XOYyOffset - _pAyList->at(drawIndex)
                * yScalingCoeff, XOYxOffset + _pAxList->at(drawIndex + 1)
                * xScalingCoeff, XOYyOffset - _pAyList->at(drawIndex + 1)
                * yScalingCoeff, pen);
            if (zRange != 0.0/* > cZeroTolerance*/) {
                pChartScene->addLine(XOZxOffset + _pAxList->at(drawIndex)
                    * xScalingCoeff, XOZzOffset + _pAzList->at(drawIndex)
                    * /*zScalingCoeff*/yScalingCoeff, XOZxOffset + _pAxList->at(drawIndex + 1)
                    * xScalingCoeff, XOZzOffset + _pAzList->at(drawIndex + 1)
                    * /*zScalingCoeff*/yScalingCoeff, pen);
            }
            else {
                pChartScene->addLine(XOZxOffset + _pAxList->at(drawIndex)
                    * xScalingCoeff, XOZzOffset, XOZxOffset
                    + _pAxList->at(drawIndex + 1) * xScalingCoeff, XOZzOffset,
                    pen);
            }
//        }
//        else {
//            pChartScene->addLine(XOYxOffset, XOYyOffset - pAyList->at(drawIndex)
//                * yScalingCoeff, XOYxOffset, XOYyOffset - pAyList->at(drawIndex
//                + 1) * yScalingCoeff, pen);
//            if (zRange != 0.0/* > cZeroTolerance*/) {
//                pChartScene->addLine(XOZxOffset, XOZzOffset
//                    + pAzList->at(drawIndex) * zScalingCoeff, XOZxOffset,
//                    XOZzOffset + pAzList->at(drawIndex + 1) * zScalingCoeff,
//                    pen);
//            }
//            else {
//                pChartScene->addLine(XOZxOffset, XOZzOffset, XOZxOffset,
//                    XOZzOffset, pen);
//            }
//        }
        drawIndex++;
    } while (drawIndex < _pAxList->size() - 1);

//    ui->ballCalcGraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    ui->ballCalcGraphicsView->setScene(pChartScene);
}

void BallCalcResults::setP930mBallDataList(
    QList<QList<double>*> *p930mBallDataList
) {
    _p930mBallDataList = p930mBallDataList;
}

QString BallCalcResults::getShellName() const
{
    return _shellName;
}

void BallCalcResults::setShellName(const QString &value)
{
    _shellName = value;
}
