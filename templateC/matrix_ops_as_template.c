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
 ** \brief Краткий комментарий к файлу
 **      Реализация шаблонов матричных операций
 ** Расширенный комментарий к файлу
 */

#ifdef T
#include <stdlib.h>
#include <stdint.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

int TEMPLATE( transpose, T)( T *matrix, const size_t rowCount, const size_t columnCount) {
    if( matrix) {
        T temp;
        T *currAddr;
        T *currAddrExtra;

        size_t i, j = 0, k;

        const size_t pairArraySize = rowCount * columnCount;
//            - ( ( rowCount > columnCount) ? rowCount : columnCount);

        uint8_t repeatFlagArray[ pairArraySize];
        uint8_t *currRepeatFlag;
        memset( repeatFlagArray, 0, pairArraySize * sizeof( uint8_t));

        TindexPair pairArray[ pairArraySize];
        TindexPair *currIndexPairAddr;
        TindexPair *currIndexPairAddrExtra;

        for( i = 0; i < pairArraySize; ++i) {
            currIndexPairAddr = pairArray + i;
            currIndexPairAddr->iRow = i / rowCount;
            currIndexPairAddr->iColumn = i % rowCount;
        }

        for( i = 0; i < rowCount + columnCount; ++i) {
            currIndexPairAddr = pairArray + j;

            if( currIndexPairAddr->iRow != currIndexPairAddr->iColumn) {
                currIndexPairAddr = pairArray + j;
                currIndexPairAddr->iRow = i;
                currIndexPairAddr->iColumn = ( i % rowCount) * rowCount + i / rowCount;

                for( k = 0; k <= j; ++k) {
                    currIndexPairAddrExtra = pairArray + k;
                    if( ( currIndexPairAddrExtra->iRow == currIndexPairAddr->iColumn)
                        || ( currIndexPairAddr->iRow == currIndexPairAddrExtra->iColumn)) {
                        currRepeatFlag = repeatFlagArray + j;
                        *currRepeatFlag = 1;
                        break;
                    }
                }

                currRepeatFlag = repeatFlagArray + j;
                if( !( *currRepeatFlag)) {
                    currAddr = matrix + currIndexPairAddr->iRow;
                    temp = *currAddr;

                    currAddrExtra = matrix + currIndexPairAddr->iColumn;
                    *currAddr = *currAddrExtra;

                    *currAddrExtra = temp;
                }
            }

            ++j;
        }

        return 0;
    }

    return 1;
}

int TEMPLATE( inverse, T)( T *matrix, const size_t size) {
    return 1;
}

int TEMPLATE( matr_multiply, T)( T *result, const T *mult1, const T *mult2, const size_t size) {
    return 1;
}

int TEMPLATE( determine, T)( T *result, const T *matrix, const size_t size) {
    return 1;
}

#endif

#endif
