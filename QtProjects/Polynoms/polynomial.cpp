#include "polynomial.h"


template <class Coeff>
Polynomial<Coeff>::Polynomial()
{
    cout << "Empty polynom" << endl;
}

/// Constructor with vector of coefficients parameter
template <class Coeff>
Polynomial<Coeff>::Polynomial(vector<Coeff> &coeffVect)
{
    _coeffVect = coeffVect;
}

/// Get coeff vector
template <class Coeff>
vector<Coeff> Polynomial<Coeff>::coeffVect() const
{
    return _coeffVect;
}

/// Set coeff vector
template <class Coeff>
void Polynomial<Coeff>::setCoeffVect(const vector<Coeff> &coeffVect)
{
    _coeffVect = coeffVect;
}

/// Assignment operator overloading
template <class Coeff>
Polynomial<Coeff> Polynomial<Coeff>::operator =(Polynomial<Coeff> &poly)
{
    setCoeffVect(poly.coeffVect());
    return *this;
}

/// Equality operator overloading
template <class Coeff>
bool Polynomial<Coeff>::operator ==(Polynomial<Coeff> &poly)
{
    for (int i = 0; i < poly.coeffVect(); i++)
        if (_coeffVect[i] != poly.coeffVect()[i])
            return false;
    return true;
}

/// Unequality operator oveloading
template <class Coeff>
bool Polynomial<Coeff>::operator !=(Polynomial<Coeff> &poly)
{
    return !(*this == poly);
}

/// Adding operator overloading
template <class Coeff>
Polynomial<Coeff> operator +(Polynomial<Coeff> &poly1, Polynomial<Coeff> &poly2)
{
    int youngerDeg = poly1.coeffVect().size() > poly2.coeffVect().size() ?
                     poly2.coeffVect().size() : poly1.coeffVect().size();
    Polynomial<Coeff> resPoly;
    vector<Coeff> resVect;

    for (int i = 0; i < youngerDeg; i++)
        resVect.push_back(poly1.coeffVect()[i] + poly2.coeffVect()[i]);

    if (poly1.coeffVect().size() == poly2.coeffVect().size())
    {
        resPoly.setCoeffVect(resVect);
        return resPoly;
    }

    if (poly1.coeffVect().size() > poly2.coeffVect().size())
        for (int i = youngerDeg; i < poly1.coeffVect().size(); i++)
            resVect.push_back(poly1.coeffVect()[i]);
    else
        for (int i = youngerDeg; i < poly2.coeffVect().size(); i++)
            resVect.push_back(poly2.coeffVect()[i]);

    resPoly.setCoeffVect(resVect);
    return resPoly;
}

/// Subtraction operator overloading
template <class Coeff>
Polynomial<Coeff> operator -(Polynomial<Coeff> &polySubtrahend,
                             Polynomial<Coeff> &polySubtractor)
{
    int youngerDeg = (polySubtrahend.coeffVect().size() >
                     polySubtractor.coeffVect().size()) ?
                     polySubtractor.coeffVect().size() :
                     polySubtrahend.coeffVect().size();

    Polynomial<Coeff> resPoly;
    vector<Coeff> resVect;

    for (int i = 0; i < youngerDeg; i++)
        resVect.push_back(polySubtrahend.coeffVect()[i] -
                          polySubtractor.coeffVect()[i]);

    if (polySubtrahend.coeffVect().size() == polySubtractor.coeffVect().size())
    {
        resPoly.setCoeffVect(resVect);
        return resPoly;
    }

    if (polySubtrahend.coeffVect().size() > polySubtractor.coeffVect().size())
        for (int i = youngerDeg; i < polySubtrahend.coeffVect().size(); i++)
            resVect.push_back(polySubtrahend.coeffVect()[i]);
    else
        for (int i = youngerDeg; i < polySubtractor.coeffVect().size(); i++)
            resVect.push_back(-polySubtractor.coeffVect()[i]);

    resPoly.setCoeffVect(resVect);
    return resPoly;
}

/// Multiplying operator overloading
template <class Coeff>
Polynomial<Coeff> operator *(Polynomial<Coeff> &poly1, Polynomial<Coeff> &poly2)
{
    Polynomial<Coeff> resPoly;
    vector<Coeff> resVect;

    for (int i = 0; i < poly1.coeffVect().size() + poly2.coeffVect().size(); i++)
        resVect.push_back(0);

    for (int i = 0; i < poly1.coeffVect().size(); i++)
        for (int j = 0; j < poly2.coeffVect().size(); j++)
            resVect[i + j] += poly1.coeffVect()[i] * poly2.coeffVect()[j];

    resPoly.setCoeffVect(resVect);
    return resPoly;
}

/// Adding a number operator overloading
template <class Coeff>
Polynomial<Coeff> operator +(Polynomial<Coeff> &poly, double number)
{
    Polynomial<Coeff> resPoly;
    vector<Coeff> resVect;

    resVect = poly.coeffVect();
    resVect[0] += number;
    resPoly.setCoeffVect(resVect);

    return resPoly;
}

/// Subtraction of a number operator overloading
template <class Coeff>
Polynomial<Coeff> operator -(Polynomial<Coeff> &poly, double number)
{
    Polynomial<Coeff> resPoly;
    vector<Coeff> resVect;

    resVect = poly.coeffVect();
    resVect[0] -= number;
    resPoly.setCoeffVect(resVect);

    return resPoly;
}

