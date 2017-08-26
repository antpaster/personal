#ifndef INVESTMENTPORTFOLIO_H
#define INVESTMENTPORTFOLIO_H

#include <QList>
#include "investor.h"
#include "investmentproject.h"
#include "stock.h"

class InvestmentPortfolio
{
public:
    InvestmentPortfolio();

    double wacc() const;
    void setWacc(double wacc);

    void calculateWacc(Investor *pinv, QList<Stock> *_ps);

private:
    double _wacc;

    QList<InvestmentProject> *_pip;
    QList<Stock> *_ps;
};

#endif // INVESTMENTPORTFOLIO_H
