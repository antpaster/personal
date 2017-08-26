#include "investmentproject.h"
#include <math.h>

InvestmentProject::InvestmentProject()
{
    _invProjName = "Default inv proj";
    double discountRate = 0.17;
    double rp = 100.0;
    double usp = 50.0;
    double uavc = 5.0;
    _invProjLifeTime = 5;
    CashFlow cf;
    for (int i = 0; i < _invProjLifeTime; i++)
    {
        cf.setYear(i + 1);
        _pcf->append(cf);
    }
    _pp = calculatePp(_pcf);
    _arr = calculateArr(_pcf, rp);

    _npv = calculateNpv(_pcf, discountRate);
    _pi = calculatePi(_pcf, discountRate);
    _irr = calculateIrr(_pcf);
    _dpp = calculateDpp(_pcf, discountRate);
    _bep = calculateBep(_pcf, usp, uavc);

    _invProjPrice = 0;
    for (int i = 0; i < _pcf->count(); i++)
            _invProjPrice += _pcf->at(i).expense();
}

InvestmentProject::InvestmentProject(EconomicalSituation *es)
{
    double rp = 100.0;
    double usp = 50.0;
    double uavc = 5.0;
    _pp = calculatePp(_pcf);
    _arr = calculateArr(_pcf, rp);

    _npv = calculateNpv(_pcf, es->discountRate());
    _pi = calculatePi(_pcf, es->discountRate());
    _irr = calculateIrr(_pcf);
    _dpp = calculateDpp(_pcf, es->discountRate());
    _bep = calculateBep(_pcf, usp, uavc);

    _invProjPrice = 0;
    for (int i = 0; i < _pcf->count(); i++)
            _invProjPrice += _pcf->at(i).expense();
}

double InvestmentProject::pp() const
{
    return _pp;
}

void InvestmentProject::setPp(double pp)
{
    _pp = pp;
}
double InvestmentProject::arr() const
{
    return _arr;
}

void InvestmentProject::setArr(double arr)
{
    _arr = arr;
}
double InvestmentProject::npv() const
{
    return _npv;
}

void InvestmentProject::setNpv(double npv)
{
    _npv = npv;
}
double InvestmentProject::pi() const
{
    return _pi;
}

void InvestmentProject::setPi(double pi)
{
    _pi = pi;
}
double InvestmentProject::irr() const
{
    return _irr;
}

void InvestmentProject::setIrr(double irr)
{
    _irr = irr;
}
double InvestmentProject::dpp() const
{
    return _dpp;
}

void InvestmentProject::setDpp(double dpp)
{
    _dpp = dpp;
}
double InvestmentProject::bep() const
{
    return _bep;
}

void InvestmentProject::setBep(double bep)
{
    _bep = bep;
}
double InvestmentProject::invProjPrice() const
{
    return _invProjPrice;
}

void InvestmentProject::setInvProjPrice(double invProjPrice)
{
    _invProjPrice = invProjPrice;
}

QList<CashFlow> *InvestmentProject::pcf() const
{
    return _pcf;
}

void InvestmentProject::setPcf(QList<CashFlow> *pcf)
{
    _pcf = pcf;
}

double InvestmentProject::calculatePp(QList<CashFlow> *_pcf)
{
    double profits = 0;
    for (int i = 0; i < _pcf->count(); i++)
        profits += _pcf->at(i).profit();

    double expenses = 0;
    for (int i = 0; i < _pcf->count(); i++)
        expenses += _pcf->at(i).expense();

    return profits / expenses;
}

double InvestmentProject::calculateArr(QList<CashFlow> *_pcf, double realizationPrice)
{
    double averageYearProfit = 0;
    for (int i = 0; i < _pcf->count(); i++)
        averageYearProfit += _pcf->at(i).profit();
    averageYearProfit /= _pcf->count();

    double expenses = 0;
    for (int i = 0; i < _pcf->count(); i++)
        expenses += _pcf->at(i).expense();

    return 2 * averageYearProfit / (expenses - realizationPrice);
}

double InvestmentProject::calculateNpv(QList<CashFlow> *_pcf, double discountRate)
{
    double npv = 0;
    for (int i = 0; i < _pcf->count(); i++)
        npv += (_pcf->at(i).profit() - _pcf->at(i).expense()) / pow((1 + discountRate), i + 1);
    return npv;
}

double InvestmentProject::calculatePi(QList<CashFlow> *_pcf, double discountRate)
{
    double profitCashFlow = 0;
    for (int i = 0; i < _pcf->count(); i++)
        profitCashFlow += _pcf->at(i).profit() / pow((1 + discountRate), i + 1);

    double expenseCashFlow = 0;
    for (int i = 0; i < _pcf->count(); i++)
        expenseCashFlow += _pcf->at(i).expense() / pow((1 + discountRate), i + 1);

    return profitCashFlow / expenseCashFlow;
}

double InvestmentProject::calculateIrr(QList<CashFlow> *_pcf)
{
    double discountRate = 0.01;
    double posNpvDiscRate;
    double negNpvDiscRate;
    double positiveNpv;
    double negativeNpv;
    do
    {
        negativeNpv = calculateNpv(_pcf, discountRate);
        discountRate++;
    }
    while (negativeNpv > 0);

    negNpvDiscRate = discountRate;
    posNpvDiscRate = discountRate - 0.01;
    positiveNpv = calculateNpv(_pcf, discountRate - 0.01);

    return posNpvDiscRate + positiveNpv / (positiveNpv - negativeNpv) * (negNpvDiscRate - posNpvDiscRate);
}

double InvestmentProject::calculateDpp(QList<CashFlow> *_pcf, double discountRate)
{
    return calculatePp(_pcf) * pow((1 + discountRate), _pcf->count());
}

double InvestmentProject::calculateBep(QList<CashFlow> *_pcf, double unitSalePrice, double unitAverageVariableCosts)
{
    double expenses = 0;
    for (int i = 0; i < _pcf->count(); i++)
        expenses += _pcf->at(i).expense();

    return expenses / (unitSalePrice - unitAverageVariableCosts);
}

QString InvestmentProject::invProjName() const
{
    return _invProjName;
}

void InvestmentProject::setInvProjName(QString invProjName)
{
    _invProjName = invProjName;
}
int InvestmentProject::invProjLifeTime() const
{
    return _invProjLifeTime;
}

void InvestmentProject::setInvProjLifeTime(int invProjLifeTime)
{
    _invProjLifeTime = invProjLifeTime;
}














