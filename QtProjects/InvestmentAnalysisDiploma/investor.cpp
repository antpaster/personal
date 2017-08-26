#include "investor.h"

Investor::Investor()
{
}
QString Investor::investorName() const
{
    return _investorName;
}

void Investor::setInvestorName(const QString &investorName)
{
    _investorName = investorName;
}
double Investor::capitalValue() const
{
    return _capitalValue;
}

void Investor::setCapitalValue(double capitalValue)
{
    _capitalValue = capitalValue;
}
bool Investor::isBudgetLimited() const
{
    return _isBudgetLimited;
}

void Investor::setIsBudgetLimited(bool isBudgetLimited)
{
    _isBudgetLimited = isBudgetLimited;
}



