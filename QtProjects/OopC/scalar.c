#include <stdlib.h>
#include <stdint.h>

#include "scalar.h"
#include "vect_lib.h"

/*! Scalar
 **************************************************************************************************/
static double getValue( TScalar *pS) {
    return ( ( TPrivateScalar*)( pS->_privateScalar))->_value;
}

static double getValid( TScalar *pS) {
    return ( ( TPrivateScalar*)( pS->_privateScalar))->_valid;
}

static void setScalar( TScalar *pS, double value, uint8_t valid) {
    ( ( TPrivateScalar*)( pS->_privateScalar))->_value = value;
    ( ( TPrivateScalar*)( pS->_privateScalar))->_valid = valid;
}

TScalar *newScalar( ) {
    TScalar *pS;

    pS = ( TScalar*)malloc( sizeof( TScalar));
    pS->_privateScalar = malloc( sizeof( TPrivateScalar));
    pS->_getValue = &getValue;
    pS->_getValid = &getValid;
    pS->_setScalar = &setScalar;

    return pS;
}

void deleteScalar( TScalar *pS) {
    free( pS->_privateScalar);
    free( pS);
}

int addScalar( TScalar *pResult, TScalar *pS1, TScalar *pS2) {
    int result = 1;

    if( pS1 && pS2) {
        double resValue = pS1->_getValue( pS1) + pS2->_getValue( pS2);
        uint8_t resValid = pS1->_getValid( pS1) & pS2->_getValid( pS2);

        pResult->_setScalar( pResult, resValue, resValid);

        result = 0;
    }

    return result;
}

int subtractScalar( TScalar *pResult, TScalar *pS1, TScalar *pS2) {
    int result = 1;

    if( pS1 && pS2) {
        double resValue = pS1->_getValue( pS1) - pS2->_getValue( pS2);
        uint8_t resValid = pS1->_getValid( pS1) & pS2->_getValid( pS2);

        pResult->_setScalar( pResult, resValue, resValid);

        result = 0;
    }

    return result;
}

int multiplyScalar( TScalar *pResult, TScalar *pS1, TScalar *pS2) {
    int result = 1;

    if( pS1 && pS2) {
        double resValue = pS1->_getValue( pS1) * pS2->_getValue( pS2);
        uint8_t resValid = pS1->_getValid( pS1) & pS2->_getValid( pS2);

        pResult->_setScalar( pResult, resValue, resValid);

        result = 0;
    }

    return result;
}

int divideScalar( TScalar *pResult, TScalar *pS1, TScalar *pS2) {
    int result = 1;

    if( pS1 && pS2) {
        double denom = ( fabs( pS2->_getValue( pS2)) > F_NULL) ? pS2->_getValue( pS2) :  F_NULL;
        double resValue = pS1->_getValue( pS1) / denom;
        uint8_t resValid = pS1->_getValid( pS1) & pS2->_getValid( pS2);

        pResult->_setScalar( pResult, resValue, resValid);

        result = 0;
    }

    return result;
}
