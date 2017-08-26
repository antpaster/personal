#ifndef INVESMENTPROJECT_H
#define INVESMENTPROJECT_H

#include <QString>
#include <QList>
#include "cashflow.h"
#include "economicalsituation.h"

class InvestmentProject
{
public:
    InvestmentProject();
    InvestmentProject(EconomicalSituation *es);

    double pp() const;
    void setPp(double pp);

    double arr() const;
    void setArr(double arr);

    double npv() const;
    void setNpv(double npv);

    double pi() const;
    void setPi(double pi);

    double irr() const;
    void setIrr(double irr);

    double dpp() const;
    void setDpp(double dpp);

    double bep() const;
    void setBep(double bep);

    double invProjPrice() const;
    void setInvProjPrice(double invProjPrice);

    QList<CashFlow> *pcf() const;
    void setPcf(QList<CashFlow> *pcf);

    double calculatePp(QList<CashFlow> *_pcf);
    double calculateArr(QList<CashFlow> *_pcf, double realizationPrice);

    double calculateNpv(QList<CashFlow> *_pcf, double discountRate);
    double calculatePi(QList<CashFlow> *_pcf, double discountRate);
    double calculateIrr(QList<CashFlow> *_pcf);
    double calculateDpp(QList<CashFlow> *_pcf, double discountRate);
    double calculateBep(QList<CashFlow> *_pcf, double unitSalePrice,
                      double unitAverageVariableCosts);

    double analyseSensitivity(double param, double sensInterval);
    double analyseScenario(double param, QList<double> *pScenarioProbs);

    QString invProjName() const;
    void setInvProjName(QString invProjName);

    int invProjLifeTime() const;
    void setInvProjLifeTime(int invProjLifeTime);

private:
    QString _invProjName;

    double _pp;
    double _arr;
    double _npv;
    double _pi;
    double _irr;
    double _dpp;
    double _bep;

    double _invProjPrice;
    int _invProjLifeTime;

    QList<CashFlow> *_pcf;

};

#endif // INVESMENTPROJECT_H
