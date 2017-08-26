#ifndef CASHFLOW_H
#define CASHFLOW_H

class CashFlow
{
public:
    CashFlow();
    CashFlow(double profit, double expense, int year);

    double profit() const;
    void setProfit(double profit);

    double expense() const;
    void setExpense(double expense);

    int year() const;
    void setYear(int year);

private:
    double _profit;
    double _expense;
    int _year;
};

#endif // CASHFLOW_H
