#include "scalar.h"
#include "vect2rd.h"
#include "vect_lib.h"

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

int addVect2Rd( TVect2Rd *pResult, TVect2Rd *pV2Rd1, TVect2Rd *pV2Rd2) {
    int result = 1;

    if( pV2Rd1 && pV2Rd2) {
        double resXvalue = pV2Rd1->_getXvalue( pV2Rd1) + pV2Rd2->_getXvalue( pV2Rd2);
        double resYvalue = pV2Rd1->_getYvalue( pV2Rd1) + pV2Rd2->_getYvalue( pV2Rd2);
        uint8_t resValid = pV2Rd1->_getValid( pV2Rd1) & pV2Rd2->_getValid( pV2Rd2);

        pResult->_setVect2Rd( pResult, resXvalue, resYvalue, resValid);

        result = 0;
    }

    return result;
}
