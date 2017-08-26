#include <stdlib.h>
#include <stdint.h>
#include "scalar.h"

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
