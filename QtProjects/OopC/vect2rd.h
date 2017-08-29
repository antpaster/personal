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
 ** \file  vect2rd.h
 ** \brief Краткий комментарий к файлу
 **      Описание класса Двумерный вещественный вектор с достоверностью
 ** Расширенный комментарий к файлу
 */

#ifndef VECT2RD_H
#define VECT2RD_H

#include "oop_math_include.h"

#if ADV_MATH_LIB

/*! Vect2Rd
 ***************************************************************************************************
 */
typedef struct SPrivateVect2Rd {
    TPrivateScalar _privateScalar;
    double _yValue;
} TPrivateVect2Rd;

typedef struct SVect2Rd {
    void *_privateVect2Rd;

    double ( *_getXvalue)( struct SVect2Rd*);
    double ( *_getYvalue)( struct SVect2Rd*);
    uint8_t ( *_getValid)( struct SVect2Rd*);

    void ( *_setVect2Rd)( struct SVect2Rd*, double, double, uint8_t);
} TVect2Rd;

#ifdef __cplusplus
extern "C" {
#endif

TVect2Rd* newVect2Rd( );
void deleteVect2Rd( TVect2Rd*);

int addVect2Rd( TVect2Rd*, TVect2Rd*, TVect2Rd*);
int subtractVect2Rd( TVect2Rd*, TVect2Rd*, TVect2Rd*);
int multiplyVect2Rd( TVect2Rd*, TVect2Rd*, TVect2Rd*);
int divideVect2Rd( TVect2Rd*, TVect2Rd*, TVect2Rd*);

#ifdef __cplusplus
};
#endif

#endif

#endif // VECT2RD_H

