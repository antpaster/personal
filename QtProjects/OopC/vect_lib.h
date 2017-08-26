#ifndef VECT_LIB_H
#define VECT_LIB_H

#include "scalar.h"
#include "vect2rd.h"
#include "vect3rd.h"
#include "matr3x3.h"

#define F_NULL 1e-20

#define add( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : addScalar, \
    TVect2Rd* : addVect2Rd, \
    TVect3Rd* : addVect3Rd, \
    TMatr3x3* : addMatr3x3 \
) ( R, X, Y)

#define subtract( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : subtractScalar, \
    TVect2Rd* : subtractVect2Rd, \
    TVect3Rd* : subtractVect3Rd, \
    TMatr3x3* : subtractMatr3x3 \
) ( R, X, Y)

#define multiply( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : multiplyScalar, \
    TVect2Rd* : multiplyVect2Rd, \
    TVect3Rd* : multiplyVect3Rd, \
    TMatr3x3* : multiplyMatr3x3 \
) ( R, X, Y)

#define divide( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : divideScalar, \
    TVect2Rd* : divideVect2Rd, \
    TVect3Rd* : divideVect3Rd, \
    TMatr3x3* : divideMatr3x3 \
) ( R, X, Y)

#define transpose( R, X) _Generic( ( R, X), \
    TMatr3x3* : transposeMatr3x3 \
) ( R, X, Y)

#endif // VECT_LIB_H

