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
 ** \file  matrix_ops_as_template.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 13.09.17
 ** \brief Matrix operations templates realization
 */

#ifdef T
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Transposing template
 * \param[ in, out] matrix Pointer to the transposed matrix
 * \param[ in] rowCount Matrix row count
 * \param[ in] columnCount Matrix column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input pointer */
int TEMPLATE( transpose, T)( T **matrix, const size_t rowCount, const size_t columnCount) {
    if( matrix) {
        T temp;
        T *currAddrExtra;

        size_t i, j = 0, k;

        const size_t pairArraySize = rowCount * columnCount;

        T matrixLocal[ rowCount][ columnCount];
        memmove( matrixLocal, matrix, rowCount * columnCount * sizeof( T));

        /* Index repeating flags array */
        uint8_t repeatFlagArray[ pairArraySize];
        uint8_t *currRepeatFlag;
        memset( repeatFlagArray, 0, pairArraySize * sizeof( uint8_t));

        /* The array of the pairs of the indexes */
        TindexPair pairArray[ pairArraySize];
        TindexPair *currIndexPairAddr;
        TindexPair *currIndexPairAddrExtra;

        /* Index pair array filling */
        for( i = 0; i < pairArraySize; ++i) {
            currIndexPairAddr = pairArray + i;
            currIndexPairAddr->iRow = i / rowCount;
            currIndexPairAddr->iColumn = i % rowCount;
        }

        for( i = 0; i < rowCount * columnCount; ++i) {
            currIndexPairAddr = pairArray + j;

            /* Assigning new index pair */
            if( currIndexPairAddr->iRow != currIndexPairAddr->iColumn) {
                currIndexPairAddr = pairArray + j;
                currIndexPairAddr->iRow = i;
                currIndexPairAddr->iColumn = ( i % rowCount) * rowCount + i / rowCount;

                /* Finding out if there was a index pair with same values of row or column */
                for( k = 0; k <= j; ++k) {
                    currIndexPairAddrExtra = pairArray + k;
                    if( ( currIndexPairAddrExtra->iRow == currIndexPairAddr->iColumn)
                        || ( currIndexPairAddr->iRow == currIndexPairAddrExtra->iColumn)) {

                        /* Setting the current repeat flag */
                        currRepeatFlag = repeatFlagArray + j;
                        *currRepeatFlag = 1;
                        break;
                    }
                }

                currRepeatFlag = repeatFlagArray + j;
                if( !( *currRepeatFlag)) {

                    /* Swap the T array variables */
                    temp = matrixLocal[ currIndexPairAddr->iRow / rowCount][ currIndexPairAddr->iRow
                        % rowCount];

                    matrixLocal[ currIndexPairAddr->iRow / rowCount][ currIndexPairAddr->iRow
                        % rowCount] = matrixLocal[ currIndexPairAddr->iColumn / rowCount]
                        [ currIndexPairAddr->iColumn % rowCount];

                    matrixLocal[ currIndexPairAddr->iColumn / rowCount][ currIndexPairAddr->iColumn
                        % rowCount] = temp;

//                    currAddr = matrix + currIndexPairAddr->iRow;
//                    temp = *currAddr;

//                    currAddrExtra = matrix + currIndexPairAddr->iColumn;
//                    *currAddr = *currAddrExtra;

//                    *currAddrExtra = temp;
                }
            }

            ++j;
        }

        return 0;
    }

    return 1;
}

/*! Matrix inversion template
 * \param[ out] result Pointer to the inverted matrix
 * \param[ in] matrix Pointer to the input matrix, rowCount * ( 2 * rowCount)
 * \param[ in] rowCount Matrix row count
 * \param[ in] columnCount Matrix column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input pointer, 2 - inverse matrix does not exist */
