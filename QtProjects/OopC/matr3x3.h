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
 ** \file  matr3x3.h
 ** \brief Краткий комментарий к файлу
 **      Описание класса Вещественная матрица 3х3
 ** Расширенный комментарий к файлу
 */

#ifndef MATR3X3_H
#define MATR3X3_H

#include "oop_math_include.h"

#if ADV_MATH_LIB

/*! Matr3x3
 ***************************************************************************************************
 */
typedef struct SPrivateMatr3x3 {
    double **_matr;
} TPrivateMatr3x3;

typedef struct SMatr3x3 {
    void *_privateMatr3x3;

    double ( *_getValueByIndex)( struct SMatr3x3*, uint8_t, uint8_t);
    void ( *_setMatr3x3)( struct SMatr3x3*, double*, double*, double*);
} TMatr3x3;

#ifdef __cplusplus
extern "C" {
#endif

TMatr3x3* newMatr3x3( );
void deleteMatr3x3( TMatr3x3*);

int addMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int subtractMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int multiplyMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int divideMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int transposeMatr3x3( TMatr3x3*, TMatr3x3*);

#ifdef __cplusplus
};
#endif

#endif

#endif // MATR3X3_H

