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
 ** \file  vect_lib.h
 ** \brief Краткий комментарий к файлу
 **      Мастер-файл ООП математической библиотеки
 ** Расширенный комментарий к файлу
 */

#ifndef VECT_LIB_H
#define VECT_LIB_H

#include "oop_math_include.h"

#if ADV_MATH_LIB

//#define create( ) _Generic( ( ), \
//    TScalar* : newScalar, \
//    TVect2Rd* : newVect2Rd, \
//    TVect3Rd* : newVect3Rd, \
//    TMatr3x3* : newMatr3x3 \
//) ( )

#define add( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : addScalar, \
    TVect2Rd* : addVect2Rd, \
    TVect3Rd* : addVect3Rd, \
    TMatr3x3* : addMatr3x3 \
) ( R, X, Y)

#define subtract( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : subtractScalar, \
    TVect2Rd* : subtractVect2Rd, \
    TVect3Rd* : subtractVect3Rd, \
    TMatr3x3* : subtractMatr3x3 \
) ( R, X, Y)

#define multiply( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : multiplyScalar, \
    TVect2Rd* : multiplyVect2Rd, \
    TVect3Rd* : multiplyVect3Rd, \
    TMatr3x3* : multiplyMatr3x3 \
) ( R, X, Y)

#define divide( R, X, Y) _Generic( ( R, X, Y), \
    TScalar* : divideScalar, \
    TVect2Rd* : divideVect2Rd, \
    TVect3Rd* : divideVect3Rd, \
    TMatr3x3* : divideMatr3x3 \
) ( R, X, Y)

#define transpose( R, X) _Generic( ( R, X), \
    TMatr3x3* : transposeMatr3x3 \
) ( R, X, Y)

#define remove( R) _Generic( ( R), \
    TScalar* : newScalar, \
    TVect2Rd* : newVect2Rd, \
    TVect3Rd* : newVect3Rd, \
    TMatr3x3* : newMatr3x3 \
) ( R)

#endif

#endif // VECT_LIB_H

