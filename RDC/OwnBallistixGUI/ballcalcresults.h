#ifndef BALLCALCRESULTS_H
#define BALLCALCRESULTS_H

#include <QDialog>

#include "../gentypes.h"
#include "../OwnVersion/typesnconstants.h"
#include "../OwnVersion/ballcharacts.h"

namespace Ui {
class BallCalcResults;
}

class BallCalcResults : public QDialog
{
    Q_OBJECT

public:
    explicit BallCalcResults(QWidget *parent = 0);
    ~BallCalcResults();

    /// Main ballistic calculation
    bool ballCalculation(
        const TInputBallData *pInpBD,
        TInternalBallData *pIntBD
    );

    QString getShellName() const;
    void setShellName(const QString &value);

    void drawResultsChart();

    void setP930mBallDataList(QList<QList<double>*> *p930mBallDataList);

private:
    Ui::BallCalcResults *ui;

    QString _shellName;

    QList<QList<double>*> *_p930mBallDataList;

    QList<double> *_pAxList;
    QList<double> *_pAyList;
    QList<double> *_pAzList;

    double /// VVA params
           _vcxSqDelta, /// extra drag force coefficient
           _vcyDelta, /// elevation force coefficient
           _vcMdelta, /// Magnus force coefficient
           _vmx1Omegax1, /// X axis dempher moment coefficient
           _vmz1Omegaz1, /// Z axis dempher moment coefficient
           _vmz1Delta, /// turning over moment coefficient
           _vmMdelta, /// Magnus force moment coefficient

           /// S8-KL params
           _vcyAlpha, /// elevation (side) force coefficient derivative
                      /// respect to attack (slide) angle
           _vMinusMzAlpha, /// shell Z axis rotation moment derivative respect
                           /// to attack angle
           _vMinusMzOmegaLineZ, /// shell Z axis rotation moment derivative
                                /// respect to dimensionless angle speed
                                /// omegaLineZ
           _vmx, /// shell X axis rotation moment coefficient
           _vMinusMxOmegaLineX; /// shell X axis rotation moment derivative
                                /// respect to dimensionless angle speed
                                /// omegaLineX

    /// Stage ballistic parameters calculation for S8-KL missile
    void s8_kl_stageBallistParamsCalc(
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
    );

    /// Filling the ballistic calculation table string by current calculation
    /// step data
    void fillBallCalcResTableString(
        int itemRowNumber,
        const TInternalBallData *pIntBD
    );
};

#endif // BALLCALCRESULTS_H
