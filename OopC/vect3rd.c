/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          28 августа 2017 г. APasternak
 ** ИЗМЕНЕН:         28 августа 2017 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 28 августа 2017 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  vect3rd.c
 ** \brief Краткий комментарий к файлу
 **      Реализация класса Трехмерный вещественный вектор с достоверностью
 ** Расширенный комментарий к файлу
 */

#include <stdlib.h>

#include "oop_math_include.h"

#if ADV_MATH_LIB

/*! Vect3Rd
 ***************************************************************************************************
 */
static double getXvalue( TVect3Rd *pV3Rd) {
    return ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_privateVect2Rd._privateScalar._value;
}

static double getYvalue( TVect3Rd *pV3Rd) {
    return ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_privateVect2Rd._yValue;
}

static double getZvalue( TVect3Rd *pV3Rd) {
    return ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_zValue;
}

static uint8_t getValid( TVect3Rd *pV3Rd) {
    return ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_privateVect2Rd._privateScalar._valid;
}

static void setVect3Rd( TVect3Rd *pV3Rd, double xValue, double yValue, double zValue,
    uint8_t valid) {
    ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_privateVect2Rd._privateScalar._value = xValue;
    ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_privateVect2Rd._yValue = yValue;
    ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_zValue = zValue;
    ( ( TPrivateVect3Rd*)( pV3Rd->_privateVect3Rd))->_privateVect2Rd._privateScalar._valid = valid;
}

TVect3Rd *newVect3Rd( ) {
    TVect3Rd *pV3Rd;

    pV3Rd = ( TVect3Rd*)malloc( sizeof( TVect3Rd));
    pV3Rd->_privateVect3Rd = malloc( sizeof( TPrivateVect3Rd));
    pV3Rd->_getXvalue = &getXvalue;
    pV3Rd->_getYvalue = &getYvalue;
    pV3Rd->_getZvalue = &getZvalue;
    pV3Rd->_getValid = &getValid;
    pV3Rd->_setVect3Rd = &setVect3Rd;

    return pV3Rd;
}

void deleteVect3Rd( TVect3Rd *pV3Rd) {
    free( pV3Rd->_privateVect3Rd);
    free( pV3Rd);
}

int addVect3Rd( TVect3Rd *pResult, TVect3Rd *pV3Rd1, TVect3Rd *pV3Rd2) {
    int result = 1;

    if( pV3Rd1 && pV3Rd2) {
        double resXvalue = pV3Rd1->_getXvalue( pV3Rd1) + pV3Rd2->_getXvalue( pV3Rd2);
        double resYvalue = pV3Rd1->_getYvalue( pV3Rd1) + pV3Rd2->_getYvalue( pV3Rd2);
        double resZvalue = pV3Rd1->_getZvalue( pV3Rd1) + pV3Rd2->_getZvalue( pV3Rd2);
        uint8_t resValid = pV3Rd1->_getValid( pV3Rd1) & pV3Rd2->_getValid( pV3Rd2);

        pResult->_setVect3Rd( pResult, resXvalue, resYvalue, resZvalue, resValid);

        result = 0;
    }

    return result;
}

int subtractVect3Rd( TVect3Rd *pResult, TVect3Rd *pV3Rd1, TVect3Rd *pV3Rd2) {
    int result = 1;

    if( pV3Rd1 && pV3Rd2) {
        double resXvalue = pV3Rd1->_getXvalue( pV3Rd1) - pV3Rd2->_getXvalue( pV3Rd2);
        double resYvalue = pV3Rd1->_getYvalue( pV3Rd1) - pV3Rd2->_getYvalue( pV3Rd2);
        double resZvalue = pV3Rd1->_getZvalue( pV3Rd1) - pV3Rd2->_getZvalue( pV3Rd2);
        uint8_t resValid = pV3Rd1->_getValid( pV3Rd1) & pV3Rd2->_getValid( pV3Rd2);

        pResult->_setVect3Rd( pResult, resXvalue, resYvalue, resZvalue, resValid);

        result = 0;
    }

    return result;
}

//int multiplyVect3Rd( TVect3Rd *pResult, TVect3Rd *pV3Rd1, TVect3Rd *pV3Rd2) {
//    int result = 1;

//    if( pV3Rd1 && pV3Rd2) {
//        double resXvalue = pV3Rd1->_getXvalue( pV3Rd1) + pV3Rd2->_getXvalue( pV3Rd2);
//        double resYvalue = pV3Rd1->_getYvalue( pV3Rd1) + pV3Rd2->_getYvalue( pV3Rd2);
//        uint8_t resValid = pV3Rd1->_getValid( pV3Rd1) & pV3Rd2->_getValid( pV3Rd2);

//        pResult->_setVect3Rd( pResult, resXvalue, resYvalue, resValid);

//        result = 0;
//    }

//    return result;
//}

//int divideVect3Rd( TVect3Rd *pResult, TVect3Rd *pV3Rd1, TVect3Rd *pV3Rd2) {
//    int result = 1;

//    if( pV3Rd1 && pV3Rd2) {
//        double resXvalue = pV3Rd1->_getXvalue( pV3Rd1) + pV3Rd2->_getXvalue( pV3Rd2);
//        double resYvalue = pV3Rd1->_getYvalue( pV3Rd1) + pV3Rd2->_getYvalue( pV3Rd2);
//        uint8_t resValid = pV3Rd1->_getValid( pV3Rd1) & pV3Rd2->_getValid( pV3Rd2);

//        pResult->_setVect3Rd( pResult, resXvalue, resYvalue, resValid);

//        result = 0;
//    }

//    return result;
//}

#endif
