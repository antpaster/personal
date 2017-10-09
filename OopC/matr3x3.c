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
 ** \file  matr3x3.c
 ** \brief Краткий комментарий к файлу
 **      Реализация класса Вещественная матрица 3х3
 ** Расширенный комментарий к файлу
 */

#include <stdlib.h>

#include "oop_math_include.h"

#if ADV_MATH_LIB

/*! Matr3x3
 ***************************************************************************************************
 */
static double getValueByIndex( TMatr3x3 *pM3x3, uint8_t iRow, uint8_t iColumn) {
    return *( *( ( ( TPrivateMatr3x3*)( pM3x3->_privateMatr3x3))->_matr) + ( 3 * iRow) + iColumn);
}

static void setMatr3x3( TMatr3x3 *pM3x3, double *pRow1, double *pRow2, double *pRow3) {
    if( pRow1) {
        *( ( ( TPrivateMatr3x3*)( pM3x3->_privateMatr3x3))->_matr) = pRow1;
    }

    if( pRow2) {
        double *row2addr = *( ( ( TPrivateMatr3x3*)( pM3x3->_privateMatr3x3))->_matr) + 3;
        row2addr = pRow2;
    }

    if( pRow3) {
        double *row3addr = *( ( ( TPrivateMatr3x3*)( pM3x3->_privateMatr3x3))->_matr) + 6;
        row3addr = pRow3;
    }
}

TMatr3x3 *newMatr3x3( ) {
    TMatr3x3 *pM3x3;

    pM3x3 = ( TMatr3x3*)malloc( sizeof( TMatr3x3));
    pM3x3->_privateMatr3x3 = malloc( sizeof( TPrivateMatr3x3));
    pM3x3->_getValueByIndex = &getValueByIndex;
    pM3x3->_setMatr3x3 = &setMatr3x3;

    return pM3x3;
}

void deleteMatr3x3( TMatr3x3 *pM3x3) {
    free( pM3x3->_privateMatr3x3);
    free( pM3x3);
}

int addMatr3x3( TMatr3x3 *pResult, TMatr3x3 *pM3x3_1, TMatr3x3 *pM3x3_2) {
    int result = 1;

    if( pM3x3_1 && pM3x3_2) {
        double **resMatr;
        double *currAddr;

        int i;
        for( i = 0; i < 9; ++i) {
            currAddr = *resMatr + i;
            *currAddr = pM3x3_1->_getValueByIndex( pM3x3_1, i % 3, i)
                + pM3x3_2->_getValueByIndex( pM3x3_2, i % 3, i);
        }

        pResult->_setMatr3x3( pResult, *resMatr, *resMatr + 3, *resMatr + 6);

        result = 0;
    }

    return result;
}

int subtractMatr3x3( TMatr3x3 *pResult, TMatr3x3 *pM3x3_1, TMatr3x3 *pM3x3_2) {
    int result = 1;

    if( pM3x3_1 && pM3x3_2) {
        double **resMatr;
        double *currAddr;

        int i;
        for( i = 0; i < 9; ++i) {
            currAddr = *resMatr + i;
            *currAddr = pM3x3_1->_getValueByIndex( pM3x3_1, i % 3, i)
                - pM3x3_2->_getValueByIndex( pM3x3_2, i % 3, i);
        }

        pResult->_setMatr3x3( pResult, *resMatr, *resMatr + 3, *resMatr + 6);

        result = 0;
    }

    return result;
}

int multiplyMatr3x3( TMatr3x3 *pResult, TMatr3x3 *pM3x3_1, TMatr3x3 *pM3x3_2) {
    int result = 1;

    if( pM3x3_1 && pM3x3_2) {
        double **resMatr;
        double *currAddr;

        memset( resMatr, 0, 9 * sizeof( double));

        int i, j, k;
        for( i = 0; i < 3; ++i) {
            for( j = 0; j < 3; ++j) {
                for( k = 0; k < 3; ++k) {
                    currAddr = *resMatr + i * 3 + j;
                    *currAddr = pM3x3_1->_getValueByIndex( pM3x3_1, i, k)
                        * pM3x3_2->_getValueByIndex( pM3x3_2, k, j);
                }
            }
        }

        pResult->_setMatr3x3( pResult, *resMatr, *resMatr + 3, *resMatr + 6);

        result = 0;
    }

    return result;
}

//int divideMatr3x3( TMatr3x3 *pResult, TMatr3x3 *pV3Rd1, TMatr3x3 *pV3Rd2) {
//    int result = 1;

//    if( pV3Rd1 && pV3Rd2) {
//        double resXvalue = pV3Rd1->_getXvalue( pV3Rd1) + pV3Rd2->_getXvalue( pV3Rd2);
//        double resYvalue = pV3Rd1->_getYvalue( pV3Rd1) + pV3Rd2->_getYvalue( pV3Rd2);
//        uint8_t resValid = pV3Rd1->_getValid( pV3Rd1) & pV3Rd2->_getValid( pV3Rd2);

//        pResult->_setMatr3x3( pResult, resXvalue, resYvalue, resValid);

//        result = 0;
//    }

//    return result;
//}

int transposeMatr3x3( TMatr3x3 *pResult, TMatr3x3 *pM3x3) {
    int result = 1;

    if( pM3x3) {
        double **resMatr;
        double *currAddr;

        int i;
        for( i = 0; i < 9; ++i) {
            currAddr = *resMatr + i;
            *currAddr = pM3x3->_getValueByIndex( pM3x3, i, i % 3);
        }

        result = 0;
    }

    return result;
}

#endif
