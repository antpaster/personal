#ifndef VECT_LIB_H
#define VECT_LIB_H

#include "scalar.h"
#include "vect2rd.h"

int addScalar( TScalar *result, TScalar *pS1, TScalar *pS2);
int addVect2Rd( TVect2Rd *result, TVect2Rd *pV2Rd1, TVect2Rd *pV2Rd2);

#define add( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : addScalar, \
    TVect2Rd* : addVect2Rd \
) ( R, X, Y)

#endif // VECT_LIB_H

