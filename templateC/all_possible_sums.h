/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          30.08.17 г. APasternak
 ** ИЗМЕНЕН:         30.08.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 30.08.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  all_possible_sums.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief All possible types for sum template description
 */

#ifndef ALL_POSSIBLE_SUMS_H
#define ALL_POSSIBLE_SUMS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "sum_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "sum_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "sum_as_template.h"

#endif

#endif // ALL_POSSIBLE_SUMS_H

