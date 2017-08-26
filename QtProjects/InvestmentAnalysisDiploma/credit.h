#ifndef CREDIT_H
#define CREDIT_H

#include <QString>

class Credit
{
public:
    Credit();

    QString bankName() const;
    void setBankName(const QString &bankName);

    double creditRate() const;
    void setCreditRate(double creditRate);

    double creditValue() const;
    void setCreditValue(double creditValue);

    int repaymentPeriod() const;
    void setRepaymentPeriod(int repaymentPeriod);

private:
    QString _bankName;
    double _creditRate;
    double _creditValue;
    int _repaymentPeriod;
};

#endif // CREDIT_H
