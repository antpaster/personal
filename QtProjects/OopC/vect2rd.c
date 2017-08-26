#include <stdlib.h>
#include <stdint.h>

#include "scalar.h"
#include "vect2rd.h"

/*! Vect2Rd
 **************************************************************************************************/
static double getXvalue( TVect2Rd *pV2Rd) {
    return ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_privateScalar._value;
}

static double getYvalue( TVect2Rd *pV2Rd) {
    return ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_yValue;
}

static double getValid( TVect2Rd *pV2Rd) {
    return ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_privateScalar._valid;
}

static void setVect2Rd( TVect2Rd *pV2Rd, double xValue, double yValue, uint8_t valid) {
    ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_privateScalar._value = xValue;
    ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_yValue = yValue;
    ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_privateScalar._valid = valid;
}

TVect2Rd *newVect2Rd( ) {
    TVect2Rd *pV2Rd;

    pV2Rd = ( TVect2Rd*)malloc( sizeof( TVect2Rd));
    pV2Rd->_privateVect2Rd = malloc( sizeof( TPrivateVect2Rd));
    pV2Rd->_getXvalue = &getXvalue;
    pV2Rd->_getYvalue = &getYvalue;
    pV2Rd->_getValid = &getValid;
    pV2Rd->_setVect2Rd = &setVect2Rd;

    return pV2Rd;
}

void deleteVect2Rd( TVect2Rd *pV2Rd) {
    free( pV2Rd->_privateVect2Rd);
    free( pV2Rd);
}
