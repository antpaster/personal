#include "stock.h"

Stock::Stock()
{
}
StockType Stock::st() const
{
    return _st;
}

double Stock::currentStockPrice() const
{
    return _currentStockPrice;
}

void Stock::setCurrentStockPrice(double currentStockPrice)
{
    _currentStockPrice = currentStockPrice;
}

void Stock::setSt(const StockType &st)
{
    _st = st;
}
double Stock::dividendValue() const
{
    return _dividendValue;
}

void Stock::setDividendValue(double dividendValue)
{
    _dividendValue = dividendValue;
}
double Stock::dividendGrowthRate() const
{
    return _dividendGrowthRate;
}

void Stock::setDividendGrowthRate(double dividendGrowthRate)
{
    _dividendGrowthRate = dividendGrowthRate;
}
double Stock::stockDeploymentPrice() const
{
    return _stockDeploymentPrice;
}

void Stock::setStockDeploymentPrice(double stockDeploymentPrice)
{
    _stockDeploymentPrice = stockDeploymentPrice;
}

double Stock::stockPrice() const
{
    return _stockPrice;
}

void Stock::setStockPrice(double stockPrice)
{
    _stockPrice = stockPrice;
}

double Stock::calculateStockPrice(double _currentStockPrice, double _dividendValue, double _dividendGrowthRate, double _stockDeploymentPrice)
{
    if (_st == privilegedStock)
        _dividendGrowthRate = 0;
    return _dividendValue / (_currentStockPrice * (1 - _stockDeploymentPrice)) + _dividendGrowthRate;
}







