#ifndef ECONOMICALSITUATION_H
#define ECONOMICALSITUATION_H

class EconomicalSituation
{
public:
    EconomicalSituation();

    double inflationRate() const;
    void setInflationRate(double inflationRate);

    double basicRate() const;
    void setBasicRate(double basicRate);

    double discountRate() const;
    void setDiscountRate(double discountRate);

    double profitTaxRate() const;
    void setProfitTaxRate(double profitTaxRate);

private:
    double _inflationRate;
    double _basicRate;
    double _discountRate;
    double _profitTaxRate;
};

#endif // ECONOMICALSITUATION_H
