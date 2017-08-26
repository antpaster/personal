#include "cashflow.h"

CashFlow::CashFlow()
{
    _profit = 100000.00;
    _expense = 75000.00;
    _year = 1;
}

CashFlow::CashFlow(double profit, double expense, int year)
{
    _profit = profit;
    _expense = expense;
    _year = year;
}

double CashFlow::profit() const
{
    return _profit;
}

void CashFlow::setProfit(double profit)
{
    _profit = profit;
}
double CashFlow::expense() const
{
    return _expense;
}

void CashFlow::setExpense(double expense)
{
    _expense = expense;
}
int CashFlow::year() const
{
    return _year;
}

void CashFlow::setYear(int year)
{
    _year = year;
}



