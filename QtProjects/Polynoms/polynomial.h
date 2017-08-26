#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

using namespace std;

template <class Coeff>
class Polynomial
{
public:
    Polynomial();
    Polynomial(vector<Coeff> &coeffVect);

    vector<Coeff> coeffVect() const;
    void setCoeffVect(const vector<Coeff> &coeffVect);

    Polynomial<Coeff> operator =(Polynomial<Coeff> &poly);
    bool operator ==(Polynomial<Coeff> &poly);
    bool operator !=(Polynomial<Coeff> &poly);

    template <Coeff>
    friend Polynomial<Coeff> operator +(Polynomial<Coeff> &poly1,
                                        Polynomial<Coeff> &poly2);
    template <Coeff>
    friend Polynomial<Coeff> operator -(Polynomial<Coeff> &polySubtrahend,
                                        Polynomial<Coeff> &polySubtractor);
    template <Coeff>
    friend Polynomial<Coeff> operator *(Polynomial<Coeff> &poly1,
                                        Polynomial<Coeff> &poly2);
    template <Coeff>
    friend Polynomial<Coeff> operator /(Polynomial<Coeff> &polyDividend,
                                        Polynomial<Coeff> &polyDivider);
    template <Coeff>
    friend Polynomial<Coeff> operator %(Polynomial<Coeff> &polyDividend,
                                        Polynomial<Coeff> &polyDivider);

    template <Coeff>
    friend Polynomial<Coeff> operator +(Polynomial<Coeff> &poly, double number);
    template <Coeff>
    friend Polynomial<Coeff> operator -(Polynomial<Coeff> &poly, double number);
    template <Coeff>
    friend Polynomial<Coeff> operator *(Polynomial<Coeff> &poly, double number);

    Polynomial<Coeff>& operator +=(Polynomial<Coeff> &poly);
    Polynomial<Coeff>& operator -=(Polynomial<Coeff> &poly);
    Polynomial<Coeff>& operator *=(Polynomial<Coeff> &poly);

    Coeff operator [](int i);

    double inPointVal(double x);

    Polynomial<Coeff> maxCommonDivider(Polynomial<Coeff> &poly1,
                                       Polynomial<Coeff> &poly2);

    template <Coeff>
    friend ostream& operator <<(ostream &out, Polynomial<Coeff> &poly);

    int polyDegree(Polynomial<Coeff> &poly);

private:
    vector<Coeff> _coeffVect;
};

#endif // POLYNOMIAL_H
