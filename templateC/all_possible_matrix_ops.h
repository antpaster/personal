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
 ** \file  all_possible_matrix_ops.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 13.09.17
 ** \brief All possible types for matrix operations template description
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

