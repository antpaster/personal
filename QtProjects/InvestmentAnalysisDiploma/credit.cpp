#include "credit.h"

Credit::Credit()
{
}
QString Credit::bankName() const
{
    return _bankName;
}

void Credit::setBankName(const QString &bankName)
{
    _bankName = bankName;
}
double Credit::creditRate() const
{
    return _creditRate;
}

void Credit::setCreditRate(double creditRate)
{
    _creditRate = creditRate;
}
double Credit::creditValue() const
{
    return _creditValue;
}

void Credit::setCreditValue(double creditValue)
{
    _creditValue = creditValue;
}
int Credit::repaymentPeriod() const
{
    return _repaymentPeriod;
}

void Credit::setRepaymentPeriod(int repaymentPeriod)
{
    _repaymentPeriod = repaymentPeriod;
}




