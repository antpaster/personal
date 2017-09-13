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
 ** \brief Краткий комментарий к файлу
 **      Описание шаблонов матричных операций
 ** Расширенный комментарий к файлу
 */

#ifndef MATRIX_OPS_AS_TEMPLATE_H
#define MATRIX_OPS_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>
#include <stdint.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

typedef struct SindexPair {
    size_t iRow;
    size_t iColumn;
} TindexPair;

int TEMPLATE( transpose, T)( T*, const size_t, const size_t);
int TEMPLATE( inverse, T)( T*, const size_t);
int TEMPLATE( matr_multiply, T)( T*, const T*, const T*, const size_t);
int TEMPLATE( determine, T)( T*, const T*, const size_t);

#endif

#endif

#endif // MATRIX_OPS_AS_TEMPLATE_H

