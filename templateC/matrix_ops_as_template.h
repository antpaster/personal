/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          13.09.17 г. APasternak
 ** ИЗМЕНЕН:         13.09.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 13.09.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  matrix_ops_as_template.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 13.09.17
 ** \brief Matrix operations template description
 */

#ifndef MATRIX_OPS_AS_TEMPLATE_H
#define MATRIX_OPS_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>
#include <stdint.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Matrix indexes pair struct
 ***************************************************************************************************
 */
typedef struct SindexPair {
    size_t iRow;
    size_t iColumn;
} TindexPair;

/*! Transposing template 
 * \param[ in, out] matrix Pointer to the transposed matrix
 * \param[ in] rowCount Matrix row count
 * \param[ in] columnCount Matrix column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input pointer */
int TEMPLATE( transpose, T)( T**, const size_t, const size_t);

/*! Matrix inversion template
 * \param[ out] result Pointer to the inverted matrix
 * \param[ in] matrix Pointer to the input matrix, rowCount * ( 2 * rowCount)
 * \param[ in] rowCount Matrix row count
 * \param[ in] columnCount Matrix column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input pointer, 2 - inverse matrix does not exist */
int TEMPLATE( inverse, T)( T**, const T**, const size_t);

/*! Matrix multiplication template
 * \param[ out] result Pointer to the multiplication result matrix
 * \param[ in] mult1 Pointer to the first matrix-multiplier
 * \param[ in] mult2 Pointer to the second matrix-multiplier
 * \param[ in] mult1rowCount 1st matrix-multiplier row count
 * \param[ in] commonSize 1st matrix-multiplier column count or 2nd matrix-multiplier row count
 * \param[ in] mult2columnCount 2nd matrix-multiplier column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input or output pointer */
int TEMPLATE( matr_multiply, T)( T**, const T**, const T**, const size_t, const size_t
    const size_t);

/* Recursive matrix determinant calculation template
 * \param[ out] result Pointer to the variable which holds the determinant value
 * \param[ in] matrix Pointer to the matrix
 * \param[ in] rowCount Matrix row count
 * \param[ in] order Matrix order
 ***************************************************************************************************
 * \return: 0 - ok, 1 - null input pointer, 2 - bad matrix order */
int TEMPLATE( determine, T)( T*, const T**, const size_t, const int);

#endif

#endif

#endif // MATRIX_OPS_AS_TEMPLATE_H

