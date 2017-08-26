#include "economicalsituation.h"

EconomicalSituation::EconomicalSituation()
{
    _inflationRate = 0.15;
    _basicRate = 0.085;
    _discountRate = 0.17;
    _profitTaxRate = 0.24;
}

double EconomicalSituation::inflationRate() const
{
    return _inflationRate;
}

void EconomicalSituation::setInflationRate(double inflationRate)
{
    _inflationRate = inflationRate;
}

double EconomicalSituation::basicRate() const
{
    return _basicRate;
}

void EconomicalSituation::setBasicRate(double basicRate)
{
    _basicRate = basicRate;
}

double EconomicalSituation::discountRate() const
{
    return _discountRate;
}

void EconomicalSituation::setDiscountRate(double discountRate)
{
    _discountRate = discountRate;
}

double EconomicalSituation::profitTaxRate() const
{
    return _profitTaxRate;
}

void EconomicalSituation::setProfitTaxRate(double profitTaxRate)
{
    _profitTaxRate = profitTaxRate;
}




