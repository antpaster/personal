#ifndef POLYNOMMEMBER_H
#define POLYNOMMEMBER_H

#include <QString>

class PolynomMember
{
public:
    PolynomMember();

    double koeff() const;
    void setKoeff(double koeff);

    int power() const;
    void setPower(int power);

    PolynomMember setPolyFromString(QString strPoly);

private:
    double _koeff;
    int _power;
};

#endif // POLYNOMMEMBER_H
