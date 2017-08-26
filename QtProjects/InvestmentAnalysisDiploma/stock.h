#ifndef STOCK_H
#define STOCK_H

enum StockType
{
    generalStock,
    privilegedStock
};

class Stock
{
public:
    Stock();

    StockType st() const;
    void setSt(const StockType &st);

    double currentStockPrice() const;
    void setCurrentStockPrice(double currentStockPrice);

    double dividendValue() const;
    void setDividendValue(double dividendValue);

    double dividendGrowthRate() const;
    void setDividendGrowthRate(double dividendGrowthRate);

    double stockDeploymentPrice() const;
    void setStockDeploymentPrice(double stockDeploymentPrice);

    double stockPrice() const;
    void setStockPrice(double stockPrice);

    double calculateStockPrice(double _currentStockPrice, double _dividendValue,
                             double _dividendGrowthRate, double _stockDeploymentPrice);

private:
    StockType _st;
    double _currentStockPrice;
    double _dividendValue;
    double _dividendGrowthRate;
    double _stockDeploymentPrice;

    double _stockPrice;
};

#endif // STOCK_H
