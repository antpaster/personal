#include <stdio.h>

#include "oop_math_include.h"
#include "vect_lib.h"

#include "all_possible_sums.h"

int main( ) {
    TScalar *pS = newScalar( );

    pS->_setScalar( pS, 15.0, 1);

    double value;
    value = pS->_getValue( pS);

    printf( "Scalar value: %f\n", value);

    TScalar *pSextra = newScalar( );
    pSextra->_setScalar( pSextra, 2.0, 1);

    TScalar *pResult = newScalar( );
    add( pResult, pS, pSextra);
    printf( "Scalar sum: %f\n", pResult->_getValue( pResult));

    subtract( pResult, pS, pSextra);
    printf( "Scalar subtraction: %f\n", pResult->_getValue( pResult));

    multiply( pResult, pS, pSextra);
    printf( "Scalar multiplication: %f\n", pResult->_getValue( pResult));

    divide( pResult, pS, pSextra);
    printf( "Scalar division: %f\n", pResult->_getValue( pResult));

    remove( pS);
    remove( pSextra);
    remove( pResult);


    TVect2Rd *pV2Rd = newVect2Rd( );
    pV2Rd->_setVect2Rd( pV2Rd, 15.0, 10.0, 1);

    double xValue, yValue;
    xValue = pV2Rd->_getXvalue( pV2Rd);
    yValue = pV2Rd->_getYvalue( pV2Rd);

    printf( "Vect2Rd value: {%f, %f}\n", xValue, yValue);

    TVect2Rd *pV2RdAdd = newVect2Rd( );
    pV2RdAdd->_setVect2Rd( pV2RdAdd, -5.0, 13.0, 0);

    TVect2Rd *pV2RdSum = newVect2Rd( );
    add( pV2RdSum, pV2Rd, pV2RdAdd);
    printf( "Vect sum: {%f, %f}\n", pV2RdSum->_getXvalue( pV2RdSum),
        pV2RdSum->_getYvalue( pV2RdSum));

    remove( pV2Rd);
    remove( pV2RdAdd);
    remove( pV2RdSum);

    return 0;
}
