#ifndef INVESTOR_H
#define INVESTOR_H

#include <QList>
#include "investmentproject.h"
#include "credit.h"

class Investor
{
public:
    Investor();

    QString investorName() const;
    void setInvestorName(const QString &investorName);

    double capitalValue() const;
    void setCapitalValue(double capitalValue);

    bool isBudgetLimited() const;
    void setIsBudgetLimited(bool isBudgetLimited);

private:
    QString _investorName;
    double _capitalValue;
    bool _isBudgetLimited;

    QList<InvestmentProject> *_pip;
    QList<Credit> *_pc;
};

#endif // INVESTOR_H