int TEMPLATE( inverse, T)( T **result, const T **matrix, const size_t rowCount) {

    if( matrix) {
        uint8_t flag = 1; /* The flag of the inverse matrix existance */
        T diagDenom;
        T denom;
        T workMatrRowBuf[ 2 * rowCount];

        int i, j, k, p;

        /* Assist matrix, firstly a copy of the input matrix */
        T assistMatr[ rowCount][ rowCount];
        memmove( assistMatr, matrix, rowCount * rowCount * sizeof( T));

        /* Working matrix: input matrix and the unit one connected to the input from the right */
        T workMatrix[ rowCount][ 2 * rowCount];
        for( i = 0; i < rowCount * rowCount; ++i) {
            workMatrix[ i / rowCount ][ i % rowCount]
                = assistMatr[ i / rowCount][ i % rowCount];
        }

        /* Making the unit matrix from the assist one */
        for( i = 0; i < rowCount * rowCount; ++i) {
            assistMatr[ i / rowCount][ i % rowCount] = ( i % 4) ? 0.0 : 1.0;
        }

        /* The right side of the working matrix now is the unit matrix. During the calcilation
         * there will be formed the inverse matrix*/
        for( i = 0; i < rowCount * rowCount; ++i) {
            workMatrix[ i / rowCount][ rowCount + i % rowCount]
                = assistMatr[ i / rowCount][ i % rowCount];
        }

        /* Checking whether there were zeroes on the main diagonal and swapping the strings in case
         * of yes */
        for( i = 0; i < rowCount; ++i) {
            if( ( 0 == workMatrix[ i][ i]) && ( rowCount - 1 != i)) {
                flag = 0;

                for( j = i + 1; j < rowCount; ++j) {

                    if( 0 != workMatrix[ j][ i]) {

                        for( k = 0; k < 2 * rowCount; ++k) {
                            workMatrRowBuf[ k] = workMatrix[ j][ k];
                            workMatrix[ j][ k] = workMatrix[ i][ k];
                            workMatrix[ i][ k] = workMatrRowBuf[ k];
                        }
                        flag = 1;
                        break;
                    }
                    else {
                        flag = 0;
                    }
                }
            }
        }

        if( flag) {
            /* Gauss-Jordan method straight way, result is upper triangle matrix */
            for( i = 0; i < rowCount; ++i) {
                diagDenom = workMatrix[ i][ i];

                for( j = i; j < 2 * rowCount; ++j) {
                    workMatrix[ i][ j] /= diagDenom;
                }

                for( k = i + 1; k < rowCount; ++k) {
                    denom = workMatrix[ k][ i];

                    for( p = i; p < 2 * rowCount; ++p) {
                        workMatrix[ k][ p] -= workMatrix[ i][ p] * denom;
                    }
                }
            }

            /* Gauss-Jordan method backward way, result is complete inverted matrix */
            for( i = rowCount - 2; i >= 0; --i) {
                for( k = i; k >= 0; --k) {
                    denom = workMatrix[ k][ i + 1];

                    for( j = 0; j < 2 * rowCount; ++j) {
                        workMatrix[ k][ j] -= workMatrix[ i + 1][ j] * denom;
                    }
                }
            }

            /* Output result matrix assigning */
            for( i = 0; i < rowCount * rowCount; ++i) {
                assistMatr[ i / rowCount][ i % rowCount]
                    = workMatrix[ i / rowCount][ rowCount + i % rowCount];
            }

            memmove( result, assistMatr, rowCount * rowCount * sizeof( T));
        }
        else {
            printf( "\nInverse matrix cannot be calculated!");
            return 2;
        }

        return 0;
    }

    return 1;
}

/*! Matrix multiplication template
 * \param[ out] result Pointer to the multiplication result matrix
 * \param[ in] mult1 Pointer to the first matrix-multiplier
 * \param[ in] mult2 Pointer to the second matrix-multiplier
 * \param[ in] mult1rowCount 1st matrix-multiplier row count
 * \param[ in] commonSize 1st matrix-multiplier column count or 2nd matrix-multiplier row count
 * \param[ in] mult2columnCount 2nd matrix-multiplier column count
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input or output pointer */
int TEMPLATE( matr_multiply, T)( T **result, const T **mult1, const T **mult2,
    const size_t mult1rowCount, const size_t commonSize, const size_t mult2columnCount) {

    if( result && mult1 && mult2) {
        size_t i, j, k;

        /* Dealing with two-dimensional matrices and index-based operations */
        T resultLocal[ commonSize][ commonSize];
        memset( resultLocal, 0, commonSize * commonSize * sizeof( T));

        T mult1local[ mult1rowCount][ commonSize];
        memmove( mult1local, mult1, mult1rowCount * commonSize * sizeof( T));

        T mult2local[ commonSize][ mult2columnCount];
        memmove( mult2local, mult2, commonSize * mult2columnCount * sizeof( T));

        for( i = 0; i < mult1rowCount; ++i) {
            for( j = 0; j < mult2columnCount; ++j) {
                resultLocal[ i][ j] = 0;

                for( k = 0; k < commonSize; ++k) {
                    resultLocal[ i][ j] += mult1local[ i][ k] * mult2local[ k][ j];
                }
            }
        }

        /* Output result matrix assigning */
        memmove( result, resultLocal, commonSize * commonSize * sizeof( T));

        return 0;
    }

    return 1;
}

