#include "polynommember.h"

#include <QString>

PolynomMember::PolynomMember()
{
}

double PolynomMember::koeff() const
{
    return _koeff;
}

void PolynomMember::setKoeff(double koeff)
{
    _koeff = koeff;
}

int PolynomMember::power() const
{
    return _power;
}

void PolynomMember::setPower(int power)
{
    _power = power;
}

PolynomMember PolynomMember::setPolyFromString(QString strPoly)
{
    QString koeffStr, powerStr;

    bool isNumber = true;
    for (int i = 0; i < strPoly.length(); i++)
        if (strPoly[i] == 'x')
            isNumber = false;
    if (isNumber)
    {
        _koeff = strPoly.toDouble();
        _power = 0;
        return *this;
    }
    else
    {
        int i = 0;
        if (strPoly[i] == 'x')
            _koeff = 1;
        else
        {
            do
            {
                koeffStr[i] = strPoly[i];
                i++;
            } while (strPoly[i] != 'x');

            _koeff = koeffStr.toDouble();
        }

        int j = 0;
        i++;
        if (i >= strPoly.length())
            _power = 1;
        else
        {
            do
            {
                powerStr[j] = strPoly[i];
                j++;
                i++;
            } while (i < strPoly.length());

            _power = powerStr.toInt();
        }
    }
    return *this;
}