/// Multiplying to a number operator overloading
template <class Coeff>
Polynomial<Coeff> operator *(Polynomial<Coeff> &poly, double number)
{
    Polynomial<Coeff> resPoly;
    vector<Coeff> resVect;

    for (int i = 0; i < poly.coeffVect().size(); i++)
        resVect = poly.coeffVect()[i] * number;
    resPoly.setCoeffVect(resVect);

    return resPoly;
}

/// Adding and assignment operator overloading
template <class Coeff>
Polynomial<Coeff> &Polynomial<Coeff>::operator +=(Polynomial<Coeff> &poly)
{
    *this = *this + poly;
    return *this;
}

/// Subtraction and assignment operator overloading
template <class Coeff>
Polynomial<Coeff> &Polynomial<Coeff>::operator -=(Polynomial<Coeff> &poly)
{
    *this = *this - poly;
    return *this;
}

/// Multiplying and assignment operator overloading
template <class Coeff>
Polynomial<Coeff> &Polynomial<Coeff>::operator *=(Polynomial<Coeff> &poly)
{
    *this = *this * poly;
    return *this;
}

/// Indexing operator overloading
template <class Coeff>
Coeff Polynomial<Coeff>::operator [](int i)
{
    if (i > _coeffVect.size() - 1)
        return 0;
    else
        return _coeffVect[i];
}

/// Polynom value in the given point calculation
template <class Coeff>
double Polynomial<Coeff>::inPointVal(double x)
{
    double res = _coeffVect[0], resTerm = 1.0;

    for (int i = 1; i < _coeffVect.size(); i++)
    {
        resTerm *= x;
        res += _coeffVect[i] * resTerm;
    }

    return res;
}

/// Retrieving polynom's degree
template <class Coeff>
int Polynomial<Coeff>::polyDegree(Polynomial<Coeff> &poly)
{
    return poly.coeffVect().size() - 1;
}

/// Division operator overloading
template <class Coeff>
Polynomial<Coeff> operator /(Polynomial<Coeff> &polyDividend,
                             Polynomial<Coeff> &polyDivider)
{
    Polynomial<Coeff> resPoly, divCheckPoly = polyDividend,
                      divSubtractPoly = polyDivider, tempResPoly;
    vector<Coeff> resVect, tempResVect;
    int resVectSize = polyDividend.coeffVect().size() -
                      polyDivider.coeffVect().size() + 1;

    for (int i = 0; i < resVectSize; i++)
    {
        resVect[resVectSize - i - 1] =
            divCheckPoly.coeffVect()[divCheckPoly.coeffVect().size() - i - 1];

        for (int j = 0; j < resVectSize - i - 1; j++)
            tempResVect.push_back(0);
        tempResVect.push_back(resVect[resVectSize - i - 1]);
        tempResPoly.setCoeffVect(tempResVect);

        divSubtractPoly *= tempResPoly;

        divCheckPoly -= divSubtractPoly;

        tempResVect.clear();
        divSubtractPoly = polyDivider;
    }

    resPoly.setCoeffVect(resVect);
    return resPoly;
}

/// Residual calculation operator overloading
template <class Coeff>
Polynomial<Coeff> operator %(Polynomial<Coeff> &polyDividend,
                             Polynomial<Coeff> &polyDivider)
{
    Polynomial<Coeff> resPoly, divCheckPoly = polyDividend,
                      divSubtractPoly = polyDivider, tempResPoly;
    vector<Coeff> resVect, tempResVect;
    int resVectSize = polyDividend.coeffVect().size() -
                      polyDivider.coeffVect().size() + 1;

    for (int i = 0; i < resVectSize; i++)
    {
        for (int j = 0; j < resVectSize - i - 1; j++)
            tempResVect.push_back(0);
        tempResVect.push_back(
            divCheckPoly.coeffVect()[divCheckPoly.coeffVect().size() - i - 1]);
        tempResPoly.setCoeffVect(tempResVect);

        divSubtractPoly *= tempResPoly;

        divCheckPoly -= divSubtractPoly;

        tempResVect.clear();
        divSubtractPoly = polyDivider;
    }

    for (int i = 0; i < polyDivider - 1; i++)
        resVect.push_back(divCheckPoly.coeffVect()[i]);

    resPoly.setCoeffVect(resVect);
    return resPoly;
}

/// Stream output operator overloading
template <class Coeff>
ostream& operator <<(ostream &out, Polynomial<Coeff> &poly)
{
    if (poly.coeffVect().size() == 1)
    {
        out << poly.coeffVect()[0];
        return out;
    }

    for (int i = poly.coeffVect().size() - 1; i > 0; i--)
    {
        if (!poly.coeffVect()[i])
            if (poly.coeffVect()[i - 1] > 0)
            {
                out << "+ ";
                continue;
            }

        out << poly.coeffVect()[i] << "x^";
        if (i != 1)
            out << i << ' ';
        else
            out << ' ';
        if (poly.coeffVect()[i - 1] > 0)
            out << "+ ";
    }
    if (poly.coeffVect()[0])
        out << poly.coeffVect()[0];

    return out;
}