/*! Matrix without iRow row and iColumn column gaining, auxiliary to the matrix determinant
 * calculation function
 * \param[ out] result Pointer to the result matrix
 * \param[ in] sourceMatr Pointer to the source matrix
 * \param[ in] iRow Row for deleting index
 * \param[ in] iColumn Column for deleting index
 * \param[ in] rowCount Row (column) count of the sourceMatr
 ***************************************************************************************************
 * \return 0 - ok, 1 - null input or output pointer */
int TEMPLATE( matrIjLess, T)( T **result, const T** sourceMatr, const size_t iRow,
    const size_t iColumn, const size_t rowCount) {

    if( result && sourceMatr) {
        size_t ki, kj, di = 0, dj = 0;

        /* Dealing with two-dimensional matrices and index-based operations */
        T sourceMatrLocal[ rowCount][ rowCount];
        memmove( sourceMatrLocal, sourceMatr, rowCount * rowCount * sizeof( T));

        T resultLocal[ rowCount - 1][ rowCount - 1];
        memset( resultLocal, 0, ( rowCount - 1) * ( rowCount - 1) * sizeof( T));

        for( ki = 0; ki < rowCount - 1; ++ki) {
            if( ki == iRow) {
                /* Row index checking */
                di = 1;
            }

            dj = 0;

            for( kj = 0; kj < rowCount - 1; ++kj) {
                if( kj == iColumn) {
                    /* Column index checking */
                    dj = 1;
                }

                resultLocal[ ki][ kj] = sourceMatrLocal[ ki + di][ kj + dj];
            }
        }

        /* Output result matrix assigning */
        memmove( result, resultLocal, ( rowCount - 1) * ( rowCount - 1) * sizeof( T));

        return 0;
    }

    return 1;
}

/*! Recursive matrix determinant calculation template
 * \param[ out] result Pointer to the variable which holds the determinant value
 * \param[ in] matrix Pointer to the matrix
 * \param[ in] rowCount Matrix row count
 * \param[ in] order Matrix order
 ***************************************************************************************************
 * \return: 0 - ok, 1 - null input pointer, 2 - bad matrix order */
int TEMPLATE( determine, T)( T *result, const T **matrix, const size_t rowCount, const int order) {
    if( matrix) {
        int i, k = 1, nextOrder = rowCount - 1;
        size_t currRowCount = rowCount;

        /* Dealing with two-dimensional matrices and index-based operations */
        T assistMatr[ rowCount][ rowCount];
        memmove( assistMatr, matrix, rowCount * rowCount * sizeof( T));

        T auxiliaryDet;

        if( order < 1) {
            printf( "\nDeterminant is uncalculable! Order is %d", order);
            return 2;
        }
        else if( 1 == order) {
            *result = assistMatr[ 0][ 0];
        }
        else if( 2 == order) {
            *result = assistMatr[ 0][ 0] * assistMatr[ 1][ 1]
                - assistMatr[ 0][ 1] * assistMatr[ 1][ 0];
        }
        else {
            T workingMatr[ nextOrder][ nextOrder];
            memset( workingMatr, 0, nextOrder * nextOrder * sizeof( T));

            for( i = 0; i < order; ++i) {
                /* Column cycle */
                TEMPLATE( matrIjLess, T)( workingMatr, assistMatr, 0, i, order);
                TEMPLATE( determine, T)( &auxiliaryDet, workingMatr, nextOrder, nextOrder);
                *result += k * assistMatr[ 0][ i] * auxiliaryDet;

                k = -k;
            }
        }

        return 0;
    }

    return 1;
}

#endif

#endif
