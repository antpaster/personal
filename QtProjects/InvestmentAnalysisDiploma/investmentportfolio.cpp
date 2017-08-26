#include "investmentportfolio.h"

InvestmentPortfolio::InvestmentPortfolio()
{
}
double InvestmentPortfolio::wacc() const
{
    return _wacc;
}

void InvestmentPortfolio::setWacc(double wacc)
{
    _wacc = wacc;
}

