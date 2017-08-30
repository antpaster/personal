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
 ** \file  vect2rd.c
 ** \brief Краткий комментарий к файлу
 **      Реализация класса Двумерный вещественный вектор с достоверностью
 ** Расширенный комментарий к файлу
 */

#include <stdlib.h>

#include "oop_math_include.h"

#if ADV_MATH_LIB

/*! Vect2Rd
 ***************************************************************************************************
 */
static double getXvalue( TVect2Rd *pV2Rd) {
    return ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_privateScalar._value;
}

static double getYvalue( TVect2Rd *pV2Rd) {
    return ( ( TPrivateVect2Rd*)( pV2Rd->_privateVect2Rd))->_yValue;
}

static uint8_t getValid( TVect2Rd *pV2Rd) {
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

int subtractVect2Rd( TVect2Rd *pResult, TVect2Rd *pV2Rd1, TVect2Rd *pV2Rd2) {
    int result = 1;

    if( pV2Rd1 && pV2Rd2) {
        double resXvalue = pV2Rd1->_getXvalue( pV2Rd1) - pV2Rd2->_getXvalue( pV2Rd2);
        double resYvalue = pV2Rd1->_getYvalue( pV2Rd1) - pV2Rd2->_getYvalue( pV2Rd2);
        uint8_t resValid = pV2Rd1->_getValid( pV2Rd1) & pV2Rd2->_getValid( pV2Rd2);

        pResult->_setVect2Rd( pResult, resXvalue, resYvalue, resValid);

        result = 0;
    }

    return result;
}

//int multiplyVect2Rd( TVect2Rd *pResult, TVect2Rd *pV2Rd1, TVect2Rd *pV2Rd2) {
//    int result = 1;

//    if( pV2Rd1 && pV2Rd2) {
//        double resXvalue = pV2Rd1->_getXvalue( pV2Rd1) + pV2Rd2->_getXvalue( pV2Rd2);
//        double resYvalue = pV2Rd1->_getYvalue( pV2Rd1) + pV2Rd2->_getYvalue( pV2Rd2);
//        uint8_t resValid = pV2Rd1->_getValid( pV2Rd1) & pV2Rd2->_getValid( pV2Rd2);

//        pResult->_setVect2Rd( pResult, resXvalue, resYvalue, resValid);

//        result = 0;
//    }

//    return result;
//}

//int divideVect2Rd( TVect2Rd *pResult, TVect2Rd *pV2Rd1, TVect2Rd *pV2Rd2) {
//    int result = 1;

//    if( pV2Rd1 && pV2Rd2) {
//        double resXvalue = pV2Rd1->_getXvalue( pV2Rd1) + pV2Rd2->_getXvalue( pV2Rd2);
//        double resYvalue = pV2Rd1->_getYvalue( pV2Rd1) + pV2Rd2->_getYvalue( pV2Rd2);
//        uint8_t resValid = pV2Rd1->_getValid( pV2Rd1) & pV2Rd2->_getValid( pV2Rd2);

//        pResult->_setVect2Rd( pResult, resXvalue, resYvalue, resValid);

//        result = 0;
//    }

//    return result;
//}

#endif
