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
 ** \file  all_possible_sums.h
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблонов матричных операций
 ** Расширенный комментарий к файлу
 */

#ifndef ALL_POSSIBLE_MATRIX_OPS_H
#define ALL_POSSIBLE_MATRIX_OPS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "matrix_ops_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "matrix_ops_as_template.h"

#endif

#endif // ALL_POSSIBLE_MATRIX_OPS_H

