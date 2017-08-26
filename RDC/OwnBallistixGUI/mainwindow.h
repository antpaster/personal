#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include "../930mBallist/ballist_pi.h"

#include "../OwnVersion/typesnconstants.h"

#include "ballcalcresults.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /// Assigning data for ballistic calculation
    void assignBallData(
        TInputBallData* pInpBD
    );

    /// Getting the calculation results
    void getBallCalcResults(
        BallCalcResults *pBCR,
        const TInputBallData *pInpBD,
        const TInternalBallData* pIntBD,
        TOutputBallData* pOutBD
    );

    double s8_kl_getAdjustParamArg(
        BallCalcResults *pBCR,
        const double adjustParamArg
    );

    /// S8-KL missile required launch parameter value adjusting by half
    /// division method
    void s8_kl_adjustParamByHalfDivision(
        BallCalcResults *pBCR
    );

    /// Whole ballistic calculation circle
    void ballCalcCircle(
        BallCalcResults* pBCR
    );


    /*! Метод Формирующий исходные данные для БВ
    ********************************************************************************
    ** \return код выполнения операции:
    **  - OPER_SUCCESS - успешное завершение операции
    **  - OPER_FAILURE - операция не может быть выполнена
    */
    TOPER_RESULT ballist_930m_lInputData (
            TBalInputData	*pInputData,	/*!< Адрес входных данных			*/
            TCREW_MEMBER	crewId			/*!< Идентификатор члена экипажа	*/
    );

    /*! Головной менеджер балистического вычислителя
    ********************************************************************************
    * \return код выполнения операции:
    *  - OPER_SUCCESS - успешное завершение операции
    *  - OPER_FAILURE - операция не может быть выполнена
    */
    TOPER_RESULT ballist_hInit (
            T_BALLIST_MODIF	modification,		/*!< Модификация модуля			*/
            TOPER_RESULT	(*(pInputData))(TBalInputData *, TCREW_MEMBER)
    );

    /*! Функция формирования параметров, определяющих
    **  баллистические характеристики НАСП
    ********************************************************************************
    **  \return
    */
    void ballist_lFormAspData (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*!  Функция формирования навигационных параметров
    ********************************************************************************
    ** \return
    */
    void ballist_lFormNvgData (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*!	Функция формирования выходной информации
    ********************************************************************************
    **	\return
    */
    void ballist_lFormOutputData (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*!	Функция баллистического вычислителя
    ********************************************************************************
    **	\return
    */
    void ballist_lCompute (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*! Головной менеджер балистического вычислителя
    ********************************************************************************
    * \return код выполнения операции:
    *  - OPER_SUCCESS - успешное завершение операции
    *  - OPER_FAILURE - операция не может быть выполнена
    */
    TOPER_RESULT ballist_Monitor (
            TCircleThread	circle	/*!< Признак потока	вызова 					*/
    );

    /*! Функция возвращает дальность до падения боеприпаса
    ********************************************************************************
    ** \return Результат вычисления
    */
    TDouble ballist_GetDistance (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*! Функция возвращает время падения боеприпаса
    ********************************************************************************
    ** \return Результат вычисления
    */
    TDouble ballist_GetFallTime (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*! Функция возвращает вектор относа боеприпаса
    ********************************************************************************
    ** \return Результат вычисления
    */
    TOPER_RESULT ballist_GetImpactPointHSC (
            TDVect3 impactPointHSC,	/*!< вектор относа НАСП в ГорСК */
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*! Метод реализующий
    ********************************************************************************
    ** \return код выполнения операции:
    **  - OPER_SUCCESS - успешное завершение операции
    **  - OPER_FAILURE - операция не может быть выполнена
    */
    TDouble ballist_GetInpRelTrgHh (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*! Метод реализующий проеверку наличия ручного выключения балитики из работы
    ********************************************************************************
    ** \return код выполнения операции:
    **  - OPER_SUCCESS - успешное завершение операции
    **  - OPER_FAILURE - операция не может быть выполнена
    */
    TREGIME_MODE ballist_GetWorkMode (
            TCREW_MEMBER	crewId	/*!< Идентификатор члена экипажа	*/
    );

    /*! Метод реализующий задания режима работы баллистики
    ********************************************************************************
    ** \return код выполнения операции:
    **  - OPER_SUCCESS - успешное завершение операции
    **  - OPER_FAILURE - операция не может быть выполнена
    */
    TOPER_RESULT ballist_SetWorkMode (
        TREGIME_MODE	workMode,	/*!< Включение оперативного режима работы	*/
        TCREW_MEMBER	crewId,	/*!< Идентификатор члена экипажа	*/
        TUInt16			idCall		/*!< Идентификатор вызова					*/
    );

    /*! Метод реализующий задание типа расчета атомсферы для БВ
    ********************************************************************************
    ** \return код выполнения операции:
    **  - OPER_SUCCESS - успешное завершение операции
    **  - OPER_FAILURE - операция не может быть выполнена
    */
    TOPER_RESULT ballist_SetAtmosphCalcType (
            T_BALLIST_ATMOSPH		atmCalcType	/*!< [in] Задаваемое значение */
    );

    /*! Метод возвращающий тип расчета атмосферы для БВ
    ********************************************************************************
    ** \return Запрашиваемое значение
    */
    T_BALLIST_ATMOSPH ballist_GetAtmosphCalcType ( void );


public slots:
    void showVelocitiesInHCS();
    void chooseShellName();
    void enterLastStageCompleteParam();
    void setLastStageCompleteParam();
    void checkInputData();
    void openCalcResultsDialog();
    void openAtmosphCalcComparisonDialog();
    void openS8KLadjustResultsDialog();

private:
    void appParamUIassignment();

    Ui::MainWindow *ui;

    /// Partial UI data accumulators. They will be changed before the input
    /// ballistic data assignment occurs
    TSingleStageBallCharact *_pSingleStageShellUI;
    TDoubleStageBallCharact *_pDoubleStageShellUI;
    TTripleStageBallCharact *_pTripleStageShellUI;
    TypesOfCompleteStage _lastStageCompleteConditionUI;
    double _lastStageCompleteParamUI;
    double _appWayAngleUI;
    double _appYawUI, _appPitchUI, _appRollUI;
    double _appAttackUI, _appSlideUI;
    TDVect3 _appWvectUI;
    TDVect3 _appVvectUI;
    TDVect3 _initUvectUI;

    /// Extra data accummulators for 930m ballistics
    TDVect3 _appVvectCCS930m;
    TDVect3 _aspEvectCCS930m;
    TDVect3 _aspEvectHCS930m;

    /// Total ballistic data object
    TTotalBallData *_pMyBallist;
    TBALLIST *_pBALLIST;
};

#endif // MAINWINDOW_H
