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
 ** \file  scalar.h
 ** \brief Краткий комментарий к файлу
 **      Описание класса Скаляр
 ** Расширенный комментарий к файлу
 */

#ifndef SCALAR_H
#define SCALAR_H

#include "oop_math_include.h"

#if ADV_MATH_LIB

/*! Scalar
 ***************************************************************************************************
 */
typedef struct SPrivateScalar {
    double _value;
    uint8_t _valid;
} TPrivateScalar;

typedef struct SScalar {
    void *_privateScalar;

    double ( *_getValue)( struct SScalar*);
    uint8_t ( *_getValid)( struct SScalar*);

    void ( *_setScalar)( struct SScalar*, double, uint8_t);
} TScalar;

#ifdef __cplusplus
extern "C" {
#endif

TScalar* newScalar( );
void deleteScalar( TScalar*);

int addScalar( TScalar*, TScalar*, TScalar*);
int subtractScalar( TScalar*, TScalar*, TScalar*);
int multiplyScalar( TScalar*, TScalar*, TScalar*);
int divideScalar( TScalar*, TScalar*, TScalar*);

#ifdef __cplusplus
};
#endif

#endif

#endif // SCALAR_H

